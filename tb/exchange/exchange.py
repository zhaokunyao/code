import socketserver
import threading
import time
import select
"""
This code is literally from Piazza, it just needs a few modification to send and recieve correctly
"""
SR_BYTES = 1024
current_price = None
side_to_send = None
is_finish = False
# For some more assistance, please look at this link
# https://www.technovelty.org/python/python-socketserver-class.html

class ExchangeReceiver(socketserver.BaseRequestHandler):
     """This Class Will Receive Messages"""
     def handle(self):
          while True:
               global current_price
               global side_to_send
               try:
                    ready_to_read, ready_to_write, in_error = select.select([self.request], [self.request], [], None)
                    
                    if is_finish: 
                        break
                    if len(ready_to_read) == 1 and ready_to_read[0] == self.request:
                        data = self.request.recv(1024)
                        current_price = float(data.decode('utf-8'))
                        #print("[ExchangeReceiver][receive]" + str(current_price))
                    if len(ready_to_write) == 1 and ready_to_write[0] == self.request: 
                        if side_to_send is not None: 
                            self.request.send(bytes(side_to_send, 'utf-8')) 
                            #print("[ExchangeReceiver][send]" + str(side_to_send))
                            side_to_send = None
               except Exception as error:
                    print("Issue with Exchange Recieve Error:{}".format(error))
                    break
          print("[ExchangeReceiver][close]")

class ExchangeSend(socketserver.BaseRequestHandler):

     def handle(self):
          global is_finish
          while True:
               global current_price
               global side_to_send
               try:
                   #You will have to implement a select like in the URL examle
                    ready_to_read, ready_to_write, in_error = select.select([self.request], [self.request], [], None)
                    
                   
                   #To check whether we need to recv or send data
                    if len(ready_to_read) == 1 and ready_to_read[0] == self.request:
                        data = self.request.recv(1024)
                        #Here you will do the opposite, receiving data will be the side
                        side_to_send = data.decode('utf-8')
                        if len(side_to_send) == 0: 
                            side_to_send = None
                            break
                        #print("[ExchangeSend][receive]" + str(side_to_send))
                    #sending data will be the price
                    #recall that you will ahve to cast from str to float for your price
                    if len(ready_to_write) == 1 and ready_to_write[0] == self.request: 
                        if current_price is not None: 
                            self.request.send(bytes(str(current_price), 'utf-8')) 
                            #print("[ExchangeSend][send]" + str(current_price))
                            current_price = None
               except Exception as error:
                    print("Issue with Exchange Send Error:{}".format(error))
                    break

          print("[ExchangeSend][close]")
          is_finish = True
