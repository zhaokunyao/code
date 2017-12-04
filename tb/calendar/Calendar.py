#encoding=utf8

"""Calendar
"""

import os
import time
import threading
import datetime
import email
import smtplib

"""
程序由两部分组成， 一部分是前台的event管理(用户各种输入对event进行管理)
另外一部分是发送邮件
为了让它们二部分能够并行执行， 启动了一个新的线程： myThread
t = myThread()
t.start()
这样发送邮件的线程就会在后台工作， 不影响前台的event管理功能。
"""
class myThread (threading.Thread): 
    """ thread class to send email
    """

    def __init__(self): 
        """init
        """
        threading.Thread.__init__(self)

    def run(self): 
        """run
        """
        # 今日是否成功发送了邮件
        # 如果超出每日7点，则表示明日是否成功发送了邮件.
        is_sended = False
        while True: 
            # get current date and hour
            d = datetime.datetime.fromtimestamp(time.time())
            date = d.strftime("%Y-%m-%d")
            hour = d.strftime('%H')
            print("============= current date %s , hour:  %s " % (date, hour))
            # 定时
            if hour == '07': 
                # 未成功发送
                if not is_sended: 
                    # 今日有日程
                    if date in arrEvents: 
                        # 今日日程数量 > 0
                        if len(arrEvents[date]) > 0: 
                            try: 
                                # 发送邮件
                                self.sendMail(arrEvents[date])
                                # 标记今日邮件发送成功
                                is_sended = True
                                print('email send ok')
                            except Exception as e: 
                                # 发送邮件时出错了
                                print('got exception while sending email')
                                print(e)
                                # 标记今日邮件未发送成功
                                is_sended = False
            else: 
                # 小时数字不为07
                # 标记(今日或明日)邮件未发送成功
                is_sended = False
            # 60秒重试一次
            time.sleep(60)

    def sendMail(self, events): 
        """send mail
        https://docs.python.org/2/library/smtplib.html
        """
        my_mail = "tett00335@gmail.com"
        # 用换行连接今日的多个日程
        msg = email.message_from_string('\n'.join(events))
        msg['From'] = my_mail
        msg['To'] = my_mail
        # 标题
        msg['Subject'] = "calendar events "

        #s = smtplib.SMTP("smtp.gmail.com", 587)
        #s = smtplib.SMTP("smtp.gmail.com", 25)
        #s.ehlo()
        #s.starttls()
        s = smtplib.SMTP_SSL("smtp.gmail.com", 465)
        s.ehlo()
        # 邮箱名  密码
        s.login(my_mail, 'abc000-=')
        # 收件人 发件人
        s.sendmail(my_mail, my_mail, msg.as_string())
        s.quit()

# a function convert string to time
# 把string类型的日期转成int,
# 如果转化出错，会抛出异常，主要是用来验证string是否符合 YYYY-mm-dd的格式。
# 符合格式则无异常
def strtotime(string, format_string = "%Y-%m-%d"): 
    tuple = time.strptime(string, format_string)
    return int(time.mktime(tuple))

# 把arrEvents保存到文件中
# 格式为 日期日程
# 如果某天有多个日程，则会出现多行。
def save(): 
    """ save all events to file.
    """
    with open(filename, 'w') as f: 
        for (date, events) in arrEvents.items(): 
            # 日程数量为0，则不保存
            if len(events) == 0: 
                continue
            for event in events: 
                line = '%s%s' % (date, event)
                f.write(line + '\n')

# 以上都是各种class或者function的定义。
# 真正的程序从这里执行。

# event file name
# 每次用户新增或删除日程之后，日程都会保存到这个文件中。
# 格式为 日期日程
# 如果某天有多个日程，则会出现多行。
# 可以用文本编辑器直接打开这个文件看一看
filename = "event.db"

# all the events group by date.
# each date has a event list.
# 全部的日程都保存在这个字典里，以日期为key， 
# 同一天内的多个日程是一个list结构。
# 比如 arrEvents['2017-11-11'] = ['event_1', 'event_2', 'event_3']
# arrEvents['2017-12-04'] = ['event_11', 'event_22', 'event_33']
arrEvents = dict()

print("loading...")
# load from event file.
# if the file exists
# 从文件中加载已经保存的日程 
if os.path.exists(filename): 
    with open(filename) as f: 
        # line by line
        for line in f: 
            # split into 2 parts
            arrColumns = line.strip().split('')
            date = arrColumns[0]
            event = arrColumns[1]
            # add to arrEvents
            if date not in arrEvents: 
                arrEvents[date] = list()
            arrEvents[date].append(event)

# start a new thread to send mail.
t = myThread()
# t.start 会在[后台]自动调用 myThread里面的run()方法
t.start()
#t.join()


# the big loop
while True: 
    print(arrEvents)
    cmd = input("""pls input a command number:
1 create new event
2 delete event
3 query event
] """)

    # create
    if cmd == "1": 
        # loop until user input a VALID date
        while True: 
            date = input("pls input a date YYYY-mm-dd] ")
            try: 
                t = strtotime(date)
            except Exception as e: 
                # wrong format, go to next loop
                print(e)
                continue
            # valid format, break the loop.
            break

        event = input("pls input a event] ")
        if date not in arrEvents: 
            arrEvents[date] = list()
        print('adding %s to %s' % (event, date))
        # update arrEvents
        arrEvents[date].append(event)
        # save to file.
        save()

        continue

    # delete
    if cmd == "2": 
        # loop until user input a VALID date
        while True: 
            date = input("pls input a date YYYY-mm-dd] ")
            try: 
                t = strtotime(date)
            except Exception as e: 
                print(e)
                continue
            break

        if date not in arrEvents: 
            print ("no events")
            continue

        if len(arrEvents[date]) == 0: 
            print ("no events.")
            continue

        index = 1
        for e in arrEvents[date]: 
            print('%s %s' % (index, e))
            index += 1 

        # loop until user input a VALID date
        while True: 
            index = input("pls input a index to delete] ")
            try: 
                index = int(index)
            except Exception as e: 
                print (e)
                continue
            # index out of range
            if index > len(arrEvents[date]) or index <= 0 : 
                print("index out of range")
            else: 
                break

        # delete from arrEvents
        del arrEvents[date][index - 1]

        # save to file.
        save()

        continue

    # query
    if cmd == "3": 
        # loop until user input a VALID date
        while True: 
            date = input("pls input a date YYYY-mm-dd] ")
            try: 
                t = strtotime(date)
            except Exception as e: 
                print(e)
                continue
            break
        if date not in arrEvents: 
            print ("no events")
            continue
        if len(arrEvents[date]) == 0: 
            print ("no events.")
            continue
        index = 1
        for e in arrEvents[date]: 
            print('%s %s' % (index, e))
            index += 1 
        continue

