import pandas as pd
import numpy as np

df = pd.read_csv("./dataset/Training_LogInfo.csv", encoding="gbk")

# 使用groupby方法对登录信息表进行分组
LogInfoGroup = df.groupby("Idx")
print('分组后的登录信息表为：\n', LogInfoGroup.head())

# 使用agg方法求取分组后的最早和最晚登录时间，最早借款成交时间
df2 = pd.DataFrame()
df2["earliest_login"] = df[["Idx", "LogInfo3"]].groupby("Idx").agg(np.min)
df2["latest_login"] = df[["Idx", "LogInfo3"]].groupby("Idx").agg(np.max)
df2["earliest_loan"] = df[["Idx", "Listinginfo1"]].groupby("Idx").agg(np.min)
print(df2)

# 使用apply函数在每一行上计算最早借款成交时间与最早登录时间的差值
print('最早借款成交时间与最早登录时间的差值:\n', LogInfoGroup.agg({'LogInfo3': np.min, 'Listinginfo1': np.min}).apply(
    lambda df: pd.to_datetime(df["Listinginfo1"]) - pd.to_datetime(df["LogInfo3"]), axis=1))
