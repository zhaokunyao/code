# 文件说明

## convert.py
python程序，读取模板文件、数据文件和图片库，生成网页文件
里面有一些配置，可以直接代码和注释。

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



# 运行说明
python ./convert.py
会生成result.html
使用浏览器打开即可。


# 配置修改
很抱歉并没有搞出来一个配置文件;
convert.py中有一些配置：
self.arrConf = {
    # 数据文件名
    "csv_file": "./exampleData.csv",
    # 图片目录
    "img_dir": "./FigureRepositroy",
    # 模板文件名
    "tpl_file": "./tpl.html",
    # 模板中的变量
    "tpl_params": {
        "csv_header": "####CSV_HEADER####",
        "csv_body": "####CSV_BODY####",
        "img_dir": "####IMG_DIR####"
    },
    # 输出文件
    "output_file": "result.html"
}

tpl.html中：
// 图片默认高度
var img_height = "200px";
// 图片默认宽度
var img_width = "200px";


