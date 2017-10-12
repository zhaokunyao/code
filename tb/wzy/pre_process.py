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

    def go(self): 
        """go
        """
        self.loadFile()
        self.featureAnalysis()

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

        if feature_name == "emp_length" or feature_name == "home_ownership": 
            # categorical
            fig = self.df[feature_name].value_counts().plot(kind='bar').get_figure()
            fig.subplots_adjust(bottom=0.2)
            fig.savefig(feature_name+".png")
            fig.clear()
        else: 
            # continuous
            fig = self.df[feature_name].plot().get_figure()
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
                    funded_amnt = int(arrTokens[4-1])
                    tot_cur_bal = int(arrTokens[63-1])
                    home_ownership = arrTokens[13-1].strip().upper()

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
        self.df = pd.DataFrame(self.arrFeatures, columns=arrColumns)
        # print self.df.isnull().sum()
        print arrCounts
        print '--------------------------'

if __name__ == "__main__": 
    o = PreProcess()
    o.go();
