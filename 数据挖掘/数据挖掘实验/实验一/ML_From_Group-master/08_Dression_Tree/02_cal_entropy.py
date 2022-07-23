#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 19 11:54:19 2020

@author: zhengsc
"""



import numpy as np
import matplotlib.pyplot as plt

# 二分类的信息熵
# p可以传递数值，也可以传递向量。因此使用np.log
def entropy(p):
    return -p * np.log(p) - (1-p) * np.log(1-p)

# linspace生成向量x，从0到1均匀取值，绘制出x在不同值时对应的信息熵
x = np.linspace(0.01,0.99,100)

plt.plot(x,entropy(x))
plt.show()