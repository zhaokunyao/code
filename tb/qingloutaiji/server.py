#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
pip install flask

python server.py 启动
ctrl  c 结束运行
或者是ps aux|grep server.py   然后kill 进程号
"""

from flask import Flask
import threading
import urllib2
import random
import socket
import time
import sys
import logging
#from logging.handlers import RotatingFileHandler

# 加载Flask框架
app = Flask(__name__)

logger = logging.getLogger('werkzeug')
handler = logging.FileHandler('server.log')
logger.addHandler(handler)
app.logger.addHandler(handler)

logging.basicConfig(filename='error.log',level=logging.DEBUG)


class Client(threading.Thread): 
    """Client类
    """
    def __init__(self): 
        """ 初始化
        """

        # 多线程
        threading.Thread.__init__(self)

        # 日志
        self.logger = logging.getLogger('client')
        handler = logging.FileHandler('client.log')
        formatter = logging.Formatter(
                '%(asctime)s %(name)-12s %(levelname)-8s %(message)s')
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)
        self.logger.setLevel(logging.DEBUG)

        self.logger.debug('[client] start')


        # 全部节点ip
        self.servers = [
            'localhost',
            '127.0.0.1',
        ]

        # 排除自己的ip
        try: 
            self.servers.remove('localhost')
        except Exception as e: 
            pass

        try: 
            self.servers.remove(self.get_host_ip())
        except Exception as e: 
            pass

        self.logger.debug('server list: ')
        self.logger.debug(self.servers)

        # server是否已经结束了
        self.is_server_close = False

    def get_host_ip(self):
        """获取本机ip地址
        """
        ip = ""
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            s.connect(('8.8.8.8', 80))
            ip = s.getsockname()[0]
            self.logger.debug('[client] local ip is: ' + ip)
            s.close()
        except Exception as e: 
            self.logger.debug("[client] error while get local ip: ")
            self.logger.debug(e)

        return ip

    def run(self): 
        """入口
        """
        while True: 
            # 接收用户输入
            # print 'please input msg: '
            msg = raw_input('please input msg: ')

            # 如果server已经结束了, client也退出
            if self.is_server_close: 
                return

            # 遍历全部节点
            for server in self.servers: 
                # 构造 http 请求
                url =  'http://' + server + ":5000/?msg=" + msg

                self.logger.debug("sending msg to: " + url)
                try: 
                    urllib2.urlopen(url).read(10000)
                except Exception as e: 
                    debug_msg = '[client] error while sending msg: '
                    self.logger.debug(debug_msg)
                    self.logger.debug(url)
                    self.logger.debug(e)


class Server(object): 
    """Server类
    """

    def __init__(self): 
        """初始化
        """

        # client
        self.c = None

        app.logger.debug('server start')


    @app.route('/')
    def hello_world():
        """接收client的http请求
        """
        return 'Hello World!'

    def go(self): 
        """入口
        """
        # 启动client
        self.startClient();
        # 启动server(flask)
        app.debug = False
        app.run()
        # server 结束
        #self.logger.debug('[server] end')
        app.logger.debug('server end')
        self.c.is_server_close = True
        # 等待client结束
        self.c.join()

    def startClient(self): 
        """startClient
        """
        self.c = Client()
        self.c.start()

if __name__ == "__main__": 
    o = Server()
    o.go()
