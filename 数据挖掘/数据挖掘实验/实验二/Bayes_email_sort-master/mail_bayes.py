import numpy as np
import random
import re


# 使用贝叶斯算法实现垃圾邮件过滤
# 将一个大字符串解析为字符串列表
def textParse(bigString):
    listOfTokens = re.split(r'\W+', bigString)  # 将特殊符号作为切分标志进行字符串切分，即非字母、非数字
    return [tok.lower() for tok in listOfTokens if len(tok) > 2]    # 除了单个字母，例如大写的I，其它单词变成小写


# 将切分的实验样本词条整理成不重复的词条列表，也就是词汇表
def createVocabList(dataSet):
    vocabSet = set([])  # 创建空集合
    for document in dataSet:
        vocabSet = vocabSet | set(document)  # 返回不重复的单词集合
    return list(vocabSet)


# 根据vocabList词汇表，将inputSet向量化，向量的每个元素为1或0
def setOfWords2Vec(vocabList, inputSet):
    returnVec = [0] * len(vocabList)
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] = 1
        else:
            print("the word: %s is not in my Vocabulary!" % word)
    return returnVec


# 贝叶斯分类器训练函数
# trainMatrix为输入的词条集合,trainCategory为词条类别
def trainNB0(trainMatrix, trainCategory):
    numTrainDocs = len(trainMatrix)  # 获取词条长度,即分母变量
    numWords = len(trainMatrix[0])  # 第一段词条中单词个数,即分子变量
    pAbusive = sum(trainCategory) / float(numTrainDocs)
    p0Num = np.ones(numWords)
    p1Num = np.ones(numWords)   # 拉普拉斯平滑
    p0Denom = 2.0
    p1Denom = 2.0
    for i in range(numTrainDocs):
        if trainCategory[i] == 1:   # 统计属于垃圾类的条件概率所需的数据，即P(w0|1),P(w1|1),P(w2|1)···
            p1Num += trainMatrix[i]
            p1Denom += sum(trainMatrix[i])
        else:   # 统计属于非垃圾类的条件概率所需的数据，即P(w0|0),P(w1|0),P(w2|0)···
            p0Num += trainMatrix[i]
            p0Denom += sum(trainMatrix[i])
    p1Vect = np.log(p1Num / p1Denom)
    p0Vect = np.log(p0Num / p0Denom)    # 取对数，防止下溢出
    return p0Vect, p1Vect, pAbusive     # 返回属于正常邮件类的条件概率数组，属于垃圾邮件类的条件概率数组，邮件属于垃圾邮件类的概率


# 贝叶斯分类器分类函数
# 1是垃圾邮件 0是非垃圾邮件
def classifyNB(vec2Classify, p0Vec, p1Vec, pClass1):
    p1 = sum(vec2Classify * p1Vec) + np.log(pClass1)
    p0 = sum(vec2Classify * p0Vec) + np.log(1.0 - pClass1)
    print('p0:', p0)
    print('p1:', p1)
    if p1 > p0:
        return 1
    else:
        return 0


# 测试贝叶斯分类器
def spamTest():
    docList = []
    classList = []
    fullText = []
    for i in range(1, 26):  # 遍历25个txt文件
        wordList = textParse(open('email/spam/%d.txt' % i).read())  # spam文件夹中的邮件全设为1
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append(1)     # 标记垃圾邮件，1表示垃圾文件
        wordList = textParse(open('email/ham/%d.txt' % i).read())  # ham文件夹中的邮件全设为0
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append(0)     # 标记正常邮件，0表示正常文件
    vocabList = createVocabList(docList)  # 将重复出现的单词删掉
    trainingSet = list(range(50))
    testSet = []    # 创建存储训练集的索引值的列表和测试集的索引值的列表
    # 随机选取20封邮件为测试集
    for i in range(20):
        randIndex = int(random.uniform(0, len(trainingSet)))
        testSet.append(trainingSet[randIndex])
        del (trainingSet[randIndex])  # 将测试集从训练集中删除
    trainMat = []
    trainClasses = []
    # 剩下的30封作为训练集
    for docIndex in trainingSet:
        trainMat.append(setOfWords2Vec(vocabList, docList[docIndex]))  # 将文本转换成向量
        trainClasses.append(classList[docIndex])    # 将类别添加到训练集类别标签系向量中
    p0V, p1V, pSpam = trainNB0(np.array(trainMat), np.array(trainClasses))  # 贝叶斯算法来计算概率
    rightCount = 0      # 正确分类计数
    # 测试集分类精度计算
    for docIndex in testSet:
        wordVector = setOfWords2Vec(vocabList, docList[docIndex])
        print("索引 %d 被分类为: %d, 其真正的分类是 %d" % (
            docIndex, classifyNB(np.array(wordVector), p0V, p1V, pSpam), classList[docIndex]))
        if classifyNB(np.array(wordVector), p0V, p1V, pSpam) == classList[docIndex]:    # 如果分类正确
            rightCount += 1     # 正确计数加1
            print("分类正确的测试集：", docList[docIndex])
    print('正确率: %.2f%%' % (float(rightCount) / len(testSet) * 100))


if __name__ == '__main__':
    spamTest()
