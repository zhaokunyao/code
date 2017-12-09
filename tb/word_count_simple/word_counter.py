#encoding=utf8

# 一个字典，key是每个单词，value是单词出现次数
arrWordCounter = dict()

# 所有单词出现的总次数
totalCount = 0

# 打开文件
with open('./doc.txt') as f: 
    # 遍历文件中的每一行
    for line in f: 
        # 去掉结尾的空行
        line = line.strip()
        print 'parsing [', line, ']'
        # 空格切分
        arrWords = line.split()

        # 遍历切分出来的每一个单词
        for word in arrWords: 
            # 去掉单词结尾的各种符号
            word = word.strip('.?!,"`')
            # 转为小写
            word = word.lower()
            # word长度大于0
            if len(word) > 0: 
                print "get ", word
                # 总数 + 1
                totalCount +=1 
                # 此单词出现次数 + 1
                if word not in arrWordCounter: 
                    arrWordCounter[word] = 0
                arrWordCounter[word] += 1

print 'total words: ', totalCount
for (word, count) in arrWordCounter.items(): 
    print 'word:[', word, '] count: ', count 
