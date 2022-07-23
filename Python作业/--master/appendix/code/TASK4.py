'''TASK4：将“好评.xlsx”、“中评.xlsx”、“差评.xlsx”三个文件合并成一个xlsx文件。
生成：“合并.xlsx”一个文件。'''
import pandas as pd

f1 = pd.ExcelFile(r'好评.xlsx')  # 读取这个excel
f2 = pd.ExcelFile(r'中评.xlsx')
f3 = pd.ExcelFile(r'差评.xlsx')

# 先在保留源文件xlsx的基础上把第一个好评xlsx放到3合并这个xlsx里面去
print(f1.sheet_names)  # 使用sheet_names来查看当前表格中包含的所有sheet名称（按顺序）
data = pd.DataFrame()  # 创建一个空集#想把第一行加进去f.parse(f.sheet_names[0]).values(0)
for i in range(len(f1.sheet_names)):  # 对于f中的每个sheet
    d = f1.parse(f1.sheet_names[i])  # 把sheet里面的数据赋给变量d
    data = pd.concat([data, d])  # 把d的数据加到data里面去
pd.DataFrame(data).to_excel("合并.xlsx", sheet_name="123", index=False, header=True)

# 想把第二个表格给合并上去
f = pd.read_excel(r'合并.xlsx')
data = pd.DataFrame(f)
print(f2.sheet_names)  # 使用sheet_names来查看当前表格中包含的所有sheet名称（按顺序）
for i in range(len(f2.sheet_names)):  # 对于f中的每个sheet
    d = f2.parse(f2.sheet_names[i])  # 把sheet里面的数据赋给变量d
    data = pd.concat([data, d])  # 把d的数据加到data里面去
pd.DataFrame(data).to_excel("合并.xlsx", sheet_name="123", index=False, header=True)

# 想把第三个表格给合并上去
ff = pd.read_excel(r'合并.xlsx')
data = pd.DataFrame(ff)
print(f3.sheet_names)  # 使用sheet_names来查看当前表格中包含的所有sheet名称（按顺序）
for i in range(len(f3.sheet_names)):  # 对于f中的每个sheet
    d = f3.parse(f3.sheet_names[i])  # 把sheet里面的数据赋给变量d
    data = pd.concat([data, d])  # 把d的数据加到data里面去
# data = pd.concat([data,f3])#把d的数据加到data里面去
pd.DataFrame(data).to_excel("合并.xlsx", sheet_name="123", index=False, header=True)
