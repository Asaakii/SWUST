'''TASK13：分析会龄对评分的影响。
生成：“复仇者联盟4用户不同会龄阶段对应评分折线图 “一个文件。'''
# 这一个py文件是把每个会龄层次对应的用户的评分找出来，然后求平均值，画以这个会龄层次为横坐标，以平均值为纵坐标的这样一幅图
import pandas as pd

f = pd.read_csv(r'jointime和outtime和scores.csv')
days = pd.DataFrame(pd.to_datetime(f['one']) - pd.to_datetime(f['jointime']))
print(days)

# 从上面得到的入会年龄这个dataframe中拿到了入会年龄数据列表，记为days_list
list = days[0].tolist()
# print(list)
import re

days_list = re.findall('Timedelta\(\'(.*?) days 00:00:00', str(list))
print(days_list)

# 变成int类型，好计算
nums = []
for m in days_list:
    m = int(m)
    nums.append(m)
print(nums)

# 把会龄和其他东西一起放着
f['会龄'] = nums
print(f)

# 接下来开始分类别筛选然后计数
fanwei = []
for k in range(0, 14):
    a1 = k
    a2 = k + 1
    fanwei1 = str(a1) + "-" + str(a2)
    print(fanwei1)
    fanwei.append(fanwei1)
print(
    fanwei)  # 这样fanwei就是['0-1', '1-2', '2-3', '3-4', '4-5', '5-6', '6-7', '7-8', '8-9', '9-10', '10-11', '11-12', '12-13', '13-14']了，显示出来的就是第几年到第几年

scores_list = f['scores'].tolist()
print(scores_list)
pingjunfen_list = []
for k in range(0, 14):
    num1 = 0  # num1是个数，这一个范围里面有几个用户评分，所以不能删
    zong = 0
    pingjunfen = 0
    for i in range(len(nums)):
        if (nums[i] >= 365 * k) & (nums[i] <= 365 * (k + 1)):
            num1 = num1 + 1
            zong = zong + scores_list[i]
            pingjunfen = float("{:.1f}".format(zong / num1))
    pingjunfen_list.append(pingjunfen)
print(pingjunfen_list)

# 绘制折线图
x = range(len(fanwei))
from pylab import *  # 支持中文

mpl.rcParams['font.sans-serif'] = ['SimHei']
plt.plot(x, pingjunfen_list, marker='o', mec='r', mfc='w')  # 圆圈，红色，中心白
# plt.legend()  # 让图例生效
plt.xticks(x, fanwei)
# 绘制数字标签:下面两句话可以让数字在折线图上显示出来
for a, b in zip(x, pingjunfen_list):
    plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
plt.subplots_adjust(bottom=0.15)
plt.xlabel(u"会龄所在范围（单位：年）")  # X轴标签
plt.ylabel("该范围对应评分平均分")  # Y轴标签
plt.title("复仇者联盟4用户不同会龄阶段对应评分情况")  # 标题
plt.savefig('./复仇者联盟4用户不同会龄阶段对应评分折线图')
plt.show()

# 接下来就是画图了
# 绘制柱状图
# from pylab import *  # 支持中文
# mpl.rcParams['font.sans-serif'] = ['SimHei']
# def draw_bar(labels, quants):
#     width = 0.4
#     ind = np.linspace(0.5, 9.5, 14)#如果要改labels, quants，那么这里的20也要改，这指的是横坐标有几个数据
#     # make a square figure
#     fig = plt.figure(1)
#     ax = fig.add_subplot(111)
#     # Bar Plot
#     ax.bar(ind - width / 2, quants, width, color='green')
#     # Set the ticks on x-axis
#     ax.set_xticks(ind)
#     # ax.set_xticklabels(labels,rotation=45)
#     ax.set_xticklabels(labels)
#     # labels
#     ax.set_xlabel('会龄所在范围（单位：年）')
#     ax.set_ylabel('该范围对应评分平均分')
#     # title
#     ax.set_title('复仇者联盟4用户不同会龄阶段对应评分情况', bbox={'facecolor': '0.8', 'pad': 5})
#     plt.grid(True)
#     plt.savefig("复仇者联盟4用户不同会龄阶段对应评分柱状图.jpg")
#     plt.show()
#     plt.close()
# #调用上面这个柱状图的函数
# labels = fanwei
# quants = pingjunfen_list
# draw_bar(labels, quants)

# #绘制饼图
# name = fanwei
# plt.rcParams['font.sans-serif']='SimHei'#设置中文显示
# plt.figure(figsize=(6,6))#将画布设定为正方形，则绘制的饼图是正圆
# label=name#定义饼图的标签，标签是列表
# explode=[0.05] * 20#设定各项距离圆心n个半径，注意这里的个数要和label的个数相同
# values=fenzu
# plt.pie(values,explode=explode,labels=label,autopct='%1.1f%%')#绘制饼图
# plt.title('复仇者联盟4用户会龄分布情况（单位：days）')#绘制标题
# plt.savefig('./复仇者联盟4用户会龄分布情况饼图')#保存图片
# plt.show()
