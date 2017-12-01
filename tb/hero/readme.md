# usage

## linux without IDE
输入make命令进行编译
输入make test执行测试任务(make test之前必须先make)
输入make run执行程序 (make run之前必须先make)

## IDE
build and run according to IDE you chose.


# 文件

## Graph.java  
程序入口

## Warehouse.java
构建nxn的 warehouse
安装门、安装hero、安装items

## Room.java  
room

## Item.java
item

## Hero.java
hero

## Test.java  
test.


# 设计

## room 
每个room有四面墙，每个墙默认都没有门。
北面墙是  -----
南面墙也是 -----
东面墙是 |
西面墙也是|
但是这样拼起来就是
-----
|   |
-----
和文档中的例子不一样，
所以又额外增加二块内容：
在北面墙与东面墙之间， 以及东面墙与南面墙之间。
如下图：
-----
|   |
|   |
|   |
-----
有门的话就是这样：
--D--
|   |
D   D
|   |
--D--
共五行，这五行在程序中分别用字符串来表示：
nWall
side
ewWall
side
sWall

每面墙上是否有门的判断， 就直接判断:
nWall若包含字符D则表示北面墙有门
sWall若包含字符D则表示南面墙有门
ewWall若是以字母D开头，则表示西面墙有门
ewWall若是以字母D结尾，则表示东面墙有门

给每面墙设置门的时候， 就直接做了字符串替换。

## warehouse
### 数据结构
使用一维数组roomList来保存nxn个room.
每个room的index这样分布：
第一行：0 1 2 3 4 5 ... ... size -1
第二行：1*size, 1*size+1, 1*size+2 ....  1*size + size -1
第三行：2*size, 2*size+1, 2*size+2 ....  2*size + size -1
........
......
最后一行：(size-1) *size, (size-1) *size +1, (size-1)*size +2, ... ...  (size-1) * size + size -1

### 随机设置门的流程：
如果warehouse中只有一个room，则无法给此room设置门,因为它的四面墙都是 external wall.
如果有多个room, 则遍历这些room，分别给他们设置门: 

首先取得这个room不包含门的所有的墙，称为wallList。
然后判断wallList中的每面墙是否为external wall, 
如果是的话，则把它从wallList中删除 。

然后，打乱wallList的顺序（为了随机的效果）。
从wallList头部取出一面墙,称为wall， 给它设置上门。
既然已经给wall设置了门，则需要把wall从wallList中删除。
根据wall，可以推算出当前room的相邻room需要被设置门的墙,称为neighbour wall。
南-北,北-南,东-西,西-东，   wall与neighbour wall总是相对应的

然后，根据wall与当前room的index, 可以推算出相邻room的index，
有了相邻room的index,就可以给它也设置上门了。


如果当前room门的数量不足2， 则继续上面的流程，再设置另外一个门。

### 是否为external wall的判断方法：
由上述roomList的数据结构可知，
如果wall为'north'， 且index在 [0, size-1] 则为external wall
如果wall为'south', 且index在[(size-1)*size,  (size-1)*size + size -1]，则为external wall
如果wall为'west', 且index 可以被size整除，则为external wall
如果wall为'east'， 且index被size除了之后，余数为 size-1， 则为external wall

### 根据wall与当前room的index计算相邻room index的方法：
同样由上述roomList的数据结构可以推断出相邻的 room index,
公式可以直接看代码。


### 输出warehouse的方法： 
如ass8.pdf中所述，输出warehouse时，
asking each room todeliver its string representation 
and then breaking those strings into (5) component parts 
并按行聚合，
之后，按行输出这些component parts.

## graph
程序入口， 负责初始化Warehouse并启动游戏


# 测试重点

--  Room初始化之后没有门
--  Room设置一个door之后， door的总量是否正确(+1)， 确认目标wall上出现了door.
--  Room设置多个door之后， door的总量是否正确(+n)， 确认目标wall上出现了door.
--  Rood在某个已经有了door 的wall上面再次设置door,  door的总量是否正确 (+0), 确认目标wall上是否仍旧有door.
--  warehouse中没有room, 无法设置door， 无法输出
--  warehouse中只有一个room,  则无法设置door
--  warehouse初始化之后，门的总数量为0
--  随机设置完所有door之后， external wall上面不能有door， 且每个Room的door的数量在2-4之间。
--  Warehouse设置一个door之后， door的总量是否正确(+2)，新增door的位置是否正确 。
--  Warehouse加载itemList
--  Warehouse加载hero
--  Warehouse移动hero(正常移动与无法移动)
--  Warehouse执行pickUp事务(hero + item,  room - item) 如果hero无法+item，则room也不应-item
--  Warehouse里执行drop事务(hero - item, room + item)
--  item的set与get方法是否正确 
--  hero的pickUp与drop方法是否正确 ， 在达到或者超出最大capacity的时候是否正确 
--  人工测试： room里面没有item， 则无法pick
--  人工测试： hero包里面没有item， 则无法drop
