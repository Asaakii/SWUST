# coding=utf-8
#================================================================
#
#   File name   : bayesnet.py
#   Author      : Faye
#   Created date: 2020/9/17 10:04 
#   Description : 贝叶斯网络
#                   https://blog.csdn.net/leida_wt/article/details/88743323
#                   需要安装 graphviz  https://blog.csdn.net/c_daofeng/article/details/81077594
#
#================================================================

import pandas as pd
from pgmpy.models import BayesianModel
from pgmpy.estimators import BayesianEstimator
from pgmpy.factors.discrete import TabularCPD

'''
PassengerId => 乘客ID
Pclass => 客舱等级(1/2/3等舱位)
Name => 乘客姓名
Sex => 性别 清洗成male=1 female=0
Age => 年龄 插补后分0,1,2 代表 幼年（0-15） 成年（15-55） 老年（55-）
SibSp => 兄弟姐妹数/配偶数
Parch => 父母数/子女数
Ticket => 船票编号
Fare => 船票价格 经聚类变0 1 2 代表少 多 很多
Cabin => 客舱号 清洗成有无此项，并发现有的生存率高
Embarked => 登船港口 清洗na,填S
'''
# combine train and test set.
train = pd.read_csv('./train.csv')
test = pd.read_csv('./test.csv')
full = pd.concat([train, test], ignore_index=True)
full['Embarked'].fillna('S', inplace=True)
full.Fare.fillna(full[full.Pclass == 3]['Fare'].median(), inplace=True)
full.loc[full.Cabin.notnull(), 'Cabin'] = 1
full.loc[full.Cabin.isnull(), 'Cabin'] = 0
full.loc[full['Sex'] == 'male', 'Sex'] = 1
full.loc[full['Sex'] == 'female', 'Sex'] = 0

full['Title'] = full['Name'].apply(lambda x: x.split(',')[1].split('.')[0].strip())
nn = {'Capt': 'Rareman', 'Col': 'Rareman', 'Don': 'Rareman', 'Dona': 'Rarewoman',
      'Dr': 'Rareman', 'Jonkheer': 'Rareman', 'Lady': 'Rarewoman', 'Major': 'Rareman',
      'Master': 'Master', 'Miss': 'Miss', 'Mlle': 'Rarewoman', 'Mme': 'Rarewoman',
      'Mr': 'Mr', 'Mrs': 'Mrs', 'Ms': 'Rarewoman', 'Rev': 'Mr', 'Sir': 'Rareman',
      'the Countess': 'Rarewoman'}
full.Title = full.Title.map(nn)
# assign the female 'Dr' to 'Rarewoman'
full.loc[full.PassengerId == 797, 'Title'] = 'Rarewoman'
full.Age.fillna(999, inplace=True)


def girl(aa):
    if (aa.Age != 999) & (aa.Title == 'Miss') & (aa.Age <= 14):
        return 'Girl'
    elif (aa.Age == 999) & (aa.Title == 'Miss') & (aa.Parch != 0):
        return 'Girl'
    else:
        return aa.Title


full['Title'] = full.apply(girl, axis=1)

Tit = ['Mr', 'Miss', 'Mrs', 'Master', 'Girl', 'Rareman', 'Rarewoman']
for i in Tit:
    full.loc[(full.Age == 999) & (full.Title == i), 'Age'] = full.loc[full.Title == i, 'Age'].median()

full.loc[full['Age'] <= 15, 'Age'] = 0
full.loc[(full['Age'] > 15) & (full['Age'] < 55), 'Age'] = 1
full.loc[full['Age'] >= 55, 'Age'] = 2
full['Pclass'] = full['Pclass'] - 1
from sklearn.cluster import KMeans

Fare = full['Fare'].values
Fare = Fare.reshape(-1, 1)
km = KMeans(n_clusters=3).fit(Fare)  # 将数据集分为2类
Fare = km.fit_predict(Fare)
full['Fare'] = Fare
full['Fare'] = full['Fare'].astype(int)
full['Age'] = full['Age'].astype(int)
full['Cabin'] = full['Cabin'].astype(int)
full['Pclass'] = full['Pclass'].astype(int)
full['Sex'] = full['Sex'].astype(int)
# full['Survived']=full['Survived'].astype(int)


dataset = full.drop(columns=['Embarked', 'Name', 'Parch', 'PassengerId', 'SibSp', 'Ticket', 'Title'])
dataset.dropna(inplace=True)
dataset['Survived'] = dataset['Survived'].astype(int)
# dataset=pd.concat([dataset, pd.DataFrame(columns=['Pri'])])
train = dataset[:800]
test = dataset[800:]
'''
最后保留如下项目,并切出800的训练集：
Pclass => 客舱等级(0/1/2等舱位)
Sex => 性别 male=1 female=0
Age => 年龄 插补后分0,1,2 代表 幼年（0-15） 成年（15-55） 老年（55-）
Fare => 船票价格 经聚类变0 1 2 代表少 多 很多
Cabin => 客舱号 清洗成有无此项，并发现有的生存率高
'''


model = BayesianModel([('Age', 'Survived'), ('Sex', 'Survived'),('Fare','Pclass'),('Pclass','Survived'),('Cabin','Survived')])

def showBN(model,save=False):
    '''传入BayesianModel对象，调用graphviz绘制结构图，jupyter中可直接显示'''
    from graphviz import Digraph
    node_attr = dict(
     style='filled',
     shape='box',
     align='left',
     fontsize='12',
     ranksep='0.1',
     height='0.2'
    )
    dot = Digraph(node_attr=node_attr, graph_attr=dict(size="12,12"))
    seen = set()
    edges=model.edges()
    for a,b in edges:
        dot.edge(a,b)
    if save:
        dot.view(cleanup=True)
    return dot
showBN(model, save=True)


#构建cpd表
my_cpd= TabularCPD(variable='Pclass', variable_card=3,
                      values=[[0.65, 0.3], [0.30, 0.6],[0.05,0.1]],
                      evidence=['Fare'], evidence_card=[2])
# 填cpd表
model.add_cpds(my_cpd)

# 执行检查（可选，用于检查cpd是否填错）
# cancer_model.check_model()


# data = pd.DataFrame(data={'A': [0, 0, 1], 'B': [0, 1, 0], 'C': [1, 1, 0]})
# model = BayesianModel([('A', 'C'), ('B', 'C')])
# estimator = BayesianEstimator(model, data)
# cpd_C = estimator.estimate_cpd('C', prior_type="dirichlet", pseudo_counts=[2, 4])
# model.add_cpds(cpd_C)


model.fit(train, estimator=BayesianEstimator, prior_type="BDeu") # default equivalent_sample_size=5

# pseudo_counts = {'D': [300, 700], 'I': [500, 500], 'G': [800, 200], 'L': [500, 500], 'S': [400, 600]}
# model.fit(data, estimator=BayesianEstimator, prior_type='dirichlet', pseudo_counts=pseudo_counts)



#输出节点信息
print(model.nodes())
#输出依赖关系
print(model.edges())
#查看某节点概率分布
print(model.get_cpds('Pclass').values)



from pgmpy.inference import VariableElimination
model_infer = VariableElimination(model)
q = model_infer.query(variables=['Survived'], evidence={'Fare': 0})
print(q)
'''
+------------+-----------------+
| Survived   |   phi(Survived) |
+============+=================+
| Survived_0 |          0.6341 |
+------------+-----------------+
| Survived_1 |          0.3659 |
+------------+-----------------+
'''
q = model_infer.map_query(variables=['Fare','Age','Sex','Pclass','Cabin'], evidence={'Survived': 1})
print(q)#{'Sex': 0, 'Fare': 0, 'Age': 1, 'Pclass': 2, 'Cabin': 0}



predict_data=test.drop(columns=['Survived'],axis=1)
y_pred = model.predict(predict_data)
y_survived = y_pred['Survived'].values
test_survived = test['Survived'].values
print('y_pred:', y_survived)
print("test:", test_survived)
print((y_survived == test_survived).sum()/len(test))
#测试集精度0.8131868131868132