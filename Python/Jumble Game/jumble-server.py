
import random
import time, _thread as thread           # or use threading.Thread().start()
from socket import *                     # get socket constructor and constants
myHost = ''                              # server machine, '' means local host
myPort = 50007                           # listen on a non-reserved port number

sockobj = socket(AF_INET, SOCK_STREAM)          # make a TCP socket object
sockobj.bind((myHost, myPort))                  # bind it to server port number
sockobj.listen(5)                               # allow up to 5 pending connects

F = open('wordlist.txt')                        # open file wordlist.txt
words = F.readlines()                           # convert to list of word strings
F.close()                                       # close the file

def now():
    return time.ctime(time.time())              # current time on the server

def handleClient(connection):                   # in spawned thread: server_output
    time = 'Connected at ' + now()                 # date and time of connection 
    connection.send(time.encode())              # encode and send time to client
    while True:                                 # read, write a client socket
        word = words[random.randrange(len(words))]          # obtain a random word at a random index from words list
        while len(word) > 5 or len(word) == 0:              # while length of word is > 5 or == 0 
            word = words[random.randrange(0, len(words))]   # obtain new word
        word = word.rstrip()                                # remove whitespaces
        old_word = word                                     # store word in old_word
        word = list(word)                                   # convert word string to char list
        jumbled_word = ''                                   # string to store the jumbled letters
        while word:                                         # while there are characters in the list
            jumbled_word = jumbled_word + word.pop(random.randrange(len(word))) # pop a char at a random index and append it to jumbled_word
            jumbled_word = jumbled_word + ' '                                   # append a whitespace to jumbled_word
        connection.send(jumbled_word.encode())              # encode and send jumbled letters to client
        
        client_input = connection.recv(1024)                # receive client answer
        if not client_input: break                          # if client provides no input, break this loop
    
        match_word = client_input.decode()                          # decode client input 
        new_word = match_word + '\n'                                # append newline to input
        if new_word in words and set(match_word) == set(old_word):  # if client input is correct
            server_output = 'You win.'                              # output of server is 'You win.'
        else:                                                       # otherwise
            server_output = 'The answer is ' + old_word             # output of server is the correct word

        connection.send(server_output.encode())                     # encode and send output of server to client
    connection.close()                                              # close connection

def dispatcher():                                # listen until process killed
    while True:                                  # wait for next connection,
        connection, address = sockobj.accept()   # pass to thread for service
        print('Server connected by', address, end=' ')          # print address of connected client
        print('at', now())                                      # print date and time of connection
        thread.start_new_thread(handleClient, (connection,))    # start new threads to handle multiple clients

dispatcher()
