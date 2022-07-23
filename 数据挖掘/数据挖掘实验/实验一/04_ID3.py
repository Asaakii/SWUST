import operator
from math import log

import numpy as np


# 计算经验熵
def calEntropy(dataSet):
    """
    Parameters：
        dataSet：样本数据集D
    Returns：
        entory：经验熵
    """
    # 返回数据集行数
    numEntries = len(dataSet)
    # 保存每个标签（label）出现次数的字典：<label:出现次数>
    labelCounts = {}
    # 对每组特征向量进行统计
    for featVec in dataSet:
        # 提取标签信息
        currentLabel = featVec[-1]
        # 如果标签没有放入统计次数的字典，添加进去
        if currentLabel not in labelCounts.keys():
            labelCounts[currentLabel] = 0
        # label计数
        labelCounts[currentLabel] += 1

    entory = 0.0
    # 计算经验熵
    for key in labelCounts:
        # 选择该标签的概率
        prob = float(labelCounts[key]) / numEntries
        # 利用公式计算
        entory -= prob * log(prob, 2)
    return entory


# 得到当前特征条件下的小类的所有样本集合（即不包含当前特征的特征样本集）
def currentConditionSet(dataSet, curtFeatIndex, categroy):
    """
    Parameters：
        dataSet：样本数据集D
        curtFeatIndex：当前用来划分数据集的特征A的位置
        categories：特征A所有可能分类的集合
    Returns：
        otherFeatSets：不包含当前特征的特征样本集
    """
    otherFeatSets = []
    # 对于数据集中的所有特征向量，抛去当前特征后拼接好的集合
    for featVec in dataSet:
        if featVec[curtFeatIndex] == categroy:
            otherFeatSet = np.append(featVec[:curtFeatIndex], featVec[curtFeatIndex + 1:])
            otherFeatSets.append(otherFeatSet)
    return otherFeatSets


# 在选择当前特征的条件下，计算熵，即条件熵
def calConditionalEnt(dataSet, curtFeatIndex, categories):
    """
    Parameters：
        dataSet：样本数据集D
        curtFeatIndex：当前用来划分数据集的特征A的位置
        categories：特征A所有可能分类的集合
    Returns：
        conditionalEnt：返回条件熵
    """
    conditionalEnt = 0
    # 对于每一个分类，计算选择当前特征的条件下条件熵
    # 比如在选择“年龄”这一特征下，共有“老中青”三个小分类
    for categroy in categories:
        # 得到当前特征条件下的小类的所有样本集合，即不包含当前特征的特征样本集
        # 如得到在选择“青年”这个小类下一共有5个样本，且不包含“年龄”这一特征
        cdtSetCategroy = currentConditionSet(dataSet, curtFeatIndex, categroy)
        # 计算当前特征条件下的小分类，占总分类的比例
        prob = len(cdtSetCategroy) / float(dataSet.shape[0])
        # 累加得到条件熵
        conditionalEnt += prob * calEntropy(cdtSetCategroy)
    return conditionalEnt


# 计算信息增益
def calInfoGain(baseEntropy, dataSet, curtFeatIndex):
    """
    Parameters：
        baseEntropy：划分样本集合D的熵是为H(D)，即基本熵
        dataSet：样本数据集D
        curtFeatIndex：当前用来划分数据集的特征A的位置
    Returns：
        infoGain：信息增益值
    """

    conditionalEnt = 0.0

    # categories是所有特征向量中当前特征的对应值的set集合（去重复）
    # 相当于该特征一共有几种分类，如“年龄”这一特征，分为“老中青”三类
    categories = set(dataSet[:, curtFeatIndex])

    # 计算划分后的数据子集（给定特征A的情况下，数据集D）的条件熵（经验条件熵）H(D|A)
    conditionalEnt = calConditionalEnt(dataSet, curtFeatIndex, categories)

    # 计算信息增益：g(D,A)=H(D)−H(D|A)
    infoGain = baseEntropy - conditionalEnt

    # 打印每个特征的信息增益
    print("第%d个特征的增益为%.3f" % (curtFeatIndex, infoGain))
    return infoGain


# 寻找最优划分
def optimalPartition(dataSet):
    """
    Parameters：
        dataSet：数据集
    Returns：
        打印最优划分结果
    """
    bestInfoGain = -1  # 最佳信息增益初始值
    bestFeatVec = -1  # 最佳划分的特征向量
    # 划分前样本集合D的熵H(D)，即基本熵
    baseEntropy = calEntropy(dataSet)

    # 遍历每一个特征维度（列），得到基于当前特征划分的信息增益
    for curtFeatIndex in range(dataSet.shape[1] - 1):

        # 计算信息增益
        infoGain = calInfoGain(baseEntropy, dataSet, curtFeatIndex)

        # 选取最优信息增益的划分
        if (infoGain > bestInfoGain):
            # 更新信息增益，找到最大的信息增益
            bestInfoGain = infoGain
            # 记录信息增益最大的特征的索引值
            bestFeatVec = curtFeatIndex
    print("最佳的划分为第%d个特征，是”%s“，信息增益为%.3f" % (bestFeatVec, featList[bestFeatVec], bestInfoGain))
    return bestFeatVec


# 数据集已经处理了所有属性，但是类标签依然不是唯一的,采用多数判决的方法决定该子节点的分类,即统计yList中出现次数最多的元素（类标签）
def majorityCnt(yList):
    """
    Parameters：
        yList：类标签列表
    Returns：
        sortedClassCount[0][0]：出现次数最多的元素（类标签）
    """
    yCount = {}
    # 统计yList中每个元素出现的次数
    for vote in yList:
        if vote not in yCount.keys():
            yCount[vote] = 0
        yCount[vote] += 1
        # 根据字典的值降序排列
        sortedYCount = sorted(yCount.items(), key=operator.itemgetter(1), reverse=True)
    return sortedYCount[0][0]


# 创建决策树
def createTree(dataSet, featList, bestFeatLists):
    """
    Parameters:
        dataSet：训练数据集
        featList：分类属性标签
        bestFeatLists：存储选择的最优特征标签
    Returns：
        myTree：决策树
    """
    # 取训练数据集最后一列，即分类标签
    yList = [example[-1] for example in dataSet]

    # 如果类别完全相同，则停止继续划分
    if yList.count(yList[0]) == len(yList):
        # 返回该类别数值
        return yList[0]

    # 采用多数判决的方法决定该子节点的分类
    if len(dataSet[0]) == 1:
        return majorityCnt(yList)

    # 选择最优划分的特征index
    bestFeatVec = optimalPartition(dataSet)
    # 最优特征index所对应的分类标签，作为树的根节点
    bestFeatLabel = featList[bestFeatVec]
    # 存储选择的最优特征标签
    bestFeatLists.append(bestFeatLabel)

    # 将最优划分特征值作为当前（子）树的根节点，生成初始决策树（用字典表示一个树结构）
    myTree = {bestFeatLabel: {}}

    # 删除已经使用的特征标签
    del (featList[bestFeatVec])
    print('featList: ', featList)

    # 得到训练集中所有最优特征那一列所对应的值
    featValues = [example[bestFeatVec] for example in dataSet]
    # 去掉重复的属性值，得到最优特征下的子类
    categories = set(featValues)

    # 遍历最优特征列所对应的值，创建决策树
    for category in categories:
        # 根据当前数据集、最优划分的特征index以及每个分类（条件）得到（条件下的子集）
        subDataSet = np.array(currentConditionSet(dataSet, bestFeatVec, category))
        # 递归地调用创建决策树的方法，将递归调用的结果作为当前树节点的一个分支
        myTree[bestFeatLabel][category] = createTree(subDataSet, featList, bestFeatLists)
    return myTree


if __name__ == '__main__':
    featList = ['年龄', '是否有工作经验', '是否本科学历', '是否满足薪资期望']
    dataSet = np.array([[0, 0, 0, 0, 0],
                        [0, 0, 0, 1, 0],
                        [0, 1, 0, 1, 1],
                        [0, 1, 1, 0, 1],
                        [0, 0, 0, 0, 0],
                        [1, 0, 0, 0, 0],
                        [1, 0, 0, 1, 0],
                        [1, 1, 1, 1, 1],
                        [1, 0, 1, 1, 1],
                        [1, 0, 1, 1, 1],
                        [2, 0, 1, 1, 1],
                        [2, 0, 1, 1, 1],
                        [2, 1, 0, 1, 1],
                        [2, 1, 0, 1, 1],
                        [2, 0, 0, 0, 0]])
    bestFeatLists = []
    myTree = createTree(dataSet, featList, bestFeatLists)
    print(myTree)
