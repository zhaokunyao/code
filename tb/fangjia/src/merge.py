# -*- coding: utf-8 -*-

import sys
import re
import json


def mergeF(): 
    arrF = {}
    prog = {
        '物业类型': re.compile(u'.*物业类型：</i>([^<]+)</span>'),
        '物业费': re.compile(u'.*物业费：</i>([^<]+)</span>'),
        '竣工时间': re.compile(u'.*竣工时间：</i>([^<]+)</span>'),
        '绿化率': re.compile(u'.*绿化率：</i>([^<]+)</span>'),
        '总户数': re.compile(u'.*总&nbsp;&nbsp;户&nbsp;&nbsp;数：</i>([^<]+)</span>'),
        '容积率': re.compile(u'.*容积率：</i>([^<]+)</span>'),
        '开发商': re.compile(u'.*<dt>开\&nbsp;\&nbsp;发\&nbsp;\&nbsp;商：</dt>[^<]+<dd>([^<]+)</dd>', re.DOTALL),
        '物业公司': re.compile(u'.*<dt>物业公司：</dt>[^<]+<dd>([^<]+)</dd>', re.DOTALL),
        '地址': re.compile(u'<p>地址：([^<]+)</p>'),
        '教育': re.compile(u'<p>教育\(([^\)]+)\)</p>'),
        '交通': re.compile(u'<p>交通\(([^\)]+)\)</p>'),
        '医院': re.compile(u'<p>医院\(([^\)]+)\)</p>'),
        '商业': re.compile(u'<p>商业\(([^\)]+)+\)</p>'),
        '银行': re.compile(u'<p>银行\(([^\)]+)\)</p>'),
    }

    arrInit = {
        'specTags': [],
        'weakTags': [],
        '物业类型': '',
        '物业费': '',
        '竣工时间': '',
        '绿化率': '',
        '总户数': '',
        '容积率': '',
        '开发商': '',
        '物业公司': '',
        '地址': '',
        '教育': '',
        '交通': '',
        '医院': '',
        '商业': '',
        '银行': '',
    }

    with open('./map.tag') as f: 
        for line in f: 
            line = line.strip()
            arrTmp = line.split(' ')
            file_name = 'data/' + arrTmp[0]
            url = arrTmp[1]
            arrTmp = url.split('=')
            sid = arrTmp[1]
            strJson = open(file_name, 'r').read(100000)
            if sid not in arrF: 
                arrF[sid] = arrInit.copy()
            try: 
                arrJson = json.loads(strJson)
                arrF[sid]['specTags'] = arrJson[u'data'][u'specTags']
                arrF[sid]['weakTags'] = arrJson[u'data'][u'weakTags']
            except Exception as e: 
                print 'tag exception: '
                print file_name
                continue

    with open('./map.feature') as f: 
        for line in f: 
            line = line.strip()
            arrTmp = line.split(' ')
            file_name = 'data/' + arrTmp[0]
            url = arrTmp[1]
            arrTmp = url.split('/')
            sid = arrTmp[3]
            arrLines = open(file_name, 'r').readlines()
            if sid not in arrF: 
                arrF[sid] = arrInit

            for line in arrLines: 
                line = line.strip()
                line = line.decode('utf-8')
                for (k, v) in prog.items(): 
                    arrGroups = v.match(line)
                    if not arrGroups: 
                        continue
                    arrF[sid][k] = arrGroups.group(1).encode('utf-8')
                    #print k, arrGroups.group(1).encode('utf-8')

            strHtml = open(file_name, 'r').read(1000000).decode('utf-8')
            key = '开发商'
            arrGroups = prog[key].match(strHtml)
            if arrGroups: 
                arrF[sid][key] = arrGroups.group(1).encode('utf-8')
                #print arrGroups.group(1).encode('utf-8')
            key = '物业公司'
            arrGroups = prog[key].match(strHtml)
            if arrGroups: 
                arrF[sid][key] = arrGroups.group(1).encode('utf-8')
                #print arrGroups.group(1).encode('utf-8')


    with open('./feature', 'w') as f: 
        f.write(json.dumps(arrF))

    for (k, v) in arrF['211369'].items(): 
        print k
        print v
    print 'length feature: ', len(arrF)

def mergeY(): 

    arrY = {}
    prog = re.compile(r'^(\{[^\}]+block[^\}]+comm[^\}]+\})')
    strKey = u'\u52a0\u5dde\u6c34\u90e1(\u897f\u533a)--comm'
    with open('./map.y') as f: 
        for line in f: 
            line = line.strip()
            arrTmp = line.split(' ')
            file_name = 'data/' + arrTmp[0]
            url = arrTmp[1]
            arrTmp = url.split('/')
            sid = arrTmp[4]
            arrLines = open(file_name, 'r').readlines()
            arrJson = {}
            for line in arrLines: 
                line = line.strip()
                arrGroups = prog.match(line)
                if not arrGroups: 
                    continue
                strJson = arrGroups.group(1)
                arrJson = json.loads(strJson)
                '''
                if strKey not in arrJson: 
                    continue
                '''

            # print arrJson
            has_price = False
            for (k, v) in arrJson.items(): 
                if k[-4:] == 'comm': 
                    arrPrices = v
                    # print arrPrices
                    try: 
                        floatRatio = 100 * arrPrices[-1] / arrPrices[0] 
                    except Exception as e: 
                        print 'price exception: '
                        print file_name 
                    # print floatRatio

                    arrY[sid] = floatRatio
                    has_price = True
                    break

            if not has_price: 
                print file_name

    with open('./y', 'w') as f: 
        f.write(json.dumps(arrY))

    print 'length: Y : ', len(arrY)
    print arrY['211369']

mergeF()
mergeY()
