#encoding=utf8

import gensim, logging
logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

sentences = [['first', 'sentence'], ['second', 'sentence']]
# train word2vec on the two sentences
model = gensim.models.Word2Vec(sentences, min_count=1)

print model.similarity('first', 'second')
print model.similarity('first', 'sentence')
print model.similarity('second', 'sentence')

