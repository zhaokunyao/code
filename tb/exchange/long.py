import os
import socket
import numpy

"""
Part of this code is literally from the slides
"""

HOST, PORT = "localhost", 9999
LIST_LENGTH = 500

class Long():
    def __init__(self):
        self.__balance = 0.0
        self.__current_price = 0.0
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__sock.connect((HOST, PORT))
        self.__prev_ma = 0.0
        self.__increase = 0
        self.__ma_list = []
        self.__is_buy = False
        self.__ma_period = 10
        self.__price_received_count  = 0

    def send(self, current_side):
            try:
                #UPDATE the balance equation here, if buy then -1 else 1 * the self.__current_price
                if current_side == 'BUY': 
                    self.__balance -= self.__current_price
                else: 
                    self.__balance += self.__current_price

                #THEN send current side
                b = bytes(current_side, 'utf-8')
                self.__sock.sendall(b)
                print ("[Long][send]" + current_side + " [balance]" + str(self.__balance))
                pass
            except Exception as error:
                print("Issue with Mr. Long Error:{}".format(error))

    def receive(self):
        while self.__price_received_count < LIST_LENGTH: 
            try:
                #GRAB PRICE FROM THE SOCKET and save in variable price
                price = self.__sock.recv(1024).decode('utf-8')
                #print("[Long][receive]" + str(price))
                self.__price_received_count += 1
                if price:
                    #convert string price to float and pass in the variable price and self.__ma_period
                    price = float(price)
                    self.__ma_list.append(price)
                    #to the moving_average function, make sure to assign a variable to the moving average that is returned
                    ma = self.moving_average()
                    if price < self.__current_price and self.__is_buy:
                        #make sure to sent self.__is_buy to Fals
                        self.__prev_ma = 0.0
                        self.__increase = 0
                        self.__is_buy = False
                        self.__current_price = price
                        #call send function and send a sell
                        self.send('SELL')
                    else:
                        #the moving average variable you have pass it in with the price to check_increase
                        # When Mr Long already sends a “BUY” he cannot sends another “BUY”
                        if not self.__is_buy: 
                            self.check_increase(ma, price)
                        pass
                    self.__current_price = price
            except Exception as error:
                print("LONG Receive Error: {0}".format(error))
                break
        self.__sock.close()
        print("FINAL LONG BALANCE: {}".format(self.__balance))

    def moving_average(self): 
        #create the moving average function
        if len(self.__ma_list) > self.__ma_period: 
            offset = len(self.__ma_list) - self.__ma_period
            self.__ma_list = self.__ma_list[offset:]
        ma = numpy.mean(self.__ma_list)
        return ma

    def check_increase(self, ma, price): 
        self.__current_price = price
        #current moving average is store in the variable ma
        if ma:
            #write code that check if there is an increase in the ma average
            #self.__prev_ma hold the previous moving average, so you can compare to the moving average
            #if there is an increase the have self.__increase increase by 1
            #Then set the prev_ma variblae to be ma
            if ma > self.__prev_ma: 
                self.__increase +=1 
                self.__prev_ma = ma
            # equal ... treat as decrease
            elif ma == self.__prev_ma: 
                self.__increase = 0
                self.__prev_ma = ma
            #else if there is a decrease reset self.__increase variable to 0 and set prev_ma to ma
            else: 
                self.__increase = 0
                self.__prev_ma = ma
            
            #Thsi is finished for you here
            if self.__increase == 3:
                self.__prev_ma = 0.0
                self.__increase = 0
                self.__is_buy = True
                self.send("BUY")
