为什么要用xrange这个函数? 
因为在python2里面用习惯了。。。这里也可以直接用range函数的。

word count
设计思路：
1) 预处理：去掉html代码、转为小写、
2) 一个一个字符地遍历text， 遇到非允许的字符就停止，
并用正则判断已经遍历过的字符组合在一起是否为合法的word
并保存到dict中计算出现次数。
3) 排序
4) 结构化返回(arrData)

细节：
由于text里面含有html代码，而文档中要求
“HTML comments should be removed and HTML tags and words within HTML tags should not be counted”
所以先使用HTMLParser过滤掉html代码， 这样就得到了很多的text片断，
然后用 ' ' 把这些片断join起来，成为新的text.

Viii.All words should be converted to lower-case before being counted
所以要把text转成全部小写

iV. The words contain em-dashes should be separated
所以把 text中的 --- 替换为空格
把text中的 -- 也替换为空格
这里一定要先替换三个的，再替换二个的， 如果反过来，三个的就变成一个的了， 这样就不对了。

初始化totalWordCount变量为0， 这个是总的word出现的次数（不去重、全局）。
初始化一个dict  arrWords ， 用来统计每个word出现的次数

写一个while循环， 从头开始,一个字符一个字符地遍历text，
如果当前字符符合要求[a-z0-9'\-_]， 则继续向后遍历text
如果当前字符不符合上述要求， 则判断一下刚刚遍历过的数据是否为一个word：
    这个判断条件有三种：
    r"^('?[a-z])[a-z0-9'\-_]*([a-z]|[0-9]|s')$"  如果符合这个正则，则为一个word，
    如果不符合这个正则，且word长度为1，且word符合 [a-z0-9'\-_]，也认为是一个word， 比如A，应该也算是一个word.
    如果值为 s'  也认为是一个word.
    为什么不用正则完全处理呢？ 因为符合这三个条件的正则太复杂了，写不出来。

如果刚遍历过的数据是一个word，则更新dict的计数与全局的计数
然后从当前位置继续新一轮的遍历

最终会到达text的结尾， 这时候就自动跳出了while循环，
但是还有一份刚刚遍历的数据未进行处理， 应按照上述的流程再判断它是否为一个word，
以及相应的更新计数。

然后使用 sorted 方法，对dict按照value进行排序（升序）
然后使用 list的slice方法取出前10 [0:10] ，也就是least often.
然后再使用  [:-10-1:-1]，取出最后10个， 也就是most often.
-1 表示从尾部开始取数字。  

最后拼装一个arrData结构，它有三个key: 
total_word_count(总数) most(10 most often )  least(10 least often)

最后再讲解一下那个比较复杂的正则是怎样写出来的：
r"^('?[a-z])[a-z0-9'\-_]*([a-z]|[0-9]|s')$"  

^('?[a-z])表示 以一个或零个'开头，然后是a-z中的某一个字符， 即文档里所说：start with a letter or start with an apostrophe followed by a letter 
[a-z0-9'\-_]* 表示0个或者多个允许的字符(i) only consist of ASCII letters, ASCII digits, apostrophes, hyphens, and underscores
([a-z]|[0-9]|s')$  表示以[a-z]中的一个字符或者[0-9]中的一个数字或者 s'结尾, 即文档中所说的
 (iii) end with (a) a letter, (b) a digit, or (c) an apostrophe preceded by the letter s,




 cgi流程:
 1) 判断是GET请求还是POST请求
 2) 若是GET请求就print出html表单
 3) 若是POST请求就做有效性验证，
 3.1) 若输入非法或者从url中获取不到数据，则print html表单及出错信息，让用户重新提交。
 3.2) 若输入合法，则调用上述wordCount方法，对text进行分析
 3.3) 输出
 3.3.1) 为了明文输出text中的html代码，需要调用cgi.escape方法
 3.3.2) 为了能让text中的换行正常显示出来， 需要把换行\n替换为<br />\n， 这样浏览器就能把换行正常渲染出来了。
 3.3.3) 判断total_word_count是否为1， 以决定显示'words' or 'word'
 3.3.4) 一次性输出二个表格。


