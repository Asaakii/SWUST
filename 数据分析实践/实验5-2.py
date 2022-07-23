# 数据预处理及K-Means模型构建
import pandas as pd
from sklearn.cluster import KMeans  # 导入分类器库

# 读取训练集数据
wine_train_Scaler = pd.read_csv('./tmp/wine_train_Scaler.csv')
wine_train_label = pd.read_csv('./tmp/wine_train_label.csv')
wine_train_label.columns = ['label']  # 重命名列名
# 构建并训练模型
kmeans = KMeans(n_clusters=3, random_state=123).fit(wine_train_Scaler)
print('构建k-means模型为：\n', kmeans)

# 轮廓系数评估KMeans模型
from sklearn.metrics import silhouette_score
import matplotlib.pyplot as plt

silhouettteScore = []
for i in range(2, 11):
    kmeans = KMeans(n_clusters=i, random_state=123).fit(wine_train_Scaler)
    score = silhouette_score(wine_train_Scaler, kmeans.labels_)
    silhouettteScore.append(score)
plt.figure(figsize=(10, 6))
plt.plot(range(2, 11), silhouettteScore, linewidth=1.5, linestyle="-")
plt.xlabel("the number of clusters")
plt.ylabel("silhouettte score")
plt.show()

# 导入SSE方法的评价函数
sse_score_list = []
for i in range(2, 11):
    # 构建并训练模型
    kmeans = KMeans(n_clusters=i, random_state=123).fit(wine_train_Scaler)
    score = kmeans.inertia_
    sse_score_list.append(score)
plt.figure(figsize=(10, 6))
plt.plot(range(2, 11), sse_score_list, linewidth=1.5, linestyle="-")
plt.xlabel("the number of clusters")
plt.ylabel("SSE")
plt.show()

from sklearn.metrics import fowlkes_mallows_score

# 导入FMI方法的评价函数
fmi_score_list = []
for i in range(2, 11):
    # 构建并训练模型
    kmeans = KMeans(n_clusters=i, random_state=123).fit(wine_train_Scaler)
    score = fowlkes_mallows_score(wine_train_label['label'], kmeans.labels_)
    fmi_score_list.append(score)
plt.figure(figsize=(10, 6))
plt.plot(range(2, 11), fmi_score_list, linewidth=1.5, linestyle="-")
plt.xlabel("the number of clusters")
plt.ylabel("FMI")
plt.show()

# 使用Calinski-Harabasz指数评价K-Means聚类
from sklearn.metrics import calinski_harabasz_score

harabasz_scor_list = []
for i in range(2, 11):
    # 构建并训练模型
    kmeans = KMeans(n_clusters=i, random_state=1).fit(wine_train_Scaler)
    score = calinski_harabasz_score(wine_train_Scaler, kmeans.labels_)
    harabasz_scor_list.append(score)
plt.plot(range(2, 11), harabasz_scor_list, linewidth=1.5, linestyle="-")
plt.xlabel("the number of clusters")
plt.ylabel("calinski_harabaz")
plt.show()
