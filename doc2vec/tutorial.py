 # -*- coding: UTF-8 -*-
import gensim, logging
import os
from gensim.models.doc2vec import Doc2Vec,LabeledSentence
from gensim.models import Doc2Vec
import gensim.models.doc2vec
 
asin=set()
category=set()
class LabeledLineSentence(object):
    def __init__(self, filename=object):
        self.filename =filename
        self.test_cut_raw_1 = None
    def __iter__(self):
        with open(self.filename,'r') as infile:
            data=infile.readlines();
            #print "length: ", len(data)
        id = 0
        for uid,line in enumerate(data):
            #print "line:",line
            uid = str(id)
            asin.add(uid)
            if (uid == "0"): 
                self.test_cut_raw_1 = line.split()
            id += 1
            #print "asin: ",asin
            category.add(line.split("\t")[1])
            yield LabeledSentence(words=line.split("\t")[0].split(" "), tags=[uid])
print 'success'
 
logging.basicConfig(format = '%(asctime)s : %(levelname)s : %(message)s', level = logging.INFO)
sentences =LabeledLineSentence('./data/22')
model = Doc2Vec(sentences, size=50, window = 5, min_count=1)
model.save('product_bpr_model50.txt')
print  'success1'
 
print "doc2vecs length:", len(model.docvecs)
outid = file('product_bpr_id_vector50.txt', 'w')
for id in asin:
    outid.write(id+"\t")
    # print "feature length in : ", id, len(model.docvecs[id])
    for idx,lv in enumerate(model.docvecs[id]):
        outid.write(str(lv)+" ")
    outid.write("\n")
outid.close()

# [('\xe4\xbb\x8b\xe4\xb9\x8e', 0.9822391271591187), ]
# ??? how to get doc?
# print sentences.test_cut_raw_1
inferred_vector = model.infer_vector(sentences.test_cut_raw_1)
for tpl in model.most_similar([inferred_vector], topn=3): 
    print tpl
