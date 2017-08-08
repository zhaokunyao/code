# 运行说明
python ./convert.py
会生成result.html
使用浏览器打开即可。


# 配置修改
很抱歉并没有搞出来一个配置文件;
convert.py中有一些配置：
```
self.arrConf = {
    # 数据文件名
    "csv_file": "./exampleData.csv",
    # 图片目录
    "img_dir": "./FigureRepositroy",
    # 模板文件名
    "tpl_file": "./tpl.html",
    # title
    "title": "报告的title",
    # 模板中的变量
    "tpl_params": {
        "csv_header": "####CSV_HEADER####",
        "csv_body": "####CSV_BODY####",
        "img_dir": "####IMG_DIR####"
    },
    # 输出文件
    "output_file": "result.html"
}
```

tpl.html中：
```
// 图片默认高度
var img_height = "200px";
// 图片默认宽度
var img_width = "200px";
```

另外，如果需要新增字段，建议增加到Rate字段后面，这样应该能够自适应。
如果增加新字段到Rate字段之前，需要修改一下tpl.html中的
```
var f2 = parseFloat(arr_body[9]);
```
中的index:9 它表示的是rate字段的index。



# 文件说明

## convert.py
python程序，读取模板文件、数据文件和图片库，生成网页文件
里面有一些配置，可以直接看代码和注释。

## tpl.html
模板文件，里面有三个主要的标签：分别是图片目录，表头数据和表格数据， 另外也定义了图片的默认大小。

## result.html
convert.py生成出来的结果文件，可以直接用浏览器打开。每次调用convert.py的时候， 会清空此文件并重新生成。所以，注意进行备份。

## zhao.html 
是用来调试的网页文件，发布时可以进行删除。

## js目录
是需要使用到的js文件， 目前只有一个jquery.


## 其它文件
同目录里面还需要有 exampleData.csv(数据文件) 和 FigureRepositroy（图片目录）


# 数据过滤功能
输入之后，直接回车就可以完成筛选功能，当然也可以点击“过滤”按钮进行筛选。
点击"重置"按钮会清除筛选输入框，并展示全部的数据。

## item匹配
不区分大小写
最左前缀进行匹配。
比如 输入AAAA 会匹配到 AAAAGROUP , aaaaxxxx 等数据
如果输入GROUP就不会匹配到AAAAGROUP了;

## rate大于
数值比较。
如果输入非数字，可能会有异常。


