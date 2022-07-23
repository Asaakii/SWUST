# 建立SVM模型
import numpy as np
import pandas as pd
from sklearn.svm import SVC

train_Scaler = pd.read_csv('./tmp/wine_train_Scaler.csv')
wine_target_train = pd.read_csv('./tmp/wine_train_label.csv')
test_Scaler = pd.read_csv('./tmp/wine_test_Scaler.csv')
wine_target_test = pd.read_csv('./tmp/wine_test_label.csv')
print('训练集形状：', train_Scaler.shape, '\n',
      '训练集标签形状：', wine_target_train.shape, '\n',
      '测试集形状', test_Scaler.shape, '\n',
      '测试集标签形状', wine_target_test.shape)
# 构建SVM模型，并预测测试集结果。
svm = SVC().fit(train_Scaler, wine_target_train.values.ravel())
print('建立的SVM模型为：', svm)

# SVM模型预测结果
wine_target_pred = svm.predict(test_Scaler)
print('测试集的预测结果为：\n', wine_target_pred)

# 预测报告
from sklearn.metrics import classification_report

# 模型评估
print('SVM模型分类报告：\n', classification_report(wine_target_test, wine_target_pred))

# 绘制每个类的Roc曲线
from sklearn.preprocessing import label_binarize
from sklearn.metrics import roc_curve, auc
import matplotlib.pyplot as plt

# 将标签二值化
y_real = label_binarize(wine_target_test, classes=[1, 2, 3])
y_pred = label_binarize(wine_target_pred, classes=[1, 2, 3])
y_real.shape, y_pred.shape

# 计算每一类的ROC
fpr = dict()
tpr = dict()
roc_auc = dict()
for i in range(3):
    fpr[i], tpr[i], _ = roc_curve(y_real[:, i], y_pred[:, i])
    roc_auc[i] = auc(fpr[i], tpr[i])

# 绘制
plt.figure(figsize=(6, 6))

colors = ["blue", 'red', 'black']
lines = ['-', ':', '--']
for i in range(3):
    plt.plot(fpr[i], tpr[i], color=colors[i], linestyle=lines[i],
             label='ROC curve of class {0} (area = {1:0.2f})'
                   ''.format(i + 1, roc_auc[i]))
plt.legend()
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('ROC curves for multi-class classification')
plt.show()
