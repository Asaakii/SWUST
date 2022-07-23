#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 19 22:15:16 2020

@author: a111
"""


import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier


X,y = datasets.make_moons(noise=0.25,random_state=666)

plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.show()

def plot_decision_boundary(model, axis): # model是模型，axis是范围
    x0, x1 = np.meshgrid(
        np.linspace(axis[0], axis[1],int((axis[1]-axis[0])*100)).reshape(-1,1),
        np.linspace(axis[2], axis[3],int((axis[3]-axis[2])*100)).reshape(-1,1),
    )
    X_new = np.c_[x0.ravel(), x1.ravel()]

    y_predict = model.predict(X_new)
    zz = y_predict.reshape(x0.shape)

    from matplotlib.colors import ListedColormap
    custom_cmap = ListedColormap(['#EF9A9A','#FFF59D','#90CAF9'])
    
    plt.contourf(x0, x1, zz, linewidth=5, cmap=custom_cmap)
    

# 如果在构建时不传参数，则默认是使用基尼系数进行特征划分
# 不限定max_depth，则决策树会一直向下划分，直到每一个节点的基尼系数为0为止
print("无剪枝")
dt_clf1 = DecisionTreeClassifier()
dt_clf1.fit(X,y)
    
plot_decision_boundary(dt_clf1, axis=[-1.5,2.5,-1.0,1.5])
plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.show()



print("预剪枝-树最大深度")
dt_clf2 = DecisionTreeClassifier(max_depth=2)
dt_clf2.fit(X,y)

plot_decision_boundary(dt_clf2, axis=[-1.5,2.5,-1.0,1.5])
plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.show()


print("预剪枝-最小样本划分")
dt_clf3 = DecisionTreeClassifier(min_samples_split=10)
dt_clf3.fit(X,y)

plot_decision_boundary(dt_clf3, axis=[-1.5,2.5,-1.0,1.5])
plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.show()


print("预剪枝-最小样本节点")
dt_clf4 = DecisionTreeClassifier(min_samples_leaf=10)
dt_clf4.fit(X,y)

plot_decision_boundary(dt_clf4, axis=[-1.5,2.5,-1.0,1.5])
plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.show()

print("预剪枝-最大样本节点")
dt_clf5 = DecisionTreeClassifier(max_leaf_nodes=4)
dt_clf5.fit(X,y)

plot_decision_boundary(dt_clf5, axis=[-1.5,2.5,-1.0,1.5])
plt.scatter(X[y==0,0],X[y==0,1])
plt.scatter(X[y==1,0],X[y==1,1])
plt.show()