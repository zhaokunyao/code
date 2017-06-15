import time

def solution(S):
    # write your code in Python 2.7
    ret = 0
    arrTimes = {
        "Mon": [],
        "Tue": [],
        "Wed": [],
        "Thu": [],
        "Fri": [],
        "Sat": [],
        "Sun": []
    }
    arrKeys = ["Mon", 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'];

    arrLines = S.split("\n")
    for line in arrLines: 
        arrTmp = line.split(" ")
        arrTimes[arrTmp[0]].append(arrTmp[1]);

    arrSlices   = [];
    for key in arrKeys: 
        if key in arrTimes: 
            arrTimes[key].sort()

    s = 0;
    for key in arrKeys: 
        if len(arrTimes[key]) == 0: 
            s += 24 * 60;
            continue

        time_old = '00:00'
        for time in arrTimes[key]: 
            arrTmp = time.split('-')
            s += cal(time_old, arrTmp[0])
            time_old  = arrTmp[1];
            arrSlices.append(s)
            s = 0;
        if time_old != '24:00': 
            s += cal(time_old, "24:00")

    if s >0: 
        arrSlices.append(s)

    return max(arrSlices)

def cal(time_old, time_new): 
    """ 10:00  16:00 
    """
    time_old = time_old + ":00"
    one = 0

    if time_new == "24:00":
        time_new = "23:59"
        one = 1
    time_new = time_new + ":59"

    t1  = strtotime("2017-11-11 " + time_old)
    t2  = strtotime("2017-11-11 " + time_new)

    return (t2-t1)/60 + one



def strtotime(string, format_string = "%Y-%m-%d %H:%M:%S"):
    tuple = time.strptime(string, format_string)
    return int(time.mktime(tuple))


S = """Mon 01:00-23:00
Tue 01:00-23:00
Wed 01:00-23:00
Thu 01:00-23:00
Fri 01:00-23:00
Sat 01:00-23:00
Sun 01:00-21:00"""
print solution(S)

S = """Sun 10:00-20:00
Fri 05:00-10:00
Fri 16:30-23:50
Sat 10:00-24:00
Sun 01:00-04:00
Sat 02:00-06:00
Tue 03:30-18:15
Tue 19:00-20:00
Wed 04:25-15:14
Wed 15:14-22:40
Thu 00:00-23:59
Mon 05:00-13:00
Mon 15:00-21:00"""

print solution(S)

