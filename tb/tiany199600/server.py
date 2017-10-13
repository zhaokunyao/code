#!/usr/bin/env python
#-*- coding: utf-8 -*-

 #
 # Licensed to the Apache Software Foundation (ASF) under one
 # or more contributor license agreements. See the NOTICE file
 # distributed with this work for additional information
 # regarding copyright ownership. The ASF licenses this file
 # to you under the Apache License, Version 2.0 (the
 # "License"); you may not use this file except in compliance
 # with the License. You may obtain a copy of the License at
 #
 #   http://www.apache.org/licenses/LICENSE-2.0
 #
 # Unless required by applicable law or agreed to in writing,
 # software distributed under the License is distributed on an
 # "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 # KIND, either express or implied. See the License for the
 # specific language governing permissions and limitations
 # under the License.
 #

import glob
import sys
#
# 下面这行代码把gen-py目录添加到path中。
# 这样后面import的时候就会在这个目录里面找文件
# gen-py目录是thrift根据kailee.thrift自动生成的。
# 它里面有一个kailee目录 ， kailee目录中有Sorter.py方法
# 这些都是thrift根据kailee.thrift文件自动生成的。
# 很巧合的是Sorter.py的文件名与kailee.thrift中的Service名称是一致的
#
sys.path.append('gen-py')
#sys.path.insert(0, glob.glob('../../lib/py/build/lib*')[0])

# 从gen-py/kailee 目录中加载Sorter.py文件
from kailee import Sorter
#from kailee.ttypes import InvalidOperation, Operation

#from shared.ttypes import SharedStruct

# 这些不用看， 是thrift提供的
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

class SorterHandler:
    """定义一个类
    """

    def __init__(self):
        """构造函数， 实例化的时候会被自动调用
        """
        self.log = {}

    def ping(self):
        """ping接口
        无返回值
        """
        # print 只是打印一些信息，  不会返回给client.
        print('ping()')

    def add(self, n1, n2):
        """add接口
        返回二个参数的和
        """
        print('add(%d,%d)' % (n1, n2))
        # 把和返回给client.
        return n1 + n2

    def sort_list(self, random_double_list): 
        """sort_list接口
        """
        print('random_double_list: ')
        #print random_double_list
        # 如果client发送过来的random_double_list长度不为100， 就抛出异常
        if len(random_double_list)  != 100:  
            raise Exception('length is not 100')

        # list排序
        random_double_list.sort()

        # 定义一个新数组
        result_list = list()
        # 从已排序的random_double_list中取第一个值（最小值）
        # 并保存到result_list中
        result_list.append(random_double_list[0])
        # 从已排序的random_double_list中取最后一个值（最大值）
        # 并保存到result_list中
        result_list.append(random_double_list[-1])
        #print 'result_list'
        #print result_list
        # 返回给client
        # result_list中其实就只有二个数字
        return result_list 

# 运行入口
if __name__ == '__main__':
    # 实例化上面定义的类
    handler = SorterHandler()
    # 下面这条是thirft生成的方法，我也不太清楚，从文档里面直接复制来的
    processor = Sorter.Processor(handler)
    # 定义一个socket，  server通过这个socket和client通信 
    transport = TSocket.TServerSocket(host='127.0.0.1', port=9090)
    # 下面这条是thirft生成的方法，我也不太清楚，从文档里面直接复制来的
    # 貌似是用来提升socket传输速度的
    tfactory = TTransport.TBufferedTransportFactory()
    # 下面这条是thirft生成的方法，我也不太清楚，从文档里面直接复制来的
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    # server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    # You could do one of these for a multithreaded server
    # server = TServer.TThreadedServer(
    #     processor, transport, tfactory, pfactory)
    # 定义一个多线程的server
    server = TServer.TThreadPoolServer(
        processor, transport, tfactory, pfactory)

    # 设置server线程数为 10000
    server.setNumThreads(10000)

    print('Starting the server...')
    # 开启server
    server.serve()
    print('done.')

