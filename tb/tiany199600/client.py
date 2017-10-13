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

import sys
import glob
# 同server的注释
sys.path.append('gen-py')
#sys.path.insert(0, glob.glob('../../lib/py/build/lib*')[0])

# 同server的注释
from kailee import Sorter

# 同server的注释
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

# 加载随机类库
import random


def main():
    # 定义一个socket， client通过这个socket和server进行通信
    transport = TSocket.TSocket('localhost', 9090)

    # 下面这条是thirft生成的方法，我也不太清楚，从文档里面直接复制来的
    # 貌似是用来提升socket传输速度的
    transport = TTransport.TBufferedTransport(transport)

    # 下面这条是thirft生成的方法，我也不太清楚，从文档里面直接复制来的
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    # 实例化client类
    client = Sorter.Client(protocol)

    # 与server建立连接
    transport.open()

    #client.ping()
    #print('ping()')

    #sum_ = client.add(1, 1)
    #print('1+1=%d' % sum_)

    # 定义一个空的数组
    random_double_list = list()
    # 循环100次
    for i in xrange(0, 100): 
        # random.uniform是创建随机数字
        # round(, 6) 是把它四舍五入保留6位小数
        # 通过append方法把生成的随机数字保存到上面定义的数组中。
        random_double_list.append(round(random.uniform(-1000000, 1000000), 6))

    # 调用server的sort_list方法
    # 传入的是我们上面定义的数组
    # 虽然这里写的是client.sort_list ， 其实确定是调用的server中的sort_list方法
    # 并接收返回值保存到list_变量中
    list_ = client.sort_list(random_double_list)

    # 由于server返回的数组中只有二个字段，所以就判断一下数组长度是否为2
    # 不为2的话，就抛出异常
    if len(list_) != 2: 
        raise Exception('return list is not 2')

    # 打印调试信息
    print 'min: ' + str(list_[0])
    print 'max: ' + str(list_[1])


    # 关闭连接
    transport.close()


# 加载多线程类库
import threading

class myThread (threading.Thread):
    """ 定义一个线程class
    """

    def __init__(self):  
        """初始化
        """
        threading.Thread.__init__(self)

    def run(self):  
        """线程启动的时候会调用这个方法
        """
        # 下面是此线程实际执行的代码
        # 主要是与server建立连接，生成一个随机数组，调用server的sort_list方法，接收返回值并打印调试信息 
        main()

def multi_thread_main():
    """1000 thread
    """
    # 定义一个数组
    threads = []
    # 循环
    for i in xrange(0, 1000): 
        # 创建一个新线程
        t = myThread()
        # 线程启动并在后台运行(调用了myThread的run方法)
        t.start()
        # 把线程放入上面定义的数组中。
        threads.append(t)

    # 循环数组中的每一个线程
    for t in threads: 
        # 等待线程的代码运行完毕
        t.join()

# 入口
if __name__ == '__main__':
    try:
        # main()
        # 调用下面的方法并捕获异常
        multi_thread_main()
    except Thrift.TException as tx:
        print('%s' % tx.message)

