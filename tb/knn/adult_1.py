# -*- coding: UTF-8 -*-
'''
kNN: k Nearest Neighbors

pip install pandas
pip install sklearn

Input:      inX: vector to compare to existing dataset (1xN)
            dataSet: size m data set of known vectors (NxM)
            labels: data set labels (1xM vector)
            k: number of neighbors to use for comparison (should be an odd number)

Output:     the most popular class label

'''
from numpy import *
import operator
from os import listdir
from pandas import DataFrame
from scipy.stats import mode

def filematrix(filename):        ######从文本文件中解析数据（python 擅长处理文本文件）生成特征矩阵########
    fr = open(filename)
    arrayline=fr.readlines()
    numberOfLines = len(arrayline)   #读取文件的行数#
    returnMat = zeros((numberOfLines,14))  # 构造一个与文件行数相等，列数为14的零矩阵作为特征矩阵，来存储样本的14个特征#
    classLabelVector = []                 #存储样本类别的列表#
    index = 0
    bad_line_count = 0
    dd={'?':None,'Private':0,'Self-emp-not-inc':1,'Self-emp-inc':2,'Federal-gov':3,'Local-gov':4,'State-gov':5,\
           'Without-pay':6,'Never-worked':7,'Bachelors':0,'Some-college':1,'11th':2,'HS-grad':3,'Prof-school':4,\
           'Assoc-acdm':5,'Assoc-voc':6,'9th':7,'7th-8th':8,'12th':9,'Masters':10,'1st-4th':11,'10th':12,\
           'Doctorate':13,'5th-6th':14,'Preschool':15,'Married-civ-spouse':0,'Divorced':1,'Never-married':2,\
           'Separated':3,'Widowed':4,'Married-spouse-absent':5,'Married-AF-spouse':6,'Tech-support':0,\
           'Craft-repair':1,'Other-service':2,'Sales':3,'Exec-managerial':4,'Prof-specialty':5,\
           'Handlers-cleaners':6,'Machine-op-inspct':7,'Adm-clerical':8,'Farming-fishing':9,'Transport-moving':10,\
           'Priv-house-serv':11,'Protective-serv':12,'Armed-Forces':13,'Wife':0,'Own-child':1,'Husband':2,'Not-in-family':3,\
           'Other-relative':4,'Unmarried':5,'White':0,'Asian-Pac-Islander':1,'Amer-Indian-Eskimo':2,'Other':3,'Black':4,\
           'United-States':0,'Cambodia':1,'England':2,'Puerto-Rico':3,'Canada':4,'Germany':5,'Outlying-US(Guam-USVI-etc)':6,\
           'India':7,'Japan':8,'Greece':9,'South':10,'China':11,'Cuba':12,'Iran':13,'Honduras':14,'Philippines':15,'Italy':16,'Poland':17,\
           'Jamaica':18,'Vietnam':19,'Mexico':20,'Portugal':21,'Ireland':22,'France':23,'Dominican-Republic':24,'Laos':25,'Ecuador':26,'Taiwan':27,\
           'Haiti':28,'Columbia':29,'Hungary':30,'Guatemala':31,'Nicaragua':32,'Scotland':33,'Thailand':34,'Yugoslavia':35,\
           'El-Salvador':36,'Trinadad&Tobago':37,'Peru':38,'Hong':39,'Holand-Netherlands':40,'>50K':0,'<=50K':1,'Female':0,'Male':1,}
    for line in arrayline:
        line = line.strip()
        line = line.replace(' ','')
        listFromLine = line.split(',')   #将逗号作为分隔符将整行数据分割成一个元素列表#

        # 字段不足的行就不要了
        if len(listFromLine) < 15: 
            print 'error_line: '
            print  line
            bad_line_count += 1
            continue

        returnMat[index,0] = int(listFromLine[0])   #循环个别值出错了，所以一行一行展开写的#
        returnMat[index,1] = dd[listFromLine[1]]
        returnMat[index,2] = int(listFromLine[2])
        returnMat[index,3] = dd[listFromLine[3]]
        returnMat[index,4] = int(listFromLine[4])
        returnMat[index,5] = dd[listFromLine[5]]
        returnMat[index,6] = dd[listFromLine[6]]
        returnMat[index,7] = dd[listFromLine[7]]
        returnMat[index,8] = dd[listFromLine[8]]
        returnMat[index,9] = dd[listFromLine[9]]
        returnMat[index,10] = int(listFromLine[10])
        returnMat[index,11] = int(listFromLine[11])
        returnMat[index,12] = int(listFromLine[12])
        returnMat[index,13] = dd[listFromLine[13]]
    # 将listfromline最后一列的元素转化为整型（告知解释器为整型，否则会直接被当成字符串），再加到classlabelvedtor中#
        salary = listFromLine[-1].strip('.')
        classLabelVector.append(dd[salary])
        index += 1

    # 切片 去掉多余的行
    if bad_line_count > 0:
        returnMat = returnMat[:numberOfLines-bad_line_count]

    # 转成 pd
    column_array = [
        'age', 'workclass', 'fnlwgt', 'education', 'education-num', 'marital-status', 'occupation',
        'relationship', 'race', 'sex', 'capital-gain', 'capital-loss', 'hours-per-week', 'native-country',
    ]
    #index_array = [i for i in xrange(0, numberOfLines-bad_line_count)]
    df = DataFrame(returnMat, columns=column_array)
    # print df.isnull().sum()
    # 填充缺失值
    df['workclass'].fillna(mode(df['workclass']).mode[0], inplace=True)
    df['occupation'].fillna(mode(df['occupation']).mode[0], inplace=True)
    df['native-country'].fillna(mode(df['native-country']).mode[0], inplace=True)
    return returnMat, classLabelVector


def autoNorm(dataSet):  # 将数字特征值归一化#
    minVals = dataSet.min(0)  # 从dataset的每一列中选取最小值构成向量#
    maxVals = dataSet.max(0)
    ranges = maxVals - minVals  # 得到dataset每一列的范围构成的向量#
    normDataSet = zeros(shape(dataSet))  # 将与dataset相同维度的零矩阵设为初始的归一化特征矩阵#
    m = dataSet.shape[0]  # dataset数据集的行数即样本总数#
    normDataSet = dataSet - tile(minVals, (m, 1))
    normDataSet = normDataSet / tile(ranges, (m, 1))  # title函数将变量内容复制成与特征矩阵相同维度的矩阵，对应元素相除#
    return normDataSet, ranges, minVals

def classify0(inX, dataSet, labels, k):       #########knn算法##########
    dataSetSize = dataSet.shape[0]             #读取数据集第一维度的长度，即行数；dataSet.shape 则为数据集的全部维度#
    # 计算欧氏距离#
    diffMat = tile(inX, (dataSetSize,1)) - dataSet  #tile(A,reps) 将原来A中每一维度的元素进行copy，
                                                    # 生成的新的A中此元素出现次数为新的reps对应维度的数目。#
    sqDiffMat = diffMat**2
    sqDistances = sqDiffMat.sum(axis=1)   #axis=1 表示对矩阵每一行上的元素进行求和；axis=0表示对矩阵上每一列上的元素求和#
    distances = sqDistances**0.5
    # 对计算出的欧氏距离排序#
    sortedDistIndicies = distances.argsort()   #argsort()函数是将distances中的元素从小到大排列，
                                              # 提取其对应的index(索引)，然后输出到sortDistIndicies#
    classCount={}    #定义了个字典,用于记录每个分类在前k个最近邻中出现的次数#
    for i in range(k):
        voteIlabel = labels[sortedDistIndicies[i]]  #依次提取前k个最小距离的样本点的标签label#
        # 对前k个近邻的类别进行统计
        classCount[voteIlabel] = classCount.get(voteIlabel,0) + 1 #get()返回字典classcount中给定键voteIlabel对应的值，
                                                                # 如果字典中不存在该键，就返回0，说明该分类没有出现过#
    # 根据前k个近邻的类别个数从大到小降序排序#
    sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(1), reverse=True)
    #key为函数，指定取字典classcount中的哪一项进行排序，operator.itemgetter（1）获取对象第2维的数据，reverse为是否选择逆序排序#
    return sortedClassCount[0][0]  #选取前k个近邻中出现次数最多的类别作为该样本的类别#


def main(): 

    (dataSet, labels) = filematrix('adult_train.txt')
    print len(dataSet)
    print len(labels)
    (test_dataset, test_labels) = filematrix('adult_test.txt')
    print len(test_dataset)
    print len(test_labels)
    index = 0
    k   = 17
    count = [0,0]
    for inX in test_dataset: 
        knn  = classify0(inX, dataSet, labels, k)
        if knn == test_labels[index]: 
            count[0] += 1
        else: 
            count[1] += 1
        index += 1
        
    print count

main()
