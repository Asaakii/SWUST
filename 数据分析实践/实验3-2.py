import numpy as np
import matplotlib.pyplot as plt

# 支持中文
plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

data = np.loadtxt("./dataset/StudentsPerformance.csv", delimiter=",", dtype=str, usecols=2, skiprows=1)
groups, counts = np.unique(data, return_counts=True)
p2 = plt.figure(figsize=(12, 12))
a2 = p2.add_subplot(2, 2, 1)
plt.pie(counts, labels=groups, autopct='%1.1f%%')
plt.title("学生种族分布饼状图")
plt.show()

data = np.loadtxt("./dataset/StudentsPerformance.csv", delimiter=",", dtype=int, usecols=(6, 7, 8), skiprows=1)
# 绘制第一幅子图
p1 = plt.figure(figsize=(12, 12))
ax1 = p1.add_subplot(2, 2, 1)
plt.hist(data,rwidth=0.5)
plt.title("学生成绩分布直方图")
plt.xticks(range(0, 101, 10))
plt.xlabel("成绩（分）")
plt.ylabel("学生人数（人）")
plt.legend(["math score", "reading score", "writing score"])

plt.subplots_adjust(hspace=0.4)  # 调整子图距离

# 绘制第二幅子图
ax2 = p1.add_subplot(2, 2, 4)
plt.boxplot(data)
plt.title("学生成绩分布箱线图")
plt.xticks(range(1, 4), ["math score", "reading score", "writing score"])
plt.yticks(range(0, 101, 10))
plt.ylabel("成绩（分）")
plt.show()
