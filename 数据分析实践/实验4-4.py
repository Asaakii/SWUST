import pandas as pd
import numpy as np


df = pd.read_csv("./dataset/Training_LogInfo.csv", encoding="gbk")


# 使用pivot_table函数进行长宽表转换：登录信息表Training_LogInfo.csv以'Idx'为行索引，列索引为'LogInfo2'，值为‘LogInfo1’，聚合函数为count生成透视表
df2 = pd.pivot_table(df, index="Idx", columns="LogInfo2", values="LogInfo1", aggfunc=np.count_nonzero)
print(df2)


# 使用crosstab函数进行长宽表转换：登录信息表Training_LogInfo.csv以'Idx'为行索引，列索引为'LogInfo2'，值为‘LogInfo1’，聚合函数为count，生成交叉表
df3 = pd.crosstab(df["Idx"], columns="LogInfo2", values="LogInfo1", aggfunc=np.count_nonzero)
print(df3)
