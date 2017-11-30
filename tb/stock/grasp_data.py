from pandas_datareader import data as pdr
import fix_yahoo_finance as yf
yf.pdr_override()
data1 = pdr.get_data_yahoo("AAL", start="2014-06-01", end="2016-06-13")
data2 = pdr.get_data_yahoo("ALK", start="2014-06-01", end="2016-06-13")
data3 = pdr.get_data_yahoo("AVH", start="2014-06-01", end="2016-06-13")
data4 = pdr.get_data_yahoo("CEA", start="2014-06-01", end="2016-06-13")
data5 = pdr.get_data_yahoo("ZNH", start="2014-06-01", end="2016-06-13")
data6 = pdr.get_data_yahoo("VLRS", start="2014-06-01", end="2016-06-13")
data7 = pdr.get_data_yahoo("CPA", start="2014-06-01", end="2016-06-13")
data8 = pdr.get_data_yahoo("DAL", start="2014-06-01", end="2016-06-13")
data9 = pdr.get_data_yahoo("GOL", start="2014-06-01", end="2016-06-13")
data10 = pdr.get_data_yahoo("LTM", start="2014-06-01", end="2016-06-13") # represent LFL
data11 = pdr.get_data_yahoo("LUV", start="2014-05-01", end="2016-06-13")
data12 = pdr.get_data_yahoo("UAL", start="2014-06-01", end="2016-06-13")
data13 = pdr.get_data_yahoo("WTI", start="2014-06-01", end="2016-06-13")