#!/usr/bin/env python
#-*- coding: utf-8 -*-

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

import time
from scipy.stats import mstats
from sklearn.linear_model import LinearRegression
from sklearn.cross_validation import KFold

from sklearn.linear_model import SGDRegressor
from sklearn.preprocessing import StandardScaler
from sklearn.cross_validation import cross_val_score

from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import Ridge


class PreProcess(object): 
    """PreProcess 4 datas
    """

    def __init__(self): 
        """__init__
        """
        self.arrFiles = {
            'thompson': 'data/thompson.txt',
            'amboy': 'data/amboy.txt',
            'admin': 'data/admin.txt',
            'riverside': 'data/riverside.txt',
        }

    def loadDataset(self):
        """loadDataset
        """
        self.loadThompson()
        self.loadAdmin()
        self.loadRiverside()
        self.loadAmboy()

    def loadRiverside(self): 
        """
        """
        src = 'riverside'
        dateparser = lambda dates: pd.datetime.strptime(dates, '%m/%d/%y %H:00:00')
        df = pd.read_csv(self.arrFiles[src], sep='\t', parse_dates=[1], date_parser=dateparser)
        df.columns = ["gaps", "time", "streamflow", "meterflow", 'rainfall']
        del df['gaps']
        df2 = df.set_index(pd.DatetimeIndex(pd.to_datetime(df['time'])))

        del df2['time']
        self.figureall(df2, src)


    def loadAdmin(self): 
        """
        """
        src = 'admin'
        dateparser = lambda dates: pd.datetime.strptime(dates, '%m/%d/%y %H:00:00')
        df = pd.read_csv(self.arrFiles[src], sep='\t', parse_dates=[1], date_parser=dateparser)
        df.columns = ["gaps", "time", "streamflow", "meterflow", 'time2', 'meterflow2', 'rainfall']
        del df['gaps']
        del df['time2']
        del df['meterflow2']
        df2 = df.set_index(pd.DatetimeIndex(pd.to_datetime(df['time'])))

        del df2['time']
        self.figureall(df2, src)


    def loadThompson(self): 
        """
        """
        src = 'thompson'
        dateparser = lambda dates: pd.datetime.strptime(dates, '%m/%d/%y %H:00:00')
        df = pd.read_csv(self.arrFiles[src], sep='\t', parse_dates=[1], date_parser=dateparser)
        df.columns = ["gaps", "time", "streamflow", "meterflow", 'rainfall']
        del df['gaps']
        df2 = df.set_index(pd.DatetimeIndex(pd.to_datetime(df['time'])))

        del df2['time']

        # 15年缺失值太多， 直接drop掉
        df2 = df2.loc['2016-01-27':'2017']
        self.figureall(df2, src)

    def loadAmboy(self): 
        """
        """
        src = 'amboy'
        dateparser = lambda dates: pd.datetime.strptime(dates, '%m/%d/%y %H:00:00')
        df = pd.read_csv(self.arrFiles[src], sep='\t', parse_dates=[1], date_parser=dateparser)
        df.columns = ["gaps", "time", "streamflow", "meterflow", 'time2', 'meterflow2', 'rainfall']
        del df['gaps']
        del df['time2']
        del df['meterflow2']
        df2 = df.set_index(pd.DatetimeIndex(pd.to_datetime(df['time'])))

        del df2['time']
        self.figureall(df2, src)



    def figureall(self, df2, src): 
        print 
        print '===================%s seasonly=========================' % src
        self.figure(df2, src, 'seasonly')
        print 
        print '==================%s daily====================' % src
        self.figure(df2, src, 'daily')
        print 
        print '==================%s half daily==================' % src
        self.figure(df2, src, 'half_daily')
        print 
        print '===================%s hourly=========================' % src
        self.figure(df2, src, 'hourly')


    def figure(self, df2, src, time_range): 
        if time_range == "daily": 
            resample_range = '1D'
        elif time_range == 'half_daily': 
            resample_range = '12H'
        elif time_range == 'seasonly': 
            resample_range = '1Q'
        else: 
            resample_range = '1H'
        
        df3 = df2.resample(resample_range).mean()
        #print 
        #print '---------------df resample %s----------' % resample_range
        #print df3.shape
        #print df3.head(3)

        # 用前一个数据代替NaN：method='pad'
        #print 
        #print '---------------fill na------------------------'
        #print df3.isnull().sum()
        #df4= df3.fillna(method='pad')
        # 平均值填充缺失
        df4= df3.fillna(df3.mean())
        #print df4.describe()

        # 画图
        #print 
        #print '---------------save figure--------------------'
        #fig = df4.plot(subplots=True)
        #plt.savefig('./img/%s_%s_original.png' % (src, time_range))
        #plt.clf()
        #plt.close()

        # 处理异常值
        #print 
        #print '---------------winsorize---------------------------'
        df4['streamflow'] = mstats.winsorize(df4['streamflow'].values, limits=(0.03, 0.03))
        df4['meterflow'] = mstats.winsorize(df4['meterflow'].values, limits=(0.03, 0.03))
        df4['rainfall'] = mstats.winsorize(df4['rainfall'].values, limits=(0.03, 0.03))

        #print df4['streamflow'].describe()
        #print df4['meterflow'].describe()
        #print df4['rainfall'].describe()

        
        # 画图
        #print
        #print '---------------save figure--------------------'
        fig, ax = plt.subplots(figsize=(20, 10))
        ax2 = ax.twinx()
        if src == 'admin': 
            if time_range == 'hourly': 
                ax2.set_ylim(10, 75)
            else: 
                ax2.set_ylim(10, 50)
        if src == 'amboy': 
            if time_range == 'hourly': 
                ax2.set_ylim(5, 30)
            else: 
                ax2.set_ylim(5, 20)
        if src == 'thompson': 
            if time_range == 'hourly': 
                ax2.set_ylim(1, 15)
            else:
                ax2.set_ylim(1, 10)
        if src == 'riverside': 
            if time_range == 'hourly': 
                ax2.set_ylim(0, 15)
            else: 
                ax2.set_ylim(0, 10)
        fig.subplots_adjust(bottom=0.2, right=0.7)
                
        df4['streamflow'].plot(ax=ax, style='b-')
        df4['meterflow'].plot(ax=ax2, style='r-')
        patches, labels = ax.get_legend_handles_labels()
        ax.legend([ax.get_lines()[0], ax2.get_lines()[0], ax.get_lines()[0]],\
            ['streamflow','meterflow'], bbox_to_anchor=(1.3, 0.5))
        
        plt.savefig('./img/%s_%s_streamflow_meterflow.png' % (src, time_range))
        plt.clf()
        plt.close()

        fig, ax = plt.subplots(figsize=(20, 10))
        ax2 = ax.twinx()
        if time_range == 'hourly': 
            ax2.set_ylim(0, 0.15)
        else: 
            ax2.set_ylim(0, 0.125)

        fig.subplots_adjust(bottom=0.2, right=0.7)
                
        df4['streamflow'].plot(ax=ax, style='b-')
        df4['rainfall'].plot(ax=ax2, style='r-')
        patches, labels = ax.get_legend_handles_labels()
        ax.legend([ax.get_lines()[0], ax2.get_lines()[0], ax.get_lines()[0]],\
            ['streamflow','rainfall'], bbox_to_anchor=(1.3, 0.5))
        
        plt.savefig('./img/%s_%s_streamflow_rainfall.png' % (src, time_range))
        plt.clf()
        plt.close()

        # 相关系数
        # 相关系数为正值，说明一个变量变大另一个变量也变大；
        # 取负值说明一个变量变大另一个变量变小，
        # 取0说明两个变量没有相关关系。
        # 相关系数的绝对值越接近1，线性关系越显著。 
        print 'corr of streamflow and meterflow:', df4['streamflow'].corr(df4['meterflow'])
        print 'corr of streamflow and rainfall:' ,df4['streamflow'].corr(df4['rainfall'])

        # LR回归
        x = df4[['meterflow', 'rainfall']].values
        y = df4[['streamflow']].values

        n_folds = 5
        kf = KFold(len(x), n_folds=n_folds)
        model = LinearRegression()
        
        total_score = 0
        current_round = 0
        for train, test in kf: 
            model.fit(x[train], y[train].ravel())
            score = model.score(x[test], y[test].ravel())
            total_score += (score)
            current_round += 1
            # 只取最后一折的score
            if current_round == n_folds: 
                print "LR:", score

        # 多项式回归
        x = df4[['meterflow', 'rainfall']].values
        y = df4[['streamflow']].values
        kf = KFold(len(x), n_folds=n_folds)
        model = LinearRegression() # 创建一个线性回归实例
        
        total_score = 0
        current_round = 0
        for train, test in kf: 
            quadratic_featurizer = PolynomialFeatures(degree=2) # 实例化一个二次多项式特征实例
            X_train_quadratic = quadratic_featurizer.fit_transform(x[train]) # 用二次多项式对样本X值做变换
            X_test_quadratic = quadratic_featurizer.transform(x[test])
            model.fit(X_train_quadratic, y[train]) # 以多项式变换后的x值为输入，代入线性回归模型做训练
            score = model.score(X_test_quadratic, y[test])
            total_score += (score)
            current_round += 1
            # 只取最后一折的score
            if current_round == n_folds: 
                print "Polynomial: " , score

        # 岭回归
        x = df4[['meterflow', 'rainfall']].values
        y = df4[['streamflow']].values
        kf = KFold(len(x), n_folds=n_folds)
        model = Ridge(alpha=.6)
        total_score = 0
        current_round = 0
        for train, test in kf: 
            model.fit(x[train], y[train].ravel())
            score = model.score(x[test], y[test].ravel())
            total_score += (score)
            current_round += 1
            # 只取最后一折的score
            if current_round == n_folds: 
                print "Ridge:", score
        

        # SGD回归
        x = df4[['meterflow', 'rainfall']].values
        y = df4[['streamflow']].values

        x_scaler = StandardScaler()
        y_scaler = StandardScaler()

        x = x_scaler.fit_transform(x)
        y = x_scaler.fit_transform(y)

        model = SGDRegressor(loss='squared_loss', max_iter=1000000, tol=1e3)
        # scores = cross_val_score(regressor, x, y.ravel(), cv = n_folds)
        total_score = 0
        current_round = 0
        for train, test in kf: 
            model.fit(x[train], y[train].ravel())
            score = model.score(x[test], y[test].ravel())
            total_score += (score)
            current_round += 1
            # 只取最后一折的score
            if current_round == n_folds: 
                print "SGD:", score
            
        # 回归 streamflow与meterflow
        """
        print
        print '-------------lstsq streamflow and meterflow---------------'
        x = df4['meterflow']
        y = df4['streamflow']
        plt.scatter(x, y)

        x = np.array([[v, 1] for v in x])
        slope, total_error,_,_ = np.linalg.lstsq(x, y)
        rmse = np.sqrt(total_error[0] / len(x))
        print rmse
        m = slope[0]
        c = slope[1]
        plt.plot(x, m*x + c, 'r')
        plt.savefig('./img/%s_%s_streamflow_meterflow.png' % (src, time_range))
        plt.clf()
        plt.close()
        """


        # 回归 streamflow与rainfall
        """
        print
        print '------------streamflow and rainfall---------------------'
        x = df4['rainfall']
        y = df4['streamflow']
        plt.scatter(x, y)

        x = np.array([[v, 1] for v in x])
        slope, total_error,_,_ = np.linalg.lstsq(x, y)
        rmse = np.sqrt(total_error[0] / len(x))
        print rmse
        m = slope[0]
        c = slope[1]
        plt.plot(x, m*x + c, 'r')
        plt.savefig('./img/%s_%s_streamflow_rainfall.png' % (src, time_range))
        plt.clf()
        plt.close()
        """


    def go(self): 
        """go
        """
        self.loadDataset()

if __name__ == '__main__': 
    o = PreProcess()
    o.go()
