'''TASK5：分析用户发表短评数量随日期的变化情况。
生成：“复仇者联盟4用户发表短评数量随日期的变化情况折线图”一个文件。'''
# 目的：任务3.1分析用户发表短评数量随日期的变化情况
import pandas as pd
import matplotlib.pyplot as plt

# 导入
f = pd.read_excel(r'合并.xlsx')
f = pd.DataFrame(f)
two = f['outtime']
# 获取这两列
two = pd.to_datetime(two, format='%Y%m%d %H:%M:%S')
print(two)
# 拆了outtime中的年月日和具体时间,放在m里
two = pd.DataFrame(two, columns=["outtime"])
two['outtime'] = two['outtime'].astype(str)  # 这样就把two中的datetime64[ns]格式的outtime这一列转换成了str格式
m = pd.DataFrame((x.split(' ') for x in two['outtime']), index=two.index, columns=['one', 'two'])
# 将two里面的'outtime'按照two里面的索引two.index，以‘ ’为界限来进行切割，然后切出来的两列分别命名为one和two
print(m)
print('-' * 20)

# 让m['one']中的时间排序下来而不是散乱着
print(m.dtypes)
m = m.sort_values(by='one')
print(m)
print('-' * 20)

# 统计列表中某个值出现的次数
result = m["one"].tolist()
List = result
d1 = {}
for i in List:
    if List.count(i) >= 1:
        d1[i] = List.count(i)
print(d1)
print('-' * 20)
# 取出字典第二个值作为一个列表
riqi, number1 = d1.keys(), d1.values()
print(riqi)
print(number1)  # 这里有个number
# 把d1_keys变成列表，这样就可以画折线图了
import re

names = riqi
name_list1 = re.findall('\d{4}-\d{2}-\d{2}', str(names))
print(name_list1)
x = range(len(name_list1))
print(x)
# 把dict_values也变成列表
number_list1 = re.findall('\d+\d*\d*', str(number1))
y1 = number_list1
print(y1)
y = []
for i in range(len(y1)):
    y2 = float(y1[i])  # 变成float的话，画图时y轴数据就会按照顺序来了
    y.append(int(y2))
print(y)
# 然后就可以画图了
plt.plot(name_list1, y, marker='o', mec='r', mfc='w')  # 圆圈，红色，中心白
from pylab import *  # 支持中文

mpl.rcParams['font.sans-serif'] = ['SimHei']
plt.xticks(x, names, rotation=45)  # 这应该是倾斜45°
# 绘制数字标签:下面两句话可以让数字在折线图上显示出来
for a, b in zip(x, y):
    plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
plt.subplots_adjust(bottom=0.15)
plt.xlabel(u"具体日期")  # X轴标签
plt.ylabel("短评发表数量")  # Y轴标签
plt.title("复仇者联盟4用户发表短评数量随日期的变化情况")  # 标题
plt.savefig('./复仇者联盟4用户发表短评数量随日期的变化情况折线图')  # 保存图片，貌似如果这句话放在plt.show()后面的话，就图片不会显示出来了，生成的是空白图片
plt.show()
