'''TASK9：1.分析用户常居城市分布情况，即每个城市对应有多少用户，并图表可视化；
             2.将所有城市简化成2个字，如“山西太原”简化为“山西”，并放入“合并2.xlsx”中，以便于后续统计不同城市的评分平均数。
生成：“合并2.xlsx”，“复仇者联盟4短评用户常居城市分布情况折线图 ”，“复仇者联盟4用户常居城市分布情况饼图”三个文件。
'''
# 用于分析用户常居城市分布情况，并将所有城市简化成2个字，放入“合并2.xlsx”中，以便于后续统计不同城市的评分平均数

import pandas as pd

# 读取excel中的城市一列
df = pd.read_excel("E:/Apython/pa_qu_ying_ping/我做的豆瓣_复仇者联盟_终极之战的爬虫/A开始分析爬出来的数据/城市/绘制地理图表/绘制地理图表成功文件/合并.xlsx",
                   usecols=[2], names=None)  # 读取项目名称列,不要列名
df_li = df.values.tolist()
result1 = []
for s_li in df_li:
    result1.append(s_li[0])
# 把四个字的地方都变成2个字
import re

result = []
for i in range(len(result1)):
    result2 = re.findall('^[\u4E00-\u9FA5]{2}', result1[i])
    try:
        result2 = str(result2).split('\'')[1]
    except:
        result2 = ''
    result.append(result2)
print(result)

# 把result加入到dataframe里面的最后一列
import pandas as pd

f1 = pd.read_excel(r'合并.xlsx')
f1.columns = ["name", "id", "city", "jointime", "content", "outtime", "scores", "degree"]
f1['city_short'] = result

# 把原来的列和新加入的city_short这一列一起输出到‘合并2’这个文件
pd.DataFrame(f1).to_excel("合并2.xlsx", sheet_name="123", index=False, header=True)

# 统计列表中某个值出现的次数
List = result
d1 = {}
for i in List:
    if List.count(i) >= 1:
        d1[i] = List.count(i)
print(d1)
print('-' * 20)

# 取出字典第二个值作为一个列表
chengshi, number1 = d1.keys(), d1.values()
print(chengshi)
print(number1)

'''
#绘制饼图
import matplotlib.pyplot as plt
name = chengshi
plt.rcParams['font.sans-serif']='SimHei'#设置中文显示
plt.figure(figsize=(6,6))#将画布设定为正方形，则绘制的饼图是正圆
label=name#定义饼图的标签，标签是列表
explode=[0.05] * 33#设定各项距离圆心n个半径，注意这里的个数要和label的个数相同
values=number1
plt.pie(values,explode=explode,labels=label,autopct='%1.1f%%')#绘制饼图
plt.title('复仇者联盟4用户常居城市分布情况')#绘制标题
plt.savefig('./复仇者联盟4用户常居城市分布情况饼图')#保存图片
plt.show()
'''

from pylab import *  # 支持中文

mpl.rcParams['font.sans-serif'] = ['SimHei']

# 把d1_keys变成列表，这样就可以画折线图了
names = chengshi
name_list1 = re.findall('\'(.*?)\'', str(names))
print(name_list1)
x = range(len(name_list1))
print(x)

# 把d1_values也变成列表
number_list1 = re.findall('\d+\d*\d*', str(number1))
y1 = number_list1
print(y1)
y = []
for i in range(len(y1)):
    y2 = float(y1[i])  # 变成float的话，画图时y轴数据就会按照顺序来了
    y.append(y2)
print(y)

# 然后就可以画折线图了
plt.plot(x, y, marker='o', mec='r', mfc='w')  # 圆圈，红色，中心白
plt.xticks(x, names)
'''绘制数字标签:下面两句话可以让数字在折线图上显示出来
for a, b in zip(x, y):
     plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
'''
plt.subplots_adjust(bottom=0.15)
plt.xlabel(u"城市名称")  # X轴标签
plt.ylabel("用户数量")  # Y轴标签
plt.title("复仇者联盟4短评用户常居城市分布情况")  # 标题
plt.savefig('./复仇者联盟4短评用户常居城市分布情况折线图')  # 保存图片，貌似如果这句话放在plt.show()后面的话，就图片不会显示出来了，生成的是空白图片
plt.show()
