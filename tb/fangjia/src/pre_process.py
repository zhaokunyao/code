# -*- coding: utf-8 -*-

import json
import numpy as np
import pandas as pd
import sys

from sklearn import preprocessing
from scipy.sparse import hstack

from sklearn.naive_bayes import MultinomialNB
from sklearn.naive_bayes import BernoulliNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.linear_model import SGDClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.svm import SVC
from sklearn.svm import LinearSVC
from sklearn import tree

from sklearn.multiclass import OneVsRestClassifier
from sklearn.feature_selection import SelectKBest
from sklearn.feature_selection import chi2
from sklearn.datasets import load_svmlight_file
from sklearn import metrics
from sklearn import model_selection

class PreProcess(object): 
    """PreProcess
    """

    def __init__(self): 
        """__init__
        """
        self.strFileFeature = './data/feature'
        self.strFileY   = './data/y'
        self.arrY = []
        self.arrX = []

    def binY(self, arrYJson): 
        """binY
        """
        arrY = arrYJson.values()
        arrColumns = ['%']
        #print arrY[0]
        df = pd.DataFrame(arrY, columns=arrColumns)
        #print '-------------------describe y-----------------------'
        #print df.describe()
        """
        count  2948.000000
        mean    113.913127
        std      33.362162
        min      10.815914
        25%      99.673803
        50%     108.240933
        75%     120.378426
        max     878.777641
        """
        # 能否达到平均增幅
        arrBins = [
            113.913127, 1000000000
        ]

        arrYB = {}
        for (k, v) in arrYJson.items(): 
            i = -1
            for kk in arrBins: 
                i += 1
                if v <= kk: 
                    """
                    arrYB[k] = {
                        'o': v,
                        'n': i
                    }
                    """
                    arrYB[k] = i
                    break
        return arrYB

    def binX(self, arrFJson): 
        """binX
        """
        arrSpecialTags = set()
        arrWeakTags = set()
        for sid, item in arrFJson.items(): 
            key = u'物业费'
            if item[key].encode('utf-8') == '暂无数据': 
                item[key] = 1.9
            elif item[key] == '': 
                item[key] = 1.9
            else: 
                item[key] = float(item[key].encode('utf-8').replace('元/m²/月', ''))

            key = u'绿化率'
            if item[key].encode('utf-8') == '暂无数据': 
                item[key] = 32.4
            elif item[key] == '': 
                item[key] = 32.4
            else: 
                item[key] = float(item[key].encode('utf-8').replace('%', ''))

            key = u'总户数'
            if item[key].encode('utf-8') == '暂无数据': 
                item[key] = 1665
            elif item[key] == '': 
                item[key] = 1665
            else: 
                item[key] = float(item[key].encode('utf-8').replace('户', ''))

            key = u'容积率'
            if item[key].encode('utf-8') == '暂无数据': 
                item[key] = 2.1
            elif item[key] == '': 
                item[key] = 2.1
            else: 
                item[key] = float(item[key].encode('utf-8'))

            key = u'地址'
            item[key] = item[key].encode('utf-8').split(' ')[0]

            key = u'教育'
            try: 
                item[key] = int(item[key].encode('utf-8').replace('+', ''))
            except Exception as e: 
                item[key] = 6.4

            key = u'交通'
            try: 
                item[key] = int(item[key].encode('utf-8').replace('+', ''))
            except Exception as e: 
                item[key] = 50

            key = u'医院'
            try: 
                item[key] = int(item[key].encode('utf-8').replace('+', ''))
            except Exception as e: 
                item[key] = 8.5

            key = u'商业'
            try: 
                item[key] = int(item[key].encode('utf-8').replace('+', ''))
            except Exception as e: 
                item[key] = 92

            key = u'银行'
            try: 
                item[key] = int(item[key].encode('utf-8').replace('+', ''))
            except Exception as e: 
                item[key] = 72

            key = u'specTags'
            for node in item[key]: 
                tag = node[u'tagName'].encode('utf-8')
                arrSpecialTags.add(tag)

            key = u'weakTags'
            for node in item[key]: 
                tag = node[u'tagName'].encode('utf-8')
                arrWeakTags.add(tag)

        #print arrSpecialTags
        i = 0
        arrSpecialTagsMap = {}
        for item in arrSpecialTags: 
            arrSpecialTagsMap[item] = i
            i += 1

        #print arrWeakTags
        i = 0
        arrWeakTagsMap = {}
        for item in arrWeakTags: 
            arrWeakTagsMap[item] = i
            i += 1

        arrFL = list()
        for (k, v) in arrFJson.items(): 
            arrList = [
                v[u'物业类型'],
                v[u'物业费'],
                v[u'绿化率'],
                v[u'总户数'],
                v[u'容积率'],
                v[u'开发商'],
                v[u'物业公司'],
                v[u'地址'],
                v[u'教育'],
                v[u'交通'],
                v[u'医院'],
                v[u'商业'],
                v[u'银行'],
            ]
            arrFL.append(arrList)
        arrColumns = [
            'wuyeleixing',
            'wuyefei',
            'lvhualv',
            'zonghushu',
            'rongjilv',
            'kaifashang',
            'wuyegongsi',
            'dizhi',
            'jiaoyu',
            'jiaotong',
            'yiyuan',
            'shangye',
            'yinhang',
        ]
        df = pd.DataFrame(arrFL, columns=arrColumns)
        arrF  = {}
        print '------------------- describe 银行-------------------'
        print df[u'yinhang'].describe()
        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'银行']
            arrF[sid]['yinhang'] = v
        print '------------------- describe 商业-------------------'
        print df[u'shangye'].describe()
        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'商业']
            arrF[sid]['shangye'] = v
        print '------------------- describe 医院-------------------'
        print df[u'yiyuan'].describe()
        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'医院']
            arrF[sid]['yiyuan'] = v
        print '------------------- describe 交通-------------------'
        print df[u'jiaotong'].describe()
        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'交通']
            arrF[sid]['jiaotong'] = v
        print '------------------- describe 教育-------------------'
        print df[u'jiaoyu'].describe()
        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'教育']
            arrF[sid]['jiaoyu'] = v

        print '------------------- describe 地址-------------------'
        print df[u'dizhi'].describe()
        arrFSet = set()
        for sid, item in arrFJson.items(): 
            arrFSet.add(item[u'地址'])

        arrMap = {}
        i = 0
        for item in arrFSet: 
            i += 1
            arrMap[item] = i

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            key = item[u'地址']
            value = 0
            if key in arrMap: 
                value = arrMap[key]
            arrF[sid]['dizhi'] = value


        print '------------------- describe 物业公司-------------------'
        print df[u'wuyegongsi'].describe()

        arrFSet = set()
        for sid, item in arrFJson.items(): 
            arrFSet.add(item[u'物业公司'].encode('utf-8'))

        arrMap = {}
        i = 0
        for item in arrFSet: 
            i += 1
            arrMap[item] = i

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            key = item[u'物业公司'].encode('utf-8')
            value = 0
            if key in arrMap: 
                value = arrMap[key]
            arrF[sid]['wuyegongsi'] = value

        print '------------------- describe 开发商-------------------'
        print df[u'kaifashang'].describe()

        arrFSet = set()
        for sid, item in arrFJson.items(): 
            arrFSet.add(item[u'开发商'].encode('utf-8'))

        arrMap = {}
        i = 0
        for item in arrFSet: 
            i += 1
            arrMap[item] = i

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            key = item[u'开发商'].encode('utf-8')
            value = 0
            if key in arrMap: 
                value = arrMap[key]
            arrF[sid]['kaifashang'] = value

        print '------------------- describe 容积率-------------------'
        print df[u'rongjilv'].describe()

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'容积率']
            arrF[sid]['rongjilv'] = v

        print '------------------- describe 总户数-------------------'
        print df[u'zonghushu'].describe()

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'总户数']
            arrF[sid]['zonghushu'] = v

        print '------------------- describe 绿化率-------------------'
        print df[u'lvhualv'].describe()

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'绿化率']
            arrF[sid]['lvhualv'] = v

        print '------------------- describe 物业费-------------------'
        print df[u'wuyefei'].describe()

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            v = item[u'物业费']
            arrF[sid]['wuyefei'] = v

        print '------------------- describe 物业类型-------------------'
        print df[u'wuyeleixing'].describe()

        arrFSet = set()
        for sid, item in arrFJson.items(): 
            arrFSet.add(item[u'物业类型'].encode('utf-8'))

        arrMap = {}
        i = 0
        for item in arrFSet: 
            i += 1
            arrMap[item] = i

        for sid, item in arrFJson.items(): 
            if sid not in arrF: 
                arrF[sid] = dict()
            key = item[u'物业类型'].encode('utf-8')
            value = 0
            if key in arrMap: 
                value = arrMap[key]
            arrF[sid]['wuyeleixing'] = value

        arrFTag1 = {}
        arrFTag2 = {}

        for sid, item in arrFJson.items(): 
            if sid not in arrFTag1: 
                arrFTag1[sid] = []
                key = u'specTags'
                arrTagMap = {}
                for node in item[key]: 
                    tag = node[u'tagName'].encode('utf-8')
                    arrTagMap[tag] = 1
                for k,v in arrSpecialTagsMap.items(): 
                    if k in arrTagMap: 
                        arrFTag1[sid].append(1)
                    else: 
                        arrFTag1[sid].append(0)

        for sid, item in arrFJson.items(): 
            if sid not in arrFTag2: 
                arrFTag2[sid] = []
                key = u'weakTags'
                arrTagMap = {}
                for node in item[key]: 
                    tag = node[u'tagName'].encode('utf-8')
                    arrTagMap[tag] = 1
                for k,v in arrWeakTagsMap.items(): 
                    arrFTag2[sid].append(0)
                    if k in arrTagMap: 
                        arrFTag2[sid].append(1)
                    else: 
                        arrFTag2[sid].append(0)

        return arrF, arrFTag1, arrFTag2, len(arrSpecialTagsMap), len(arrWeakTagsMap)


    def go(self): 
        """go
        """
        arrFJson    = json.load(open(self.strFileFeature))
        arrYJson    = json.load(open(self.strFileY))
        arrY = self.binY(arrYJson)
        arrF, arrFTag1, arrFTag2, len_tag1, len_tag2 = self.binX(arrFJson)

        arrColumns = [
            'wuyeleixing',
            'wuyefei',
            'lvhualv',
            'zonghushu',
            'rongjilv',
            'kaifashang',
            'wuyegongsi',
            'dizhi',
            'jiaoyu',
            'jiaotong',
            'yiyuan',
            'shangye',
            'yinhang',
        ]
        for sid, y in arrY.items(): 
            if sid not in arrF: 
                continue
            f = arrF[sid]
            self.arrY.append(y)
            ftag1 = [.0] * len_tag1
            ftag2 = [.0] * len_tag2
            if sid in  arrFTag1: 
                ftag1 = arrFTag1[sid]
            if sid in arrFTag2: 
                ftag2 = arrFTag2[sid]
            f2 = []
            for col in arrColumns: 
                f2.append(f[col])

            # 组合f2与ftag1与ftag2
            f = f2 + ftag1 + ftag2
            self.arrX.append(f)

        self.output()

    def output(self): 
        """output
        """

        #self.arrX = preprocessing.scale(np.array(self.arrX))

        arrXTrain, arrXTest, arrYTrain, arrYTest = \
                model_selection.train_test_split(
                        self.arrX, self.arrY, test_size=0.25)
        with open('./data/train.svm', 'w') as f: 
            i = 0
            for item in arrYTrain: 
                arrVector = []
                arrVector.append(str(item))
                j = 0
                for col in arrXTrain[i]: 
                    arrVector.append('%s:%s' % (j, col))
                    j += 1
                line = ' '.join(arrVector)
                f.write(line + '\n')
                i += 1

        with open('./data/test.svm', 'w') as f: 
            i = 0
            for item in arrYTest: 
                arrVector = []
                arrVector.append(str(item))
                j = 0
                for col in arrXTest[i]: 
                    arrVector.append('%s:%s' % (j, col))
                    j += 1
                line = ' '.join(arrVector)
                f.write(line + '\n')
                i += 1

if __name__ == '__main__': 
    o = PreProcess()
    o.go()
