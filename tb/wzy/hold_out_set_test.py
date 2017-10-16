#!/usr/bin/env python
# -*- coding: utf-8 -*-

from sklearn.naive_bayes import MultinomialNB,BernoulliNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.linear_model import SGDClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.svm import SVC,LinearSVC
from sklearn import tree

from sklearn.multiclass import OneVsRestClassifier
from sklearn.feature_selection import SelectKBest, chi2
from sklearn.datasets import load_svmlight_file
from sklearn import metrics
from sklearn import model_selection
import time
import sys
import numpy as np

# naive_bayes  Classifier
def naive_bayes_classifier(train_x, train_y):
    clf = MultinomialNB(alpha=0.01)
    clf = BernoulliNB(alpha=0.01)
    clf.fit(train_x, train_y)
    return clf

# knn Classifier
def knn_classifier(train_x, train_y):
    clf = KNeighborsClassifier(n_neighbors=10,n_jobs=10)
    clf.fit(train_x, train_y)
    return clf

# SGDClassifier
def sgd_classifier(train_x, train_y):
    clf = SGDClassifier(alpha=0.0001, max_iter=50, penalty='l2',n_jobs=10)
    clf.fit(train_x, train_y)
    return clf

# LogisticRegression
def logistic_regression_classifier(train_x, train_y):
    clf = LogisticRegression(penalty='l1',n_jobs=1)
    clf.fit(train_x, train_y)
    return clf

# liblinear
def liblinear_classifier(train_x,train_y):
    clf = LinearSVC(penalty='l1', loss='squared_hinge', dual=False)
    clf.fit(train_x, train_y)
    return clf

# RandomForestClassifier
def random_forest_classifier(train_x, train_y):
    clf = RandomForestClassifier(n_estimators=50,n_jobs=10)
    clf.fit(train_x, train_y)
    return clf

# Decision Tree Classifier
def decision_tree_classifier(train_x, train_y):
    clf = tree.DecisionTreeClassifier()
    clf.fit(train_x, train_y)
    return clf

# GBDT(Gradient Boosting Decision Tree) Classifier
def gradient_boosting_classifier(train_x, train_y):
    clf = GradientBoostingClassifier(n_estimators=100)
    clf.fit(train_x, train_y)
    return clf

# SVM Classifier
def svm_classifier(train_x, train_y):
    svr = OneVsRestClassifier(SVC(kernel='rbf', probability=True),n_jobs=10)
    svr.fit(train_x, train_y)
    return svr


class HoldOutSetTest(object): 
    """ HoldOutSetTest
    """

    def __init__(self): 
        """__init__
        """
        self.arrClassifiers = {
            'NB': naive_bayes_classifier,
            'SGD': sgd_classifier,
            'LR': logistic_regression_classifier,
            'RF': random_forest_classifier,
            'DT': decision_tree_classifier,
            'LIBLINEAR': liblinear_classifier,
            #'GBDT': gradient_boosting_classifier,
            'KNN': knn_classifier,
            #'SVM': svm_classifier,
        }
        self.arrEva = dict()
        for (k, v) in self.arrClassifiers.items(): 
            self.arrEva[k] = {
                'acc': [],
                'precision': [],
                'recall': [],
                'f1score': [],
                'train_time': [],
                'predict_time': [],
            }

    def test(self, X_train, X_test, y_train, y_test): 
        """test
        """
        for  (classifier_name, clsf) in self.arrClassifiers.items(): 
            print "*************************** [%s] ********************" % (classifier_name)
            start_time = int(time.time())
            model = clsf(X_train, y_train)
            train_time = int(time.time()) - start_time
            predict = model.predict(X_test)
            predict_time = int(time.time()) - start_time - train_time

            #http://scikit-learn.org/stable/modules/generated/sklearn.metrics.accuracy_score.html
            acc = metrics.accuracy_score(y_test, predict)
            ave = 'weighted'
            precision = metrics.precision_score(y_test, predict, average=ave)
            recall = metrics.recall_score(y_test, predict, average=ave)
            f1score = metrics.f1_score(y_test, predict, average=ave)

            metrics_time = int(time.time()) - start_time - train_time - predict_time

            print "acc: %.2f%% train_time: %.2f predict_time: %.2f  metrics_time: %.2f" %  (
                acc * 100, train_time, predict_time, metrics_time)
            self.arrEva[classifier_name]['acc'].append(acc)
            self.arrEva[classifier_name]['precision'].append(precision)
            self.arrEva[classifier_name]['recall'].append(recall)
            self.arrEva[classifier_name]['f1score'].append(f1score)
            self.arrEva[classifier_name]['train_time'].append(train_time)
            self.arrEva[classifier_name]['predict_time'].append(predict_time)
            target_names = [
                'GOOD',
                'POOR',
            ]
            print metrics.classification_report(y_test, predict, target_names=target_names)

    def output(self): 
        """output summary
        """
        print "*************************** summary *******************************"
        fmt='%12s%12s%12s%12s%12s%12s%12s'
        print fmt % ('classifier','acc','precision','recall','f1-score','train_time', 'predict_time')
        for (classifier_name, row) in self.arrEva.items(): 
            acc = np.mean(row['acc'])
            precision = np.mean(row['precision'])
            recall  = np.mean(row['recall'])
            f1score = np.mean(row['f1score'])
            train_time = np.mean(row['train_time'])
            predict_time = np.mean(row['predict_time'])
            print fmt % tuple( [classifier_name] + [str('%.3f'%x) for x in [acc,precision,recall,f1score,train_time, predict_time] ])

    def go(self): 
        """go
        """
        X_train, y_train = load_svmlight_file('./train.svm')
        X_test, y_test = load_svmlight_file('./test.svm')
        # http://scikit-learn.org/stable/modules/generated/sklearn.model_selection.KFold.html#sklearn.model_selection.KFold
        intTrainSize,   intTrainDim = X_train.shape
        intTestSize,    intTestDim = X_test.shape
        print "train size: %d test size: %d, dimension: %d" % (intTrainSize, intTestSize, intTrainDim)
        self.test(X_train, X_test, y_train, y_test)

        self.output()

if __name__ == "__main__": 
    o = HoldOutSetTest()
    o.go()
