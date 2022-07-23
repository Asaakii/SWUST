'''TASK6：分析用户发表短评数量随时刻的变化情况。
生成：“复仇者联盟4用户发表短评数量随时刻的变化情况折线图“一个文件。'''
# 题目：分析用户发表短评数量随时刻的变化情况
import pandas as pd
import matplotlib.pyplot as plt

dakai = pd.read_excel(r'合并.xlsx')
data = pd.DataFrame(dakai)
print(data)
data['time'] = pd.to_datetime(data['outtime']).apply(lambda x: x.hour)
print(data['time'])
num = data['time'].value_counts().sort_index()
print(num)
# 稍微处理下数据，能让图更加好看
y = num.tolist()
print(y)
x = range(len(y))
print(x)
# 绘图
plt.plot(x, y, marker='o', mec='r', mfc='w')
plt.xticks(x, x)
plt.xlabel('具体时刻')
plt.ylabel('短评发表数量')
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False  # 上面两行是为了让标题不乱码，能够正常显示中文
for a, b in zip(x, y):
     plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
plt.subplots_adjust(bottom=0.15)
plt.title('复仇者联盟4用户发表短评数量随时刻的变化情况')
plt.savefig('./复仇者联盟4用户发表短评数量随时刻的变化情况折线图')
plt.show()
