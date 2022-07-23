import numpy as np
import matplotlib.pyplot as plt

# 设置字体格式
plt.rcParams['font.family'] = ['simhei']

# 定义初始条件
maxIter = 1200  # 最大迭代时间，即热扩散时间
x = y = 40  # 二维空腔的长和宽
area = 1  # 点面积

# 各边界温度
top = 400  # 上边界
bottle = 300  # 下边界
left = 300  # 左边界
right = 300  # 右边界

# 内部节点温度
nodes = 300

# 导热系数
ratio = 0.0675

# 设置色彩插值和色彩图谱
color_interpolation = 50
color_Map = plt.cm.jet

# 设置网状网格
[X, Y] = np.meshgrid(np.arange(0, x), np.arange(0, y))

# 设置数组大小，用估计的方式设置内部值
T = np.empty((len(X), len(Y)))
T.fill(nodes)
print(T)

# 设置边界条件
T[x - 1, :] = top
T[0, :] = bottle
T[:, 0] = right
T[:, y - 1] = left

# 迭代（假设在最大迭代为1200时收敛）
flag = 0
for iteration in range(0, maxIter + 1):  # 时间层
    for i in range(1, x - 1, area):  # X方向
        for j in range(1, y - 1, area):  # Y方向
            T[i, j] = T[i, j] + ratio * (
                        (T[i + 1, j] - 2 * T[i, j] + T[i - 1, j]) + (T[i, j + 1] - 2 * T[i, j] + T[i, j - 1]))

    if flag % 100 == 0:
        fig = plt.figure(figsize=(6, 4))
        # 设置轮廓
        plt.title("温度轮廓(第{}时刻)".format(iteration))
        plt.contourf(X, Y, T, color_interpolation, cmap=color_Map)

        # 设置色标
        plt.colorbar()

        # 在绘图窗口中显示结果
        plt.show()
        flag = 0
    flag = flag + 1
