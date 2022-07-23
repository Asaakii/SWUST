import pandas as pd
import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE

# 中文和负号的正常显示
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False


# 读取数据
def read_data(path):
    data = pd.read_csv(path)

    # 输出数据基本信息
    print('维度：', data.ndim)
    print('大小：', data.shape)
    desc = data.describe()
    print('数据描述：\n', desc)

    return data


# 训练模型
def train_model(k, X):
    model = KMeans(n_clusters=k, init='k-means++', n_init=10, max_iter=300, random_state=0)
    model.fit(X)
    return model


# 绘制不同聚类中心数下的离差平方和折线图
def draw_distortions(distortions, clu_center):
    plt.plot(clu_center, distortions, 'bo-', mfc='r')
    plt.xlabel('簇中心的个数 k')
    plt.ylabel('离差平方和')
    plt.title('肘方法确定 k-means 聚类中簇的最佳数量')
    plt.show()


# 绘制聚类结果
def draw_cluster_result(model, k, X):
    # 记录分类结果及其中心点
    labels = model.labels_
    centroids = model.cluster_centers_
    X = np.vstack((X, centroids))

    # 使用TSNE算法进行降维
    tsne = TSNE()
    data = tsne.fit_transform(X)  # 进行数据降维,并返回结果

    # 分离聚类中心和样本值
    data = pd.DataFrame(data)
    num = data.shape[0]
    center = data.iloc[num - k:num]  # 聚类中心
    data_tsne = data.iloc[:num - k]  # 样本点
    data_tsne.index = labels  # 聚类标签

    # 绘制样本分布
    plt.figure(figsize=(8, 6))
    color = ['lightgreen', 'orange', 'lightblue', 'black', 'green', 'blue', 'purple', 'magenta']
    for i in range(k):
        d = data_tsne[data_tsne.index == i]
        plt.scatter(d[0], d[1], c=color[i], marker='o')

    # 绘制聚类中心点
    plt.scatter(center[0], center[1], c='red', marker='x', s=100)
    plt.show()


# 数值型数据分布情况
def distribute_data(model, data, col_name):
    data = data[col_name]
    data.index = model.labels_
    target_data = []
    category = []
    for i in range(model.n_clusters):
        target_data.append(data[data.index == i])
        category.append('类别' + str(i))

    fig, (ax0, ax1) = plt.subplots(nrows=2, ncols=1)  # 新建画布，并且划分子图

    # 绘制第一个子图
    ax0.hist(target_data, bins=20, histtype='bar', label=category)  # 直方图
    ax0.set_title(col_name + '分布直方图')
    ax0.set_xlabel('数值')
    ax0.set_ylabel('人数')
    ax0.legend()  # 显示图形的图例

    # 绘制第二个子图
    ax1.boxplot(target_data, patch_artist=True, vert=False, labels=category,
                boxprops={'color': 'black', 'facecolor': 'darkgray'},  # 箱体属性
                medianprops={'color': 'black'},  # 中位数属性
                capprops={'color': 'black'},  # 箱线图顶端和末端线条的属性
                whiskerprops={'color': 'black'})  # 设置须的属性
    ax1.set_title(col_name + '分布箱线图')

    fig.tight_layout()  # 防止出现遮挡情况
    plt.show()


if __name__ == "__main__":
    # 读取数据
    path = r'./dataset/players.csv'
    data = read_data(path)

    # 选择聚类数据以及转换数据格式
    columns = ['得分', '命中率', '三分命中率', '罚球命中率', '场次', '上场时间']
    X = np.array(data[columns])

    # 使用肘方法判断聚类中心数
    distortions = []  # 保存不同超参数对应模型的聚类偏差
    num_center = range(1, 11)  # 聚类中心数
    for k in num_center:
        model = train_model(k, X)
        distortions.append(model.inertia_)

    # 绘制离差平方和
    draw_distortions(distortions, num_center)

    # 训练最终模型
    k = eval(input('输入聚类中心数：'))
    model = train_model(k, X)

    # 绘制聚类结果
    draw_cluster_result(model, k, X)

    # 绘制某个字段数据分布
    col_name = '罚球命中率'
    distribute_data(model, data, col_name)
