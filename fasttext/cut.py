#encoding=utf8
"""
merge and mount.
"""
import sys
import jieba
import math

# 词典
jieba.set_dictionary('./dict.txt.big')
jieba.initialize()
arrStopwords = set()

# 停用词
with open('./stopwords') as f: 
    for line in f: 
        arrStopwords.add(line.strip())


def cut(name): 
    """cut and filt
    """
    arrTokens = jieba.lcut(name)
    arrRet = []
    for token in arrTokens: 
        token = token.encode('utf-8')
        if token not in arrStopwords: 
            arrRet.append(token)
    return arrRet

arrContents = list()
with open("./article") as f: 
    for line in f: 
        line = line.strip()
        if len(line) == 0: 
            continue
        arrTokens = cut(line)
        arrContents.append(arrTokens)

with open('./data.txt', 'w') as f: 
    for arrTokens in arrContents: 
        line = '\t'.join(arrTokens)
        #line += '\n'
        f.write(line)
