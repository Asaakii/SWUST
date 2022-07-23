#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 19 22:58:02 2020

@author: zhengsc
"""


import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeRegressor

boston = datasets.load_boston()
X = boston.data
y = boston.target
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=666)


dt_reg = DecisionTreeRegressor()
dt_reg.fit(X_train, y_train)

print("准确率:",dt_reg.score(X_test, y_test))