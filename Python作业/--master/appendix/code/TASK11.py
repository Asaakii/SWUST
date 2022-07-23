'''TASK11：把outtime这一列的日期分成年月日和时分秒两列，然后跟scores还有jointime一起放到一个csv里去。
生成：“jointime和outtime和scores.csv“一个文件。'''
import pandas as pd

f = pd.read_excel(r'合并.xlsx')
f = pd.DataFrame(f)
two = f.ix[:, ['jointime', 'outtime', 'scores']]
print(two)
# 拆了outtime中的年月日和具体时间
print(two.dtypes)  # 用来查看two里面每一列的元素格式
two['outtime'] = two['outtime'].astype(str)  # 这样就把two中的datetime64[ns]格式的outtime这一列转换成了str格式
print(two.dtypes)  # 再次查看是不是已经变成了str格式
m = pd.DataFrame((x.split(' ') for x in two['outtime']), index=two.index, columns=['one', 'two'])
# 将two里面的'outtime'按照two里面的索引two.index，以‘ ’为界限来进行切割，然后切出来的两列分别命名为one和two
print(m)
two['one'] = m['one']
two['two'] = m['two']
print(two)
two.to_csv('jointime和outtime和scores.csv', encoding='utf-8_sig')  # 因为担心把源文件覆盖掉，所以这里名字变了一下
