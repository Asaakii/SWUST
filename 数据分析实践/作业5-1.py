import numpy as np
import pandas as pd

data = [200, 300, 400, 600, 1000]
Ser1 = pd.Series(data)


# 最小-最大规范化
def MinMaxScaler(data):
    scaler = (data - data.min()) / (data.max() - data.min())
    return scaler


print(MinMaxScaler(Ser1))


# 标准差标准化
def StandardScaler(data):
    data = (data - data.mean()) / data.std()
    return data


print(StandardScaler(Ser1))


# 小数定标规范化
def DecimalScaler(data):
    data = data / 10 ** np.ceil(np.log10(data.abs().max()))
    return data


print(DecimalScaler(Ser1))
