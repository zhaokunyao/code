#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""蓄水池
"""

import sys
import random

SAMPLE_COUNT = 1000

arrSample   = list()
filename    = sys.argv[1]

for  index, line in enumerate(open(filename)): 
    if index < SAMPLE_COUNT: 
        arrSample.append(line)
    else: 
        r = random.randint(0, index)
        if r < SAMPLE_COUNT: 
            arrSample[r]    = line

for line in arrSample: 
    print line.strip()
