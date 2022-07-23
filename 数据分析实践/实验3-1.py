import numpy as np
import matplotlib.pyplot as plt

# 使用numpy库读取人口数据
data = np.load('./dataset/populations.npz', allow_pickle=True)

plt.rcParams['font.sans-serif'] = 'SimHei'  # 设置中文显示
name = data['feature_names']  # 提取其中的feature_names数组，视为数据的标签
values = data['data']  # 提取其中的data数组，视为数据的存在位置
values = values[:-2, :]  # 取数组的前20行数据,消除nan
values = values[::-1]  # 按时间排序

p1 = plt.figure(figsize=(12, 12))  # 确定画布大小
pip1 = p1.add_subplot(2, 1, 1)  # 绘制子图1
plt.scatter(values[:, 0], values[:, 2], marker='o', color='yellow')
plt.scatter(values[:, 0], values[:, 3], marker='D', color='green')
plt.scatter(values[:, 0], values[:, 4], marker='p', color='blue')
plt.scatter(values[:, 0], values[:, 5], marker='s', color='purple')
plt.xlabel('时间')
plt.ylabel('总人口（万人）')
plt.xticks(values[:, 0])
plt.legend(['男性', '女性', '城镇', '乡村'])
plt.title('1996-2015年各类人口随时间变化散点图')

plt.subplots_adjust(hspace=0.4)  # 调整子图距离

pip2 = p1.add_subplot(2, 1, 2)  # 绘制子图2
plt.plot(values[:, 0], values[:, 2] / values[:, 3], 'y-')
plt.plot(values[:, 0], values[:, 4] / values[:, 5], 'g-.')
plt.xlabel('时间')
plt.ylabel('人口比例')
plt.xticks(values[:, 0])
plt.legend(['男女人口比例', '城乡人口比例'])
plt.title("1996-2015年各类人口比例随时间变化折线图")
plt.show()
