import socket
import time
import threading
import numpy as np

SENT_BYTES = 1024
LIST_LENGTH = 500

"""
Part of this code is literally from the slides
"""
HOST, PORT = "localhost", 9998

class Liquidity():
    def __init__(self):
        #call the random seed of 12345 of numpy
        np.random.seed(12345)
        #create a variable called self.__list_prices that calls the np.random that Sebastien mentioend
        self.__list_prices = list(np.random.uniform(low=12.5, high=14.5, size=(LIST_LENGTH,)))
        self.__balance = 0.0
        self.__cp = 0.0
        #Create a socket connection called self.__sock
        #call connect for HOST and PORT
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__sock.connect((HOST, PORT))


    def send(self):
         #Create a for loop that iterates through the prices in self.__list_prices
        print ("[Liquidity]start to send prices")
        while len(self.__list_prices) > 0:
             try:
                 price = float(self.__list_prices.pop(0))
                 b = bytes(str(price), 'utf-8')
                 #sent self.__cp to the price you just sent to keep track of the current price
                 self.__cp = price
                 #call teh sendall function of self.__sock and send the price
                 self.__sock.sendall(b)
                 #call sleep for the time asked in the pdf of the assignment
                 time.sleep(1)
                 #print("[Liquidity][send]" + str(price))
                 pass
             except Exception as error:
                 print("Issue with Sir Liquidity Error:{}".format(error))
                 break
        print("[Liquidity]Sent all prices, Closing........")

    def receive(self): 
        while True: 
            try:
                received = self.__sock.recv(1024)
                if received: 
                    #If data is received, Keep track of the balance for Sir Liquidity here
                    received = received.decode('utf-8')
                    if received == 'BUY': 
                        self.__balance  += self.__cp
                    else: 
                        self.__balance  -= self.__cp
                    #print the current balance of sir liquidity
                    #print ("[Liquidity][received]" + str(received))
                    print ("[Liquidity][receive]" + str(received) + " [balance]" + str(self.__balance))
                    #Then set receive to None
                    received = None
                else: 
                    break
            except Exception as error:
                print("Receive Error: {0}".format(error))
                break
        print("FINAL LIQUIDITY BALANCE: {}".format(self.__balance))
