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
sys.path.append('gen-py')
#sys.path.insert(0, glob.glob('../../lib/py/build/lib*')[0])

from kailee import Sorter

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

import random


def main():
    # Make socket
    transport = TSocket.TSocket('localhost', 9090)

    # Buffering is critical. Raw sockets are very slow
    transport = TTransport.TBufferedTransport(transport)

    # Wrap in a protocol
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    # Create a client to use the protocol encoder
    client = Sorter.Client(protocol)

    # Connect!
    transport.open()

    #client.ping()
    #print('ping()')

    #sum_ = client.add(1, 1)
    #print('1+1=%d' % sum_)

    random_double_list = list()
    for i in xrange(0, 100): 
        random_double_list.append(round(random.uniform(-1000000, 1000000), 6))

    list_ = client.sort_list(random_double_list)
    if len(list_) != 2: 
        raise Exception('return list is not 2')
    print 'min: ' + str(list_[0])
    print 'max: ' + str(list_[1])


    # Close!
    transport.close()


import threading

class myThread (threading.Thread):

    def __init__(self):  
        threading.Thread.__init__(self)

    def run(self):  
        main()

def multi_thread_main():
    """1000 thread
    """
    threads = []
    for i in xrange(0, 1000): 
        t = myThread()
        t.start()
        threads.append(t)

    for t in threads: 
        t.join()

if __name__ == '__main__':
    try:
        # main()
        multi_thread_main()
    except Thrift.TException as tx:
        print('%s' % tx.message)

