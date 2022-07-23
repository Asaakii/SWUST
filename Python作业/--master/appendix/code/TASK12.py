'''TASK12：分析《复仇者联盟4》发布短评用户的会龄分布。
生成：“复仇者联盟4用户会龄分布情况柱状图“一个文件。'''
# 用短评发表时间减去加入时间，得到两者之间差的天数，记为days
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

# 接下来先看一下最大值和最小值，可以用来考虑分段筛选
nums = []
for m in days_list:
    m = int(m)  # 变成int类型之后，下面排序时就不会错了
    nums.append(m)
print(nums)
nums.sort()  # 让nums从小到大排序
print(nums)
print(len(nums))
max = nums[len(nums) - 1]  # 取排序后的最后一个值作为最大值
min = nums[0]  # 取排序后的第一个值作为最小值
print("-------------最大最小值结果-------------")
print("最大值：", max)  # 最大值： 5038
print("最小值：", min)  # 最小值： 0。
# 4945, 4946, 4947, 4968, 4971, 4974, 5018, 5028, 5037, 5038这是后面比较大的几个数，挺均衡的
# 0, 1, 58, 64, 71, 71, 117, 118, 153, 157, 172这是前面比较小的几个数，接下来比较均衡了，所以160之前的数据没有几个
# print("-------------最大最小值位置-------------")
# print(nums.index(max))
# print(nums.index(min))

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

fenzu = []
for k in range(0, 14):
    num1 = 0
    for m in nums:
        if (m >= 365 * k) & (m <= 365 * (k + 1)):
            num1 = num1 + 1
    fenzu.append(num1)
print(fenzu)
print(sum(fenzu))

# 接下来就是画图了
# 绘制柱状图
from pylab import *  # 支持中文

mpl.rcParams['font.sans-serif'] = ['SimHei']


def draw_bar(labels, quants):
    width = 0.4
    ind = np.linspace(0.5, 9.5, 14)  # 如果要改labels, quants，那么这里的20也要改，这指的是横坐标有几个数据
    # make a square figure
    fig = plt.figure(1)
    ax = fig.add_subplot(111)
    # Bar Plot
    ax.bar(ind - width / 2, quants, width, color='green')
    # Set the ticks on x-axis
    ax.set_xticks(ind)
    # ax.set_xticklabels(labels,rotation=45)
    ax.set_xticklabels(labels)
    # labels
    ax.set_xlabel('会龄所在范围（单位：年）')
    ax.set_ylabel('该范围对应用户人数')
    # title
    ax.set_title('复仇者联盟4用户会龄分布情况柱状图', bbox={'facecolor': '0.8', 'pad': 5})
    plt.grid(True)
    plt.savefig("bar3.jpg")
    plt.show()
    plt.close()


# 调用上面这个柱状图的函数
labels = fanwei
quants = fenzu
draw_bar(labels, quants)

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

# #绘制折线图
# x = range(len(fanwei))
# from pylab import *  # 支持中文
# mpl.rcParams['font.sans-serif'] = ['SimHei']
# plt.plot(x, fenzu, marker='o', mec='r', mfc='w')#圆圈，红色，中心白
# # plt.legend()  # 让图例生效
# # plt.xticks(x, fanwei, rotation=45)#这应该是倾斜45°
# plt.xticks(x, fanwei)
# # plt.xticks(x, name_list1)
# #绘制数字标签:下面两句话可以让数字在折线图上显示出来
# for a, b in zip(x, fenzu):
#      plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
# plt.subplots_adjust(bottom=0.15)
# plt.xlabel(u"会龄所在范围（单位：年）")  # X轴标签
# plt.ylabel("该范围对应用户人数")  # Y轴标签
# plt.title("复仇者联盟4用户会龄分布情况")  # 标题
# plt.savefig('./复仇者联盟4用户会龄分布情况折线图')#保存图片，貌似如果这句话放在plt.show()后面的话，就图片不会显示出来了，生成的是空白图片
# plt.show()
