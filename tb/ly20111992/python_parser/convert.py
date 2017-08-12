#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os
import json

""" 根据csv和图片，生成html
页面上的主要功能均由js来实现
python 负责把源数据转成js的数组.
python与js之间通过json格式来进行交流
当然这个交流是单向的 python->js
"""

class Converter(object): 
    """转化器
    此文件中就只有这一个类
    此类中的各种方法基本上不会返回true false，
    只会比较随意地抛出各种异常
    """

    def __init__(self): 
        """init
        """
        # 配置
        self.arrConf = {
            # 数据文件
            "csv_file": "./exampleData_new.csv",
            # 图片目录
            "img_dir": "./newFigureRepositroy",
            # 模板文件
            "tpl_file": "./tpl.html",
            # title
            "title": "报告的title",
            # 模板变量
            "tpl_params": {
                "csv_header": "####CSV_HEADER####",
                "csv_body": "####CSV_BODY####",
                "img_dir": "####IMG_DIR####",
                "title" : "####TITLE####"
            },
            # 输出文件
            "output_file": "result.html"
        }
        
        # csv文件头
        self.arrCsvHeader   = list()

        # csv文件内容
        self.arrCsvBody     = list()

        # 图片列表
        self.arrImg = {}


    def run(self): 
        """入口函数
        """
        self.parseImg()
        self.parseCsv()
        self.merge()
        self.output()

    def output(self): 
        """ 把python中的变量json化之后输出到html模板中
        """

        # 读取模板
        strHtml  = open(self.arrConf['tpl_file']).read(1000000) 

        # json 化
        strCsvHeader    = json.dumps(self.arrCsvHeader)
        strCsvBody      = json.dumps(self.arrCsvBody)

        # 替换
        strHtml = strHtml.replace(self.arrConf['tpl_params']['csv_header'], strCsvHeader)
        strHtml = strHtml.replace(self.arrConf['tpl_params']['csv_body'], strCsvBody)
        strHtml = strHtml.replace(self.arrConf['tpl_params']['img_dir'], self.arrConf['img_dir'] + "/")
        strHtml = strHtml.replace(self.arrConf['tpl_params']['title'], self.arrConf['title'])

        # 输出
        with open(self.arrConf['output_file'], "w") as f: 
            f.write(strHtml)


    def merge(self): 
        """ 把csv文件相关的变量与img相关的变量
        通过key关联起来
        """
        for arr in self.arrCsvBody: 
            # key就是img文件名的前半部分
            key = arr[0]
            # 这条csv数据没有关联的图片
            # 所以我们放一个空数组在后面
            # 以便于保持arr格式的一致性
            if key not in self.arrImg: 
                arr.append([])
                continue
            # 把图片数组放到csvbody的最后一列
            arr.append(self.arrImg[key])

    def parseImg(self): 
        """ parseImg
        从self.arrConf.img_dir中读取各个图片文件并分组
        """
        for filename in os.listdir(self.arrConf['img_dir']): 
            filename = filename.strip()
            # 只接收.png结尾的文件
            if filename[-4:] != '.png': 
                continue

            # 文件名一定是符合 AAAA DMM 2-box.png 
            # 这种格式的，如果不符合，
            # 则抛出异常
            arrTmp = filename.split("-")
            #if len(arrTmp) != 2: 
            #    raise Exception(filename + " format error")

            # 用key把文件组织起来
            # key = arrTmp[0].strip()
            key = '-'.join(arrTmp[:-1]).strip()
            if key not in self.arrImg: 
                self.arrImg[key] = list()
            # print "add " + filename + " to key: " + key
            self.arrImg[key].append(filename)
        
    def parseCsv(self): 
        """ parseCsv
        从self.arrConf.csv_file中读取源数据
        全部读取到数组之中
        """

        with open(self.arrConf['csv_file']) as f: 
            i = 0
            for line in f: 
                i += 1
                line = line.strip()
                arrTmp = line.split(",")
                # 第一行
                # 认为是头
                if i == 1: 
                    self.arrCsvHeader   = arrTmp
                    continue

                # 其它行
                # 认为是body
                self.arrCsvBody.append(arrTmp)

def main(arrConf): 
    """main
    调用Converter类的run方法
    """
    o = Converter()
    for k,v in arrConf.items(): 
        o.arrConf[k] = v
    o.run()


if __name__ == "__main__": 
    try: 
        arrConf = {}
        if len(sys.argv) == 4: 
            arrConf['csv_file'] = sys.argv[1]
            arrConf['img_dir'] = sys.argv[2]
            arrConf['title'] = sys.argv[3]
        main(arrConf)
    except Exception as e: 
        print e
        sys.exit(-1)

