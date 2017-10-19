#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
pip install pandas
pip install sklearn
sudo apt-get install libpng-dev
sudo apt-get install libfreetype6-dev
pip install matplotlib
gtk+ is needed to plot
"""
import sys
import numpy as np
import operator
import pandas as pd
import matplotlib
from sklearn import model_selection

class PreProcess(object): 
    """PreProcess
    """

    def __init__(self): 
        """__init__
        """
        self.df = None
        self.arrFeatures = list()
        self.arrResults = list()
        self.arrLoanStatus = {
            'CURRENT': 0,
            'FULLY PAID': 0,
            'LATE (16-30 DAYS)': 1,
            'LATE (31-120 DAYS)': 1,
            'CHARGED OFF': 1,
            'DEFAULT': 1
        }

        self.arrEmpLength = {
            '1 YEAR': 1,
            '2 YEARS': 2,
            '3 YEARS': 3,
            '4 YEARS': 4,
            '5 YEARS': 5,
            '6 YEARS': 6,
            '7 YEARS': 7,
            '8 YEARS': 8,
            '9 YEARS': 9,
            '10+ YEARS': 10
        }

        self.arrHomeOwnership = {
            'MORTGAGE': 1,
            'RENT': 2,
            'OTHER': 3,
            'OWN': 4,
            'NONE': 5,
            'ANY': 6 
        }

    def go(self): 
        """go
        """
        self.loadFile()
        self.featureAnalysis()
        self.save()

    def save(self): 
        """save feature and result to svm file
        """

        # http://scikit-learn.org/stable/modules/generated/sklearn.model_selection.train_test_split.html#sklearn.model_selection.train_test_split
        arrXTrain, arrXTest, arrYTrain, arrYTest = \
            model_selection.train_test_split(
                self.arrFeatures, self.arrResults, test_size=0.25)

        with open('./test.svm', 'w') as f: 
            index = 0
            for X in arrXTest: 
                Y = arrYTest[index]
                index += 1
                vector = list()
                vector.append(str(Y) + ' ')
                i = 0
                for feature in X: 
                    vector.append(str(i) + ':' + str('%.6f' % feature))
                    i += 1
                vector.append(str(i) + ':' + str('%.6f' % 0))
                f.write(' '.join(vector) + '\n')

        with open('./train.svm', 'w') as f: 
            index = 0
            for X in arrXTrain: 
                Y = arrYTrain[index]
                index += 1
                vector = list()
                vector.append(str(Y) + ' ')
                i = 0
                for feature in X: 
                    vector.append(str(i) + ':' + str('%.6f' % feature))
                    i += 1
                vector.append(str(i) + ':' + str('%.6f' % 0))
                f.write(' '.join(vector) + '\n')

    def featureAnalysis(self): 
        """featureAnalysis
        """
        self.analyse('loan_amnt')
        self.analyse('int_rate')
        self.analyse('annual_inc')
        self.analyse('delinq_2yrs')
        self.analyse('open_acc')
        self.analyse('dti')
        self.analyse('emp_length')
        self.analyse('funded_amnt')
        self.analyse('tot_cur_bal')
        self.analyse('home_ownership')

    def analyse(self, feature_name): 
        """analyse some feature
        """
        print 'analyse feature : ' + feature_name
        print self.df[feature_name].describe()
        print '------------------------------------------------'
        return

        if feature_name == "emp_length" or feature_name == "home_ownership": 
            # categorical
            fig = self.df[feature_name].value_counts().plot(kind='bar').get_figure()
        else: 
            # continuous
            fig = self.df[feature_name].plot.hist(bins=50).get_figure()

        fig.set_size_inches(18.5, 10.5)
        fig.subplots_adjust(bottom=0.2)
        fig.savefig(feature_name+".png")
        fig.clear()


    def loadFile(self): 
        """loadFile
        """
        arrCounts = {
            'total_line': 0,
            'result_line': 0,
            'token_count_error': 0,
            'format_error':0, 
            'status_filter': 0,
        }
        with open('./LendingClub2012to2013.csv') as f: 
            for line in f: 
                arrCounts['total_line'] += 1
                #if arrCounts['total_line'] > 10000: 
                #    break
                line = line.strip()
                arrTokens = line.split(',')

                if len(arrTokens) != 115: 
                    arrCounts['token_count_error'] += 1
                    continue

                try: 
                    ID = int(arrTokens[1-1])
                    loan_amnt = int(arrTokens[3-1])
                    int_rate = float(arrTokens[7-1].replace("%", ""))
                    annual_inc = int(arrTokens[14-1])
                    delinq_2yrs = int(arrTokens[26-1])
                    open_acc = int(arrTokens[33-1])
                    dti = float(arrTokens[25-1])

                    emp_length = arrTokens[12-1].strip().upper()
                    if emp_length in self.arrEmpLength: 
                        emp_length = self.arrEmpLength[emp_length]
                    else: 
                        emp_length = 0

                    funded_amnt = int(arrTokens[4-1])
                    tot_cur_bal = int(arrTokens[63-1])

                    home_ownership = arrTokens[13-1].strip().upper()
                    if home_ownership in self.arrHomeOwnership: 
                        home_ownership = self.arrHomeOwnership[home_ownership]
                    else: 
                        home_ownership = 0

                except Exception as e: 
                    arrCounts['format_error'] += 1
                    continue

                loan_status = arrTokens[16].upper()
                if loan_status not in self.arrLoanStatus.keys(): 
                    arrCounts['status_filter'] += 1
                    continue

                arrF = [
                    loan_amnt,
                    int_rate,
                    annual_inc,
                    delinq_2yrs,
                    open_acc,
                    dti,
                    emp_length,
                    funded_amnt,
                    tot_cur_bal,
                    home_ownership
                ]
                self.arrFeatures.append(arrF)

                # predict loan_status
                self.arrResults.append(self.arrLoanStatus[loan_status])
                arrCounts['result_line'] += 1

        # convert list to dataframe
        arrColumns = [
            'loan_amnt', 'int_rate', 'annual_inc', 'delinq_2yrs',
            'open_acc', 'dti', 'emp_length', 'funded_amnt', 'tot_cur_bal',
            'home_ownership'
        ]
        self.df = pd.DataFrame(self.arrFeatures)
        # print self.df.isnull().sum()
        print self.df.head(3)
        # useless ...
        from sklearn.preprocessing import Normalizer
        ndarray = Normalizer(norm='l2').fit_transform(self.df)  
        self.df = pd.DataFrame(ndarray, columns=arrColumns)
        print self.df.head(3)
        self.arrFeatures = list()
        self.arrFeatures = self.df.values.tolist()

        print arrCounts
        print '------------------------------------------------'

if __name__ == "__main__": 
    o = PreProcess()
    o.go();
