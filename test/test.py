import math
import time
import xml.etree.ElementTree as ET

def strtotime(string, format_string = "%Y%m%d:%H%M%S"):
    tuple = time.strptime(string, format_string)
    return int(time.mktime(tuple))

# import the xml file
tree = ET.parse('a.xml')
root = tree.getroot()

arrTimeTaken = []

# access each element
for child in root: 
    # Log_Entry
    print '======================================='
    print "child.tag:", child.tag
    for ele in child: 
        print "ele.tag: ", ele.tag
        # Parse the Time into a sensible integer value
        if ele.tag == "Time": 
            print 'ele.text:', strtotime(ele.text)
        else: 
            print "ele.text:", ele.text

        if ele.tag == "Time_Taken": 
            arrTimeTaken.append(int(ele.text))
            if int(ele.text) > 500: 
                speed_ele = ET.Element('speed')
                speed_ele.text = 'slow'
                child.append(speed_ele)
                print 'mark slow', ele.text

# mean
def mean(nums): 
    sum = 0.0
    for n in nums: 
        sum = sum + n
    return sum / len(nums)

# standard deviation
def stdDev(nums): 
    xbar = mean(nums)
    sumDev  = 0.0
    for n in nums: 
        dev = n - xbar
        sumDev  += dev ** 2
    return math.sqrt(sumDev/len(nums))

print arrTimeTaken

print 'mean: ', mean(arrTimeTaken)
print 'standard deviation: ', stdDev(arrTimeTaken)


tree.write('./b.xml')
