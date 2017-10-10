# 类说明

BaseStationSimulator.py 共包含三个类:
1) 基站 BaseStation
包含以下几个成员变量:
`self.ID`  unique id
`self.street` location.street
`self.city` location.city
`self.country` location.country
`self.capacity`  最多同时允许几个手机连接上来
`start_time`  基站启动时间
`records`   连接到此基站的全部手机号码及建立连接的时间

2) 用户手机 Phone
包含以下几个成员变量:
`self.phone`  手机号码
`self.is_connected`  是否已经与基站建立了连接
`self.msg`  没什么用
`self.bs`   已连接上的基站

3) 模拟器 BaseStationSimulator
模拟器去调用基站与手机的各种接口.

# 接口说明
## Phone
connect  向某个基站发起连接
disconnect  从某个基站断开连接
sendMsg 发送消息给基站(hello)
dump    debug信息

## BaseStation
startup  基站启动 同时把此事件发送给data processor
connect 接收手机的连接请求
如果未达到capacity,则成功建立连接, 同时把此事件推送给data processor
disconnect  接收手机的断开连接的请求
同时把此事件推送给data processor
receiveMsg  接收手机发来的信息
dump   debug信息

# 大体流程
模拟器启动多个基站
模拟器随机创建多个手机号码
死循环
    打乱全部手机号码的顺序
    对于每一个手机号码
        随机sleep 一段时间
        再取一个0-1之间的随机数, 如果此数大于0.5 则不再处理当前手机.
        如果此手机已经建立了连接,则断开连接
        如果此手机尚未建立连接,则从多个基站中随机取一个并建立连接之后,再发送hello消息


# todo 
Offline functionalities:
your program should be able to save messages in memory(in a data structure of your choice)
when an Internet connection is not available,
and send them when the connection is established again.


