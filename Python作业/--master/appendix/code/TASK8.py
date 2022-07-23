'''TASK8：分析随日期变化，评分变化情况。
生成：“复仇者联盟4随日期而变化的评分情况折线图“一个文件。'''
# 由于此代码是从文件“成功统计不同城市的评分平均数”里改编而来，故部分变量的名称中含有city
import pandas as pd
import re
import matplotlib.pyplot as plt

# 导入city_short和scores这两列的数据成一个dataframe
f = pd.read_csv(r'outtime切成两列.csv')
f = pd.DataFrame(f)
two = f.ix[:, ['one', 'scores']]
print(two)

# 让m['one']中的时间排序下来而不是散乱着
print(two.dtypes)  # 查看里面每一列的格式
two = two.sort_values(by='one')  # 让two中的数据按照one这一列中的时间来有顺序地排下来
print(two)
two.reset_index(inplace=True)  # 上面按时间排之后索引也会变掉，然后最后出来的答案就错了？？？不知道为什么，不过这一行代码可以把索引值变回1,2,3……然后出来的答案又对了
print(two)
print('-' * 20)

# 选出名为“xx"的城市，然后将其对应的scores求平均

# 第一步：取出city_short和scores里面的数据分别弄成一个列表
city_short_list = two["one"].tolist()
scores_list = two["scores"].tolist()
print(city_short_list)
print(scores_list)

# 第二步：查看里面有哪些重复出现的日期

# 统计列表中某个值出现的次数
List = city_short_list
d1 = {}
for i in List:
    if List.count(i) >= 1:
        d1[i] = List.count(i)
print(d1)
print('-' * 20)

# 取出字典第二个值作为一个列表
chengshi, number1 = d1.keys(), d1.values()
print(chengshi)
print(number1)  # 这里有个number
print('-' * 20)

# 把dict_keys变成列表，这样这个列表里面就是所有重复出现的城市的名字了
names = chengshi
name_list1 = re.findall('\'(.*?)\'', str(names))
print(name_list1)
x = range(len(name_list1))
print(x)
print('-' * 20)

# 第二步：对城市进行循环,得到每个城市的分数
fenshu = []
for p in name_list1:
    print(p)
    a = two[(two.one == p)].index.tolist()
    print(a)
    beijing_ = 0
    for m in a:
        number = scores_list[m]
        beijing_ = beijing_ + number
    print(beijing_)
    len2 = len(a)
    print(len2)
    beijing_num = float("{:.1f}".format(beijing_ / len2))
    print(beijing_num)  # 这样能够算出平均分
    fenshu.append(beijing_num)
print(fenshu)

# 绘图
from pylab import *  # 支持中文

mpl.rcParams['font.sans-serif'] = ['SimHei']
plt.plot(x, fenshu, marker='o', mec='r', mfc='w')  # 圆圈，红色，中心白
plt.xticks(x, names, rotation=45)
for a, b in zip(x, fenshu):
    plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
plt.subplots_adjust(bottom=0.15)
plt.xlabel(u"具体日期")  # X轴标签
plt.ylabel("用户打分的平均分")  # Y轴标签
plt.title("复仇者联盟4随日期而变化的评分情况")  # 标题
plt.savefig('./复仇者联盟4随日期而变化的评分情况折线图')
plt.show()
