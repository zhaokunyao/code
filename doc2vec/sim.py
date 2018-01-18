#coding:utf-8
#使用doc2vec 判断文档相似性
from gensim import models,corpora,similarities
from gensim.models.doc2vec import TaggedDocument,Doc2Vec
import os

def a_sub_b(a,b):
    ret = []
    for el in a:
        if el not in b:
            ret.append(el)
    return ret
#stop = [line.strip().decode('utf-8') for line in open('stopword.txt').readlines() ]
stop = []

#读取文件
raw_documents=[]
walk = os.walk(os.path.realpath("./data2/"))
for root, dirs, files in walk:
    #print root
    #print dirs
    #print files
    for name in files:
        f = open(os.path.join(root, name), 'r')
        raw = str(os.path.join(root, name))+" "
        raw += f.read()
        raw_documents.append(raw)

#构建语料库
corpora_documents = []
doc=[]            #输出时使用，用来存储未经过TaggedDocument处理的数据，如果输出document，前面会有u
test_cut_raw_1 =[]
for i, item_text in enumerate(raw_documents):
    words_list =item_text.split()
    if i == 0: 
        test_cut_raw_1 = words_list
    words_list=a_sub_b(words_list,list(stop))
    document = TaggedDocument(words=words_list, tags=[i])
    corpora_documents.append(document)
    doc.append(words_list)
#创建model
model = Doc2Vec(size=50, min_count=1, iter=10)
model.build_vocab(corpora_documents)
model.train(corpora_documents, total_examples=model.corpus_count, epochs=model.iter)
print('#########', model.vector_size)


test_cut_raw_1 = "印度 乘客 坐火车 顶部 被 桥梁 剐 蹭 致 28 人 死伤   　 　 国际 在线 消息 ： 印度 一列 快速 列车 1 日 在 北方邦 行驶 期间 发生 重大 伤亡事故 ， 造成 至少 14 名 乘客 死亡 ， 另有 14 人 受伤 ， 其中 6 人 伤势 严重 。   　 　 印度 媒体 1 日晚 援引 警方 的 消息 报道 说 ， 该 列车 当天 在 行驶 中 通过 一个 低矮 的 天桥 时 ， 一些 坐在 车顶 的 乘客 相继 被 刮 坠地 ， 造成 重大 伤亡 。   　 　 警方 说 ， 多数 遇难 乘客 是 东部 比哈尔邦 的 青年 ， 他们 在 北方邦 报名 应征 边境 警察部队 后 坐车 返回 。 由于 车厢 内 挤满 了 乘客 ， 许多 应征 青年 不顾 交通安全 法规 ， 爬 上 了 车顶 ， 坐在 上面 返乡 。         __label__affairs".split()
inferred_vector = model.infer_vector(test_cut_raw_1)
sims = model.docvecs.most_similar([inferred_vector], topn=3)
print(sims)  #sims是一个tuples,(index_of_document, similarity)
for i in sims:
    similar=""
    print('################################')
    print i[0]
    for j in doc[i[0]]:
        similar+=j
    print similar

