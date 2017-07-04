#!/usr/bin/env python  
  
from operator import itemgetter  
import sys  
  
current_id = None  
arr     = list()
  
# input comes from STDIN  
for line in sys.stdin:  
    # remove leading and trailing whitespace  
    line = line.strip()  
  
    # parse the input we got from mapper.py  
    arrTmp = line.split(' ');
  
    # convert count (currently a string) to int  
    try:  
        ID = int(arrTmp[0])  
    except ValueError:  
        # count was not a number, so silently  
        # ignore/discard this line  
        continue  
  
    # this IF-switch only works because Hadoop sorts map output  
    # by key (here: word) before it is passed to the reducer  
    if current_id == ID:  
        arr.append(arrTmp[1])
    else:  
        if current_id is not None: 
            print """%s %s""" % (current_id, '_'.join(arr))
        current_id = ID  
        arr = list()
        arr.append(arrTmp[1])
  

print """%s %s""" % (current_id, '_'.join(arr))
