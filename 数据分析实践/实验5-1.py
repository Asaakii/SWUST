# 读取wine数据集
import pandas as pd

wine = pd.read_csv('./dataset/wine.csv', encoding='gb18030')
# wine有179条记录 每条记录第一列为分类标签，有13个属性
print('wine数据集的shape为：', wine.shape)
print('wine数据集的前五行：\n', wine.head())

# 拆分wine数据集
wine_data = wine.iloc[:, 1:14]
wine_label = wine.iloc[:, 0]
print('wine数据集的标签为：\n', wine_label)

# 对wine数据集进行划分
from sklearn.model_selection import train_test_split

wine_train, wine_test, wine_train_label, wine_test_label = train_test_split \
    (wine_data, wine_label, test_size=0.2, random_state=42)
wine_train_label.to_csv('./tmp/wine_train_label.csv', index=False)
wine_test_label.to_csv('./tmp/wine_test_label.csv', index=False)
print('wine原始数据集数据的形状为：', wine_data.shape)
print('wine训练集数据的形状为：', wine_train.shape)
print('wine训练集标签的形状为：', wine_train_label.shape)
print('wine测试集数据的形状为：', wine_test.shape)
print('wine测试集标签的形状为：', wine_test_label.shape)

from sklearn.preprocessing import MinMaxScaler

# 标准化wine训练集
Scaler = MinMaxScaler().fit(wine_train)  # 生成规则
# 将规则应用于wine_quality训练集
wine_train_Scaler = Scaler.transform(wine_train)
# 将wine_train_Scaler转为DataFrame
wine_train_Scaler = pd.DataFrame(wine_train_Scaler)
# 重命名wine_train_Scaler
wine_train_Scaler.columns = wine_train.columns
wine_train_Scaler.to_csv('./tmp/wine_train_Scaler.csv', index=False)
print('离差标准化后wine训练集前5行的数据为：\n', wine_train_Scaler.head())

# 标准化wine测试集
Scaler = MinMaxScaler().fit(wine_test)  # 生成规则
# 将规则应用于wine_quality训练集
wine_test_Scaler = Scaler.transform(wine_test)
# 将wine_test_Scalerr转为DataFrame
wine_test_Scaler = pd.DataFrame(wine_test_Scaler)
# 重命名wine_test_Scaler
wine_train_Scaler.columns = wine_test.columns
wine_test_Scaler.to_csv('./tmp/wine_test_Scaler.csv', index=False)
print('离差标准化后wine测试集前5行的数据为：\n', wine_test_Scaler.head())

# 对wine数据集降维
from sklearn.decomposition import PCA

model = PCA(n_components=2, random_state=42)
X_transnform = model.fit_transform(wine_train_Scaler)
print('PCA降维前wine测试集数据的形状为：', wine_train_Scaler.shape)
print('PCA降维后wine测试集数据的形状为：', X_transnform.shape)

# 降维结果可视化
import matplotlib.pyplot as plt

plt.figure(figsize=(10, 8))

colors = ["", 'red', 'black', 'orange']
for i in [1, 2, 3]:
    plt.scatter(X_transnform[wine_train_label == i, 0], X_transnform[wine_train_label == i, 1], alpha=0.7, c=colors[i],
                label="class {}".format(i))
plt.legend()
plt.show()
