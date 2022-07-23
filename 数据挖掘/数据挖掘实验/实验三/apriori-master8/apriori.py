# coding=utf-8                        # 全文utf-8编码
# import sys

def apriori(D, minSup):
    '''频繁项集用keys表示，
    key表示项集中的某一项，
    cutKeys表示经过剪枝步的某k项集。
    C表示某k项集的每一项在事务数据库D中的支持计数
    '''

    C1 = {}
    for T in D:
        for I in T:
            if I in C1:
                C1[I] += 1
            else:
                C1[I] = 1

    print("\n---------候选1项集---------")
    print("F1:", C1)
    _keys1 = C1.keys()

    keys1 = []
    for i in _keys1:
        keys1.append([i])

    n = len(D)
    cutKeys1 = []
    for k in keys1[:]:
        if C1[k[0]] * 1.0 / n >= minSup:
            cutKeys1.append(k)

    cutKeys1.sort()

    keys = cutKeys1
    all_keys = []
    while keys != []:
        C = getC(D, keys)
        print_houxuanji(keys, C)
        cutKeys = getCutKeys(keys, C, minSup, len(D))
        print_pinfanji(cutKeys)
        for key in cutKeys:
            all_keys.append(key)
        keys = aproiri_gen(cutKeys)

    return all_keys


def getC(D, keys):
    '''对keys中的每一个key进行计数'''
    C = []
    for key in keys:
        c = 0
        for T in D:
            have = True
            for k in key:
                if k not in T:
                    have = False
            if have:
                c += 1
        C.append(c)
    return C


def getCutKeys(keys, C, minSup, length):
    '''剪枝步'''
    # print("剪枝\n",keys)
    # for i, key in enumerate(keys):
    #     print(i, C[i], key)
    #     if float(C[i]) / length < minSup:
    #         keys.remove(key)
    # return keys

    CutKeys = []
    for i in range(len(keys)):
        if float(C[i] / length >= minSup):
            CutKeys.append(keys[i])
    return CutKeys


def keyInT(key, T):
    '''判断项key是否在数据库中某一元组T中'''
    for k in key:
        if k not in T:
            return False
    return True


def aproiri_gen(keys1):
    '''连接步'''
    keys2 = []
    for k1 in keys1:
        for k2 in keys1:
            if k1 != k2:
                key = []
                for k in k1:
                    if k not in key:
                        key.append(k)
                for k in k2:
                    if k not in key:
                        key.append(k)
                key.sort()
                if key not in keys2:
                    keys2.append(key)

    return keys2


def print_houxuanji(keys, C):
    print("\n------连接->候选集---------")
    for i in range(len(keys)):
        print(keys[i], C[i])


def print_pinfanji(cutKeys):
    print("-----剪枝->频繁集----------")
    print(cutKeys)


if __name__ == "__main__":
    # item_set = [['A','C','D'],['B','C','E'],['A','B','C','E'],['B','E']]

    item_set = [['面包', '啤酒'],
                ['面包', '啤酒', '牛奶', '尿布'],
                ['面包', '牛奶', '可乐'],
                ['牛奶', '尿布', '可乐'],
                ['啤酒', '牛奶', '尿布', '可乐']]

    # item_set = [['面包','牛奶'],
    #             ['面包','尿布','啤酒','鸡蛋'],
    #             ['牛奶','尿布','啤酒','可乐'],
    #             ['面包','牛奶','尿布','啤酒'],
    #             ['面包','牛奶','尿布','可乐']]
    print("\n---------候选集------------")
    for item in item_set:
        print(item)

    minsup = 0.6
    F = apriori(item_set, minsup)

    one_list = []
    two_list = []
    three_list = []
    other_list = []
    # print ('\nfrequent itemset:\n', F)
    for item in F:
        if len(item) == 1:
            one_list.append(item)
        elif len(item) == 2:
            two_list.append(item)
        elif len(item) == 3:
            three_list.append(item)
        else:
            other_list.append(item)

    print("\n---------计算结果----------")
    print("最小支持度:", minsup)
    print("1项频繁集:", one_list)
    print("2项频繁集:", two_list)
    print("3项频繁集:", three_list)
    print(other_list)
