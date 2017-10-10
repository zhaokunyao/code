#!usr/bin/env python
#-*- coding: utf-8 -*-

"""2BaseStationSimulator(25%)
"""
import random
import time

class BaseStation(object): 
    """BaseStation. bs
    """
    def __init__(self, ID, street, city, country, capacity): 
        """__init__
        """
        self.ID = ID
        self.street = street
        self.city = city
        self.country = country
        self.capacity = capacity
        self.start_time = 0
        self.records = dict()
        print """[bs] created. ID: [%s] street: [%s] city: [%s] country: [%s] capacity: [%s]""" % (
            self.ID,
            self.street,
            self.city,
            self.country,
            self.capacity
        )

    def startup(self): 
        """startup
        """
        self.start_time = int(time.time())
        print """[bs] ID: [%s] start at [%s] """ % (self.ID, self.start_time)

        print """[bs] ID: [%s] inform data processor i have started""" % (self.ID)

    def connect(self, phone): 
        """ connect
        """
        print """[bs] ID: [%s] phone [%s] is connecting""" % (self.ID, phone)
        if len(self.records) >= self.capacity: 
            print """[bs] ID: [%s] phone [%s] is connecting, but bs reach capacity [%s]""" % (
                self.ID, phone, self.capacity)
            return False

        self.records[phone] = int(time.time())
        print """[bs] ID: [%s] phone [%s] have connected""" % (self.ID, phone)
        print """[bs] ID: [%s] inform data processor [%s] have connected""" % (self.ID, phone)
        return True

    def disconnect(self, phone): 
        """ disconnect
        """
        if phone in self.records: 
            del(self.records[phone])
        print """[bs] ID: [%s] phone [%s] have disconnected""" % (self.ID, phone)
        print """[bs] ID: [%s] inform data processor [%s] have disconnected""" % (self.ID, phone)

    def receiveMsg(self, phone, msg): 
        """receiveMsg
        """
        print """[bs] ID: [%s] receiveMsg: [%s] from phone: [%s]""" % (self.ID, msg, phone)

    def dump(self): 
        """dump self
        """
        print '--------------------------------------'
        print "ID: " + str(self.ID)
        print "street: " + self.street
        print "city: " + self.city
        print "country: " + self.country
        print "capacity: " + str(self.capacity)
        print "start_time" + str(self.start_time)
        print "records: "
        print self.records
        print '--------------------------------------'

class Phone(object): 
    """Phone
    """
    def __init__(self, phone): 
        """__init__
        """
        self.phone = phone
        self.is_connected = False
        self.msg = ""
        self.bs  = None
        print "[phone] [%s] is created" % (self.phone)

    def connect(self, bs): 
        """connect to bs
        """
        self.bs = bs
        print "[phone] [%s] connecting to bs id: [%s]" % (self.phone, self.bs.ID)
        ret = self.bs.connect(self.phone)
        if ret: 
            print "[phone] [%s] connecting to bs id: [%s] . OK" % (self.phone, self.bs.ID)
            self.is_connected = True
        else: 
            print "[phone] [%s] connecting to bs id: [%s] . FAILED" % (self.phone, self.bs.ID)
            self.is_connected = False

    def disconnect(self): 
        """disconnect from bs
        """
        print "[phone] [%s] disconnecting from bs id: [%s]" % (self.phone, self.bs.ID)
        self.bs.disconnect(self.phone)
        self.is_connected = False

    def sendMsg(self, msg): 
        """send msg to bs
        """
        self.msg = msg
        print "[phone] [%s] sending msg [%s] to bs id: [%s]" % (self.phone, self.msg, self.bs.ID)
        self.bs.receiveMsg(self.phone, self.msg)

    def dump(self): 
        """dump
        """
        if self.is_connected: 
            print "[phone] [%s] connected to bs id: [%s]" % (self.phone, self.bs.ID)
        else: 
            print "[phone] [%s] is not connected"

class BaseStationSimulator(object): 
    """BaseStationSimulator
    """

    def __init__(self): 
        """__init__
        """
        self.bs = list()
        self.phones = list()

    def startBs(self): 
        """ start all bs.
        """
        print '[simulator] starting bs'
        capacity = 4
        o = BaseStation(0, 'Kingfisher Way', 'Loughborough', 'England', capacity)
        o.startup()
        self.bs.append(o)
        time.sleep(int(random.random() * 4))

        o = BaseStation(1, 'Village Court O/C', 'Loughborough', 'England', capacity)
        o.startup()
        self.bs.append(o)
        time.sleep(int(random.random() * 4))

        o = BaseStation(2, 'Filbert Way', 'Leicester', 'England', capacity)
        o.startup()
        self.bs.append(o)
        time.sleep(int(random.random() * 4))

        o = BaseStation(3, 'Sir Matt Busby Way', 'Manchester', 'England', capacity)
        o.startup()
        self.bs.append(o)
        time.sleep(int(random.random() * 4))

        o = BaseStation(4, '9 Birmingham Rd', 'West Bromwich', 'England', capacity)
        o.startup()
        self.bs.append(o)
        time.sleep(int(random.random() * 4))
        print '[simulator] starting bs. ok'

    def randomPhone(self): 
        """create random phone number
        """
        vocabulary = [1,2,3,4,5,6,7,8,9]
        return ''.join(str(i) for i in random.sample(vocabulary, len(vocabulary)))

    def createPhones(self): 
        """createPhones
        """
        print '[simulator] create Phones'
        for i in xrange(0, 20): 
            p = self.randomPhone()
            o = Phone(p)
            self.phones.append(o)

        print '[simulator] create %s Phones ok.' % (len(self.phones))

    def dumpBs(self): 
        """dumpBs
        """
        print 'dump bs'
        for o in self.bs: 
            o.dump()

    def dumpPhone(self): 
        """dumpPhone
        """
        print 'dump phone'
        print '====================================='
        for o in self.phones: 
            o.dump()
        print '====================================='

    def go(self): 
        """go
        """
        self.startBs()
        self.createPhones()
        i = 0
        while True: 
            self.phones = random.sample(self.phones, len(self.phones))
            for p in self.phones: 
                i += 1
                if i % 10 == 0: 
                    self.dumpBs()
                    self.dumpPhone()
                time.sleep(int(random.random() * 10))
                if random.random() > 0.5: 
                    continue

                if p.is_connected: 
                    p.disconnect()
                else: 
                    bs_index = int(random.random() * len(self.bs))
                    if bs_index == len(self.bs): 
                        bs_index = 0
                    p.connect(self.bs[bs_index])
                    p.sendMsg('hello')

if __name__ == "__main__": 
    o = BaseStationSimulator()
    try: 
        o.go()
    except Exception as e: 
        print e
