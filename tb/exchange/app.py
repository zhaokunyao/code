"""
python3 -m pip install numpy
"""
import socketserver
import threading
import exchange
import liquidity
import long
import sys


def main():
    HOST_LONG, PORT_LONG = "localhost", 9999
    HOST_LIQUIDITY, PORT_LIQUIDITY = "localhost", 9998
    mr_long = socketserver.TCPServer((HOST_LONG, PORT_LONG), exchange.ExchangeSend)
    long_thread = threading.Thread(target=mr_long.serve_forever)
    long_thread.start()
    #Create a TCP Connection for SIR LIQUIDITY calling the exchange's ExchangeReceiver, call the variable sirliq
    sirliq = socketserver.TCPServer((HOST_LIQUIDITY, PORT_LIQUIDITY), exchange.ExchangeReceiver)
    #Create a thread for the TCPServer you called sirliq and call the serve_forever command as your target, call the variable liq_thread
    liq_thread = threading.Thread(target=sirliq.serve_forever)
    #Call start function for liq_thread
    liq_thread.start()
    #Create a variable call mrlong that calls the Long class
    mrlong = long.Long()
    #Create a variable receiving that create a thread whose target calls variable's mrlong's  recieve function
    receiving   = threading.Thread(target=mrlong.receive)
    #Call start function for receiving variable
    # mrlong  first receive, then send.
    receiving.start()

    liq = liquidity.Liquidity()
    sending = threading.Thread(target=liq.send)
    liquid_receive = threading.Thread(target=liq.receive)
    # liquid send and receive.
    sending.start()
    liquid_receive.start()

    # wait for them to end
    receiving.join()
    sending.join()
    liquid_receive.join()
    mr_long.shutdown()
    sirliq.shutdown()

if __name__ == "__main__":
    main()
