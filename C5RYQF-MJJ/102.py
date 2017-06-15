import sys
import re

def solution(file_object):

    
    while 1: 
        line = file_object.readline()

        if not line:
            break
        line = line.strip()

        m   = re.match(r'^([+\-]?\d+)$', line)

        if m: 
            number = int(m.group(1))
        else:
            continue

        if number >1000000000 or number < -1000000000: 
            continue
        yield number


file_object = open("foo.txt")
for i in solution(file_object):
    print i

