#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 19 11:20:13 2020

@author: zhengsc
"""


import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from matplotlib.colors import ListedColormap
    
iris = datasets.load_iris()
X = iris.data[:,2:] # iris有四个特征，这里取后两个，形成一个坐标点
y = iris.target
# 绘图
plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.scatter(X[y==2,0],X[y==2,1])
plt.show()


# 创建决策树对象，最大深度max_depth为2层，criterion评判标准为entropy（熵）
dt_clt = DecisionTreeClassifier(max_depth=2,criterion='entropy')
# 将训练数据送给模型
dt_clt.fit(X,y)

# 绘制决策边界
def plot_decision_boundary(model, axis): # model是模型，axis是范围
    x0, x1 = np.meshgrid(
        np.linspace(axis[0], axis[1],int((axis[1]-axis[0])*100)).reshape(-1,1),
        np.linspace(axis[2], axis[3],int((axis[3]-axis[2])*100)).reshape(-1,1),
    )
    X_new = np.c_[x0.ravel(), x1.ravel()]
    y_predict = model.predict(X_new)
    zz = y_predict.reshape(x0.shape)
    custom_cmap = ListedColormap(['#EF9A9A','#FFF59D','#90CAF9'])
    plt.contourf(x0, x1, zz, linewidth=5, cmap=custom_cmap)

# 数据可视化
plot_decision_boundary(dt_clt, axis=[0.5,7.5,0,3])
plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.scatter(X[y==2,0],X[y==2,1])
plt.show()

