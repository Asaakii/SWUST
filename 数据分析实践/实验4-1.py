import pandas as pd

Data = pd.read_csv("./dataset/Training_Master.csv", encoding="gbk")

# 查看ndim维度、shape形状、memory_usage占用内存
print("维度为：", Data.ndim)
print("大小为：", Data.shape)
print("占用内存为：\n", Data.memory_usage())

# describe方法
print("描述性统计为：\n", Data.describe())


# 删除值相同或者全空的列
def Drop_same_null(data):
    before = data.shape
    print("删除前的的大小为：", before)
    TheNull = data.describe().loc["count"] == 0  # 数据为空
    for i in range(0, len(TheNull)):
        if TheNull[i]:
            data.drop(TheNull.index[i], axis=1, inplace=True)
    TheStd = data.describe().loc["std"] == 0  # 数据相同,标准差为0
    for j in range(0, len(TheStd)):
        if TheStd[j]:
            data.drop(TheStd.index[j], axis=1, inplace=True)
    after = data.shape
    print("删除后的大小为：", after)


print("删除相同或者全空的列后：")
Drop_same_null(Data)
print(Data.columns)

# print(Data[['UserInfo_2', 'UserInfo_3']].groupby('UserInfo_2').count())
