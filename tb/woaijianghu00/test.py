#-*- coding: utf-8 -*-
from pymongo import MongoClient
import json
import bson.json_util
from bson.json_util import dumps
client = MongoClient("mongodb://127.0.0.1:27017/cosyly")
db = client.cosyly
cursor = db.BaseStation.find({},{'_id':0})
print dumps(cursor)

""" 
所有base station内最早连接上来的4台mobile
"""
cursor = db.MobileData.find({}, {'_id': 0}, sort=[('timeofconnection', 1)], limit = 4)
print dumps(cursor)

""" 
每个base station内最早连接上来的mobile
http://api.mongodb.com/python/current/examples/aggregation.html
"""
pipeline = [
{"$group": {"_id": "$stationid", "time_of_connection": {"$min": "$timeofconnection"}}},
]
cursor = db.MobileData.aggregate(pipeline)
print dumps(cursor)

"""
每个城市内base station的数量 
"""
pipeline = [
{"$group": {"_id": "$location", "_count_": {"$sum": 1}}},
]
cursor = db.BaseStation.aggregate(pipeline)
print dumps(cursor)

"""
base station with max capacity
"""
cursor = db.MobileData.find({}, {'_id': 0}, sort=[('capacity', -1)], limit = 1)
print dumps(cursor)


""" 
每个城市在线的手机数量
"""


""" 
每个城市 在线手机量最大的base station
"""

