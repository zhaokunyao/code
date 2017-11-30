#encoding=utf8
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pandas.util.testing import assert_series_equal
import sys
import time
import statsmodels.formula.api as smf

class trading_strategy: 

    def __init__(self): 
        self.moving_average_25 = 0
        self.moving_average_5 = 0
        self.moving_average_25_old = 0
        self.moving_average_5_old = 0
        self.list_5 = list()
        self.list_25 = list()
        self.pnl = 0

    def process_tick(self, adjusted_price, date): 
        price = adjusted_price
        date = date
        #print ('process_tick %s %s'  % (adjusted_price , date))

        self.moving_average_5_old = self.moving_average_5
        self.moving_average_25_old = self.moving_average_25

        len_5 = len(self.list_5)
        if len_5 < 5: 
            self.list_5.append(price)
        else: 
            self.list_5.pop(0)
            self.list_5.append(price)
            self.moving_average_5 = np.mean(self.list_5)

        len_25 = len(self.list_25)
        if len_25 < 25: 
            self.list_25.append(price)
        else: 
            self.list_25.pop(0)
            self.list_25.append(price)
            self.moving_average_25 = np.mean(self.list_25)

        # skip zeros
        if len(self.list_25) < 25 or len(self.list_5) < 5: 
            return

        signal = self.check_signal()
        if 0 == signal: 
            return

        if 1 == signal: 
            self.generate_buy_order(price, date)
            self.update_pnl(price)

        if -1 == signal: 
            self.generate_sell_order(price, date)
            self.update_pnl(-1 * price)

    def check_signal (self): 
        if self.moving_average_5_old <= self.moving_average_25_old: 
            if self.moving_average_5 > self.moving_average_25: 
                return 1 
        if self.moving_average_5_old >= self.moving_average_25_old: 
            if self.moving_average_5 < self.moving_average_25: 
                return -1

        return 0

    def update_pnl (self, price): 
        self.pnl += price

    def generate_buy_order (self, price, date): 
        print ("BUY %s %s" % (price, date))

    def generate_sell_order (self, price, date): 
        print ("SELL %s %s" % (price, date))

    def display_pnl(self): 
        return self.pnl

class Stock(object): 
    """ the stock class
    """

    def __init__(self): 
        """ __init__
        """

        self.arrFilePath = {
            'AAL': 'DATA/AAL.csv',
            'ALK': 'DATA/ALK.csv',
            'AVH': 'DATA/AVH.csv',
            'CEA': 'DATA/CEA.csv',
            'ZNH': 'DATA/ZNH.csv',
            'VLRS': 'DATA/VLRS.csv',
            'CPA': 'DATA/CPA.csv',
            'DAL': 'DATA/DAL.csv',
            'GOL': 'DATA/GOL.csv',
            'LFL': 'DATA/LFL.csv',
            'LUV': 'DATA/LUV.csv',
            'UAL': 'DATA/UAL.csv',
            'WTI': 'DATA/WTI.csv',
        }

        self.arrSymbol = [
            'AAL', 
            'ALK',
            'AVH',
            'CEA',
            'CPA',
            'DAL',
            'GOL',
            'LFL',
            'LUV',
            'UAL',
            'VLRS',
            'WTI',
            'ZNH',
        ]

    def task1(self): 
        """task1
        """
        print ("============task1=============")
        self.all_data = dict()
        for symbol in self.arrSymbol: 
            if symbol == "LUV": 
                continue
            file_path = self.arrFilePath[symbol]
            dateparser = lambda dates: pd.datetime.strptime(dates, '%Y/%m/%d')
            self.all_data[symbol] = pd.read_csv(file_path, 
                sep=',', parse_dates=[0], date_parser=dateparser, index_col=0)

        print (self.all_data['AAL'].head(2))
        print (self.all_data['AAL'].tail(2))

    def task2(self): 
        """task2
        """
        print ("============task2=============")
        symbol = "LUV"
        file_path = self.arrFilePath[symbol]
        dateparser = lambda dates: pd.datetime.strptime(dates, '%Y/%m/%d')
        self.luvdf = pd.read_csv(file_path, 
                sep=',', parse_dates=[0], date_parser=dateparser, index_col=0)
        print(self.luvdf.head(2))

    def task3(self): 
        """task3
        """
        print ("============task3=============")
        symbol = "LUV"
        date_start = self.all_data['AAL'].index.values[0]
        date_end = self.all_data['AAL'].index.values[-1]
        self.all_data[symbol] = self.luvdf[date_start: date_end]
        print (self.all_data[symbol].head(2))
        print (self.all_data[symbol].tail(2))

    def task4(self): 
        """task4
        """
        print ("============task4=============")

        column_name = 'Adj Close'
        self.price = self.all_data['AAL'][column_name]
        self.price = self.price.rename("AAL")

        for symbol in self.arrSymbol: 
            if symbol == 'AAL': 
                continue
            s2 = self.all_data[symbol][column_name]
            s2 = s2.rename(symbol)
            self.price = pd.concat([self.price, s2], axis=1)
        print(self.price.head(2))

        column_name = 'Volume'
        self.volume = self.all_data['AAL'][column_name]
        self.volume = self.volume.rename("AAL")

        for symbol in self.arrSymbol: 
            if symbol == 'AAL': 
                continue
            s2 = self.all_data[symbol][column_name]
            s2 = s2.rename(symbol)
            self.volume = pd.concat([self.volume, s2], axis=1)
        print(self.volume.head(2))

    def task5(self): 
        """task5
        """
        print ("============task5=============")
        self.daily_return = dict()
        for symbol in self.arrSymbol: 
            self.daily_return[symbol] = self.price[symbol].pct_change()


        self.daily_return_shift = dict()
        for symbol in self.arrSymbol: 
            shift = self.price[symbol].shift(1)
            daily_return = (self.price[symbol] - shift ) / shift
            self.daily_return_shift[symbol] = daily_return

        is_equal = True
        for symbol in self.arrSymbol: 
            try: 
                assert_series_equal(self.daily_return[symbol], self.daily_return_shift[symbol])
            except Exception as e: 
                is_equal = False
                print(symbol + " two daily_return are NOT equal")

        if is_equal: 
            print("two daily_return are equal")

    def task6(self): 
        """task6
        """
        print ("============task6=============")
        # return of AAL and the Volume

        df2 = self.volume['AAL'].rename('AAL VOLUME')
        df = pd.concat([self.daily_return['AAL'].rename('AAL RETURN'), df2], axis=1)
        df.plot(kind='scatter', x='AAL RETURN', y='AAL VOLUME', color='RED')
        #plt.show()
        plt.savefig('task_6_AAL.png')

        # return of LUV and the Volume
        df2 = self.volume['LUV'].rename('LUV VOLUME')
        df = pd.concat([self.daily_return['LUV'].rename('LUV RETURN'), df2], axis=1)
        df.plot(kind='scatter', x='LUV RETURN', y='LUV VOLUME', color='RED')
        #plt.show()
        plt.savefig('task_6_LUV.png')

    def task7(self): 
        """task7
        """
        print ("============task7=============")
        arrSet = set()
        for s in self.arrSymbol: 
            for s2 in self.arrSymbol: 
                key = '%s:%s' % tuple(sorted([s, s2]))
                if key in  arrSet: 
                    continue
                arrSet.add(key)
                if s == s2: 
                    continue
                print ("correlation between %s and %s:" % (s, s2))
                df1 = self.daily_return[s].to_frame().dropna(axis=0, how='any')
                df1.columns = ['daily_return']
                df2 = self.daily_return[s2].to_frame().dropna(axis=0, how='any')
                df2.columns = ['daily_return']
                print (df1.corrwith(df2))

        big_df = self.daily_return['AAL']
        big_df = big_df.rename('AAL')
        for symbol in self.arrSymbol: 
            if symbol == 'AAL': 
                continue
            s2 = self.daily_return[symbol]
            s2 = s2.rename(symbol)
            big_df = pd.concat([big_df, s2], axis=1)

        # a graphic between the correlation of all the symbols
        pd.scatter_matrix(big_df, diagonal='kde', figsize=(10, 10));
        #plt.show()
        plt.savefig('task_7_matrix.png')

    def task8(self): 
        """task8
        """
        print ("============task8=============")
        #self.all_data['MovingAverage'] = dict()
        for symbol in self.arrSymbol: 
            #self.all_data['MovingAverage'][symbol] = (self.all_data[symbol].rolling(5).mean())
            self.all_data[symbol]['MovingAverage'] = self.daily_return[symbol].rolling(5).mean()
        print (self.all_data['AAL'].head(10))
    
    def task9(self): 
        """task9
        """
        print ("============task9=============")
        noluv = self.daily_return['AAL']
        noluv = noluv.rename('AAL')
        for symbol in self.arrSymbol: 
            if symbol == 'AAL': 
                continue
            s2 = self.daily_return[symbol]
            s2 = s2.rename(symbol)
            noluv = pd.concat([noluv, s2], axis=1)
        #onlyluv = self.daily_return['LUV']
        onlyluv = noluv['LUV']
        # 1 for column
        # mean of the return of all the symbols
        #noluv = noluv.drop('LUV', 1).mean(axis=1)
        # also get rid of WTI
        noluv = noluv.drop('LUV', 1).drop('WTI', 1).mean(axis=1)
        print (noluv.head(10))
        print (onlyluv.head(10))
        tt=pd.DataFrame({'No.LUV': noluv , 'LUV': onlyluv})
        tt.plot()
        #plt.show()
        plt.savefig('task_9_default.png')

        pd.rolling_mean(tt, 10).plot()
        plt.savefig('task_9_rolling_mean.png')

    def task10(self): 
        """task10
        """
        print ("============task10=============")
        arrDict = dict()
        for symbol in self.arrSymbol: 
            if symbol not in arrDict: 
                arrDict[symbol] = dict()
            arrDict[symbol]['expected returns'] = self.daily_return[symbol].mean()
            arrDict[symbol]['risk'] = self.daily_return[symbol].std()

        df = pd.DataFrame(arrDict)
        df = df.T

        fig, ax = plt.subplots()
        df.plot(kind='scatter', x='expected returns', y='risk', color='RED', s=120, figsize=(20,10), ax=ax, linewidth=0)
        for k, v in df.iterrows(): 
            ax.annotate(k, v, xytext=(10,-5), 
                textcoords='offset points', 
                family='sans-serif', 
                fontsize=18, 
                color='darkslategrey')
        
        plt.savefig('task_10.png')

    def task11(self): 
        """task11
        """
        print ("============task11=============")
        df = self.daily_return['AAL']
        df = df.rename('AAL')
        for symbol in self.arrSymbol: 
            if symbol == 'AAL' or symbol == 'WTI': 
                continue
            s2 = self.daily_return[symbol]
            s2 = s2.rename(symbol)
            df = pd.concat([df, s2], axis=1)

        df = df.mean(axis=1).rename('average_return')

        s2 = self.price['WTI']
        s2 = s2.rename('WTI_price')
        df2 = pd.concat([df, s2], axis=1)

        df2.plot(kind='scatter', x='average_return', y='WTI_price', color='RED')
        plt.savefig('task_11_a.png')

        s2 = self.daily_return['WTI']
        s2 = s2.rename('WTI_return')
        df3 = pd.concat([df, s2], axis=1)

        df3.plot(kind='scatter', x='average_return', y='WTI_return', color='RED')
        plt.savefig('task_11_b.png')

        
        est = smf.ols(formula='WTI_return ~ average_return', data=df3).fit()
        print (est.summary())
        print (est.params)
        plt.plot(df3['average_return'], est.params[0] + est.params[1] * df3['average_return'], 'b')
        plt.savefig('task_11_c.png') 

    def task_iv_1(self): 
        """task_iv_1
        """
        print ("============task_iv_1=============")
        price = self.price['LUV']
        #print (price.head(30))
        price_25 = price.rolling(25).mean()
        #print (price_25.head(30))
        price_5 = price.rolling(5).mean()
        #print (price_5.head(10))

        self.luv_data = self.daily_return['AAL']
        self.luv_data = self.luv_data.rename('RETURN_AAL')
        for symbol in self.arrSymbol: 
            if symbol == 'AAL' or symbol == 'WTI' or symbol == 'LUV': 
                continue
            s2 = self.daily_return[symbol]
            s2 = s2.rename('RETURN_' + symbol)
            self.luv_data = pd.concat([self.luv_data, s2], axis=1)

        price = price.rename('LUV_PRICE')
        self.luv_data = pd.concat([self.luv_data, price], axis=1)
        price_5 = price_5.rename('LUV_PRICE_5')
        self.luv_data = pd.concat([self.luv_data, price_5], axis=1)
        price_25 = price_25.rename('LUV_PRICE_25')
        self.luv_data = pd.concat([self.luv_data, price_25], axis=1)

        #self.luv_data = self.luv_data.dropna(axis=0, how='any')
        self.luv_data = self.luv_data.fillna(0)
        print(self.luv_data)

    def task_iv_2(self): 
        """task_iv_2
        """
        print ("============task_iv_2=============")
        # init
        self.luv_data['Signal'] = self.luv_data.apply(lambda row: 0, axis=1)
        old_price_5 = None
        old_price_25 = None
        for index, row in self.luv_data.iterrows(): 
            signal = 0
            if old_price_5 is not None: 
                # skip zeros
                if old_price_5 != 0 and old_price_25 != 0: 
                    # cross
                    if old_price_5 <= old_price_25: 
                        if row['LUV_PRICE_5'] > row['LUV_PRICE_25']: 
                            signal = 1
                    # cross
                    if old_price_5 >= old_price_25: 
                        if row['LUV_PRICE_5'] < row['LUV_PRICE_25']: 
                            signal = -1 
            else: 
                #signal = 1
                pass
       
            self.luv_data['Signal'][index] = signal

            old_price_5 = row['LUV_PRICE_5']
            old_price_25 = row['LUV_PRICE_25']
        
        print (self.luv_data)

    def task_iv_3(self): 
        """task_iv_3
        """
        print ("============task_iv_3=============")
        self.luv_data['PNL'] = self.luv_data.apply(lambda row: 0.0, axis=1)
        old_pnl = 0
        for index, row in self.luv_data.iterrows(): 
            signal = row['Signal']
            if signal == 1: 
                pnl = old_pnl + row['LUV_PRICE']
                print ("buy: %s + %s -> %s [%s]" % (old_pnl, row['LUV_PRICE'], pnl, index))
            elif signal == -1: 
                pnl = old_pnl - row['LUV_PRICE']
                print ("sell: %s - %s -> %s [%s]" % (old_pnl, row['LUV_PRICE'], pnl, index))
            else: 
                pnl = old_pnl
            self.luv_data['PNL'][index] = pnl
            old_pnl = pnl

        print (self.luv_data)

    def task_iv_4(self): 
        """task_iv_4
        """
        print ("============task_iv_4=============")

    def task_iv_5(self): 
        """task_iv_5
        """
        print ("============task_iv_5=============")
        ts1 = trading_strategy()
        for index, row in self.luv_data.iterrows(): 
            adjusted_price = row['LUV_PRICE']
            ts1.process_tick(adjusted_price, index)
        pnl = ts1.display_pnl()
        print (pnl)

        index = self.luv_data.tail(1).index
        pnl2 = self.luv_data['PNL'][index]
        pnl2 = pnl2.values.tolist()[0]

        if pnl == pnl2: 
            print ("the final PNL is exactly the same as the PNL in task3")
        else: 
            print ('wrong pnl task3: %s task5: %s' %(pnl2, pnl))

    def go(self): 
        """go
        """
        # project part III
        self.task1()
        self.task2()
        self.task3()
        self.task4()
        self.task5()
        self.task6()
        self.task7()
        self.task8()
        self.task9()
        self.task10()
        self.task11()

        # project part IV
        self.task_iv_1()
        self.task_iv_2()
        self.task_iv_3()
        self.task_iv_4()
        self.task_iv_5()

if __name__ == '__main__': 
    o = Stock()
    o.go()
