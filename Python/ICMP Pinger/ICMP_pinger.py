from socket import *
import os
import sys
import struct
import time
import select
import binascii  

ICMP_ECHO_REQUEST = 8

RTT_list = [] #list of RTTs
pkts_sent = 0 #number of packets sent
pkts_rec = 0 #number of packets received

def MyChecksum(hexlist):
    summ=0
    carry=0
    for i in range(0,len(hexlist),2):
        summ+=(hexlist[i]<< 8)  + hexlist[i+1]
        carry=summ>>16
        summ=(summ & 0xffff)  + carry
        #print(str(hex((hexlist[i]<< 8)  + hexlist[i+1]))+" "+str(hex(summ)) + "  " +str(hex(carry)) + " " + str(hex(summ^0xffff)))

    while( summ != (summ & 0xffff)):
        carry=summ>>16
        summ=summ & 0xffffffff  + carry
        #print("loop loop")

    summ^=0xffff #invert it
    return summ

def checksum(string): 
	csum = 0
	countTo = (len(string) // 2) * 2  
	count = 0

	while count < countTo:
		thisVal = ord(string[count+1]) * 256 + ord(string[count]) 
		csum = csum + thisVal 
		csum = csum & 0xffffffff  
		count = count + 2
	
	if countTo < len(string):
		csum = csum + ord(string[len(string) - 1])
		csum = csum & 0xffffffff 
	
	csum = (csum >> 16) + (csum & 0xffff)
	csum = csum + (csum >> 16)
	answer = ~csum 
	answer = answer & 0xffff 
	answer = answer >> 8 | (answer << 8 & 0xff00)
	#print(hex(answer))
	#print(hex(checksum0(string)))
	return answer
	
def receiveOnePing(mySocket, ID, timeout, destAddr):
	global RTT_list, pkts_rec #make global
	timeLeft = timeout
	
	while 1: 
		startedSelect = time.time()
		whatReady = select.select([mySocket], [], [], timeLeft)
		howLongInSelect = (time.time() - startedSelect)
		if whatReady[0] == []: # Timeout
			return "Request timed out."
	
		timeReceived = time.time() 
		recPacket, addr = mySocket.recvfrom(1024)
	       
	        #Fill in start
        
        	#Fetch the ICMP header from the IP packet
		
		icmp_header = recPacket[20:28] #find icmp header from packet
		icmp_type, code, checksum, pkt_ID, seq_num = struct.unpack("bbHHh", icmp_header) #unpack, set variables, obtain packet ID

		if pkt_ID == ID: #if packet ID is the same as ID
			size_bytes = struct.calcsize("d") #find byte size
			timeSent = struct.unpack("d", recPacket[28:28 + size_bytes])[0] #find time packet is sent
			RTT = timeReceived - timeSent #subtract time sent from time received to get RTT
			RTT_list.append(RTT) #append RTT to list
			pkts_rec += 1 #increment number of packets received
			return RTT
		    
                #Fill in end
		timeLeft = timeLeft - howLongInSelect
		if timeLeft <= 0:
			return "Request timed out."
	
def sendOnePing(mySocket, destAddr, ID):
	# Header is type (8), code (8), checksum (16), id (16), sequence (16)

	global pkts_sent #make global
	myChecksum = 0
	
        # Make a dummy header with a 0 checksum
	# struct -- Interpret strings as packed binary data
	header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, myChecksum, ID, 1)
	data = struct.pack("d", time.time())
    
	# Calculate the checksum on the data and the dummy header.
	#myChecksum = checksum(str(header + data))
	myChecksum = MyChecksum ([i for i in header] + [i for i in data])
	# Get the right checksum, and put in the header
	if sys.platform == 'darwin':
		# Convert 16-bit integers from host to network  byte order
		myChecksum = htons(myChecksum) & 0xffff		
	else:
		myChecksum = htons(myChecksum)
		
	header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, myChecksum, ID, 1)
	packet = header + data
	
	mySocket.sendto(packet, (destAddr, 1))
	pkts_sent += 1 #increment number of packets sent
	
	# AF_INET address must be tuple, not str
	# Both LISTS and TUPLES consist of a number of objects
	# which can be referenced by their position number within the object.
	
def doOnePing(destAddr, timeout): 
	icmp = getprotobyname("icmp")
	# SOCK_RAW is a powerful socket type. For more details:   http://sock-raw.org/papers/sock_raw

	mySocket = socket(AF_INET, SOCK_RAW, icmp)
	
	myID = os.getpid() & 0xFFFF  # Return the current process i
	sendOnePing(mySocket, destAddr, myID)
	delay = receiveOnePing(mySocket, myID, timeout, destAddr)
	
	mySocket.close()
	return delay
	
def ping(host, timeout=1):
	# timeout=1 means: If one second goes by without a reply from the server,
	# the client assumes that either the client's ping or the server's pong is lost
	dest = gethostbyname(host)
	print("Pinging " + dest + " using Python:")
	print("")
	# Send ping requests to a server separated by approximately one second
	for i in range(0, 20) : #do 20 pings and print their RTTs
		delay = doOnePing(dest, timeout)
		if type(delay) is float: print(delay, "s")
		else: print(delay)
		time.sleep(1)# one second
	#print min, max, and avg RTTs, and packet loss rate
	print("\n")
	if len(RTT_list) > 0:
		print("Min RTT:", min(RTT_list), "s")
		print("Max RTT:", max(RTT_list), "s")
		print("Avg RTT:", sum(RTT_list)/len(RTT_list), "s")
	if pkts_sent > 0: print("Packet loss rate:", 100*(pkts_sent - pkts_rec)/pkts_sent, "%")
	return delay

#ping("localhost")
#ping("www.google.com")
#ping("www.brasil.gov.br")
#ping("www.ox.ac.uk")
#ping("www.thepaper.cn")
#ping("www.ust.hk")
