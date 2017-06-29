#!/usr/bin/env python  
  
from operator import itemgetter  
import sys  
  
current_id = None  
word = None  
  
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
        continue
    else:  
        print line
        current_id = ID  
  
