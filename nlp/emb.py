
# -*- coding: UTF-8 -*- 

import numpy as np
import cPickle as pickle
import os
import sys
import operator



f = open("word_dict.pkl")
wd = pickle.load(f)
#print len(wd)

arr_dict = dict()
index = -1
for (k, v) in wd.items(): 
    uk = k.encode("utf-8")
    if uk == "计算机": 
        index = v
    arr_dict[v] = uk

if index == -1: 
    sys.exit(0)
print index
emb = np.load("emb.npy")
emb_guowang = emb[index]

arr_dis = dict()
i   = 0
for obj in emb: 
    dis = 0
    j = 0
    for v in obj: 
        dis += (v - emb_guowang[j]) * (v - emb_guowang[j])
        j += 1
    arr_dis[i] = dis
    i += 1

arr_sorted_dis = sorted(arr_dis.items(), key=operator.itemgetter(1))
arr_sorted_dis = arr_sorted_dis[0:10]



for obj in arr_sorted_dis: 
    k = obj[0]
    v = obj[1]
    print "%s, %s, %s" % (k, v, arr_dict[k])

