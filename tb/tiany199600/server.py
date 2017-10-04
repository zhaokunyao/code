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
sys.path.append('gen-py')
#sys.path.insert(0, glob.glob('../../lib/py/build/lib*')[0])

from kailee import Sorter
#from kailee.ttypes import InvalidOperation, Operation

#from shared.ttypes import SharedStruct

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

class SorterHandler:
    def __init__(self):
        self.log = {}

    def ping(self):
        print('ping()')

    def add(self, n1, n2):
        print('add(%d,%d)' % (n1, n2))
        return n1 + n2

    def sort_list(self, random_double_list): 
        print('random_double_list: ')
        #print random_double_list
        if len(random_double_list)  != 100:  
            raise Exception('length is not 100')
        random_double_list.sort()
        result_list = list()
        result_list.append(random_double_list[0])
        result_list.append(random_double_list[-1])
        #print 'result_list'
        #print result_list
        return result_list 

if __name__ == '__main__':
    handler = SorterHandler()
    processor = Sorter.Processor(handler)
    transport = TSocket.TServerSocket(host='127.0.0.1', port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    # server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    # You could do one of these for a multithreaded server
    # server = TServer.TThreadedServer(
    #     processor, transport, tfactory, pfactory)
    server = TServer.TThreadPoolServer(
        processor, transport, tfactory, pfactory)
    server.setNumThreads(10000)

    print('Starting the server...')
    server.serve()
    print('done.')

