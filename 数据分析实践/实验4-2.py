import pandas as pd

df = pd.read_csv("./dataset/Training_LogInfo.csv", encoding="gbk")

# 使用to_datetime函数转换登录信息表的时间字符串。
df["Listinginfo1"] = pd.to_datetime(df["Listinginfo1"])
print(df)
df["LogInfo3"] = pd.to_datetime(df["LogInfo3"])

# 新增3列，取值分别为字段‘Listinginfo1’的时间信息：年、月、周
df['year'] = df["Listinginfo1"].dt.year
df['month'] = df["Listinginfo1"].dt.month
df['week'] = df["Listinginfo1"].dt.week
print(df)

# 计算用户信息更新表和登录信息表中两时间的差,分别以日、小时、分钟计算
timeDeltaLogInfo = df["Listinginfo1"] - df["LogInfo3"]
print("计算时间差以日为单位：\n", timeDeltaLogInfo)


def TransformDayIntoHour(data):
    for i in range(0, len(data)):
        data[i] = data[i].total_seconds() / 3600
    return data


print("计算时间差以小时为单位：\n", TransformDayIntoHour(timeDeltaLogInfo))


def TransformDayIntoMinute(data):
    for i in range(0, len(data)):
        data[i] = data[i].total_seconds() / 60
    return data


timeDeltaLogInfo = df["Listinginfo1"] - df["LogInfo3"]
print("计算时间差以分钟为单位：\n", TransformDayIntoMinute(timeDeltaLogInfo))
