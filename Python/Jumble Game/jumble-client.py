
import sys
from socket import *              # portable socket interface plus constants
serverHost = 'localhost'          # server name, or: 'starship.python.net'
serverPort = 50007                # non-reserved port used by the server

sockobj = socket(AF_INET, SOCK_STREAM)      # make a TCP/IP socket object
sockobj.connect((serverHost, serverPort))   # connect to server machine + port

time = sockobj.recv(1024)                   # receive time of connection from server
print(time.decode() + '\n')                 # decode and print

while True:
    jumbled_word = sockobj.recv(1024)       # receive the jumbled word string from server
    print(jumbled_word.decode())            # decode and print it to client
    print('Type your answer') 
    client_input = input()                  # take client input from command line
    if not client_input: break              # if client provides no input, break this loop
    sockobj.send(client_input.encode())     # encode and send input to server over socket
    server_output = sockobj.recv(1024)      # receive output from server
    print(server_output.decode() + '\n')    # decode and print it to client

sockobj.close()                             # close socket to send eof to server
