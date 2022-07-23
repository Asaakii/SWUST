# encoding: utf-8
# Apriori 算法实现 10142510168 刘恩铭

import numpy as np
import itertools
import time


def loadDataSet():
    # 加载数据集
    dataSet = [
        ['牛奶', '鸡蛋', '面包', '薯片'],
        ['鸡蛋', '爆米花', '薯片', '啤酒'],
        ['牛奶', '啤酒', '面包'],
        ['牛奶', '鸡蛋', '面包', '爆米花', '啤酒', '薯片'],
        ['鸡蛋', '面包', '薯片'],
        ['鸡蛋', '面包', '啤酒', ],
        ['牛奶', '面包', '薯片'],
        ['牛奶', '鸡蛋', '面包', '黄油', '薯片'],
        ['牛奶', '鸡蛋', '黄油', '薯片']
    ]
    return dataSet


def generate_c1(dataSet):
    # 生成候选项集的列表，每个候选项集只有一个元素，返回C1和映射表
    # 生成C1，为候选项集
    C1_map = dict()
    # 生成C1的映射表
    C1_dict = dict()
    C1 = set()
    for i in dataSet:
        for j in i:
            if C1_map.get(j, -1) == -1:
                C1.add(j)
                C1_map[j] = 1
            else:
                C1_map[j] = C1_map.get(j) + 1
    for s in C1:
        C1_dict[s] = C1_map[s]
    return C1_dict, C1


def generate_L1(support):
    # 生成L1返回
    # dictionary为一个映射表，c1-s为L1
    dictionary, c1 = generate_c1(loadDataSet())
    # print(c1)
    s = set()
    for key in dictionary.keys():
        if (dictionary[key] < support):
            # 小于支持度计数的，放入一个集合s
            s.add(key)
    for a in s:
        dictionary.pop(a)
        # 从映射表中去除小于支持度的元素
    return dictionary, c1 - s


def apriori_gen(Lk_1, k=2):
    # 生成Ck的方法，求自然连接，每个候选项集的大小为k
    Ck = set()

    for i in Lk_1:
        for j in Lk_1:
            if (i != j):
                s = set()

                if k == 2:
                    # 元素为单个数字的情况，此时没法直接union，先转化成集合再连接
                    si = {i}
                    sj = {j}
                else:
                    flag = True
                    si = set(i)
                    sj = set(j)
                    # 自然连接，如果两个集合交集为空，无法自然连接
                    if (len(si.intersection(sj)) == 0):
                        continue
                    # 将两个集合分别转化成有序列表，分别比较各自下标的元素，若前k-1个中有不同，则跳过，不进行自然连接
                    si_list = sorted(list(si))
                    sj_list = sorted(list(sj))
                    for m in range(0, k - 2):
                        if (si_list[m] != sj_list[m]):
                            flag = False
                            break
                    if (not flag):
                        continue
                s = si.union(sj)
                # 检查集合的非频繁子集测试，没有则加入Ck
                if (not has_infrequent_subset(s, Lk_1, k)):
                    # 转化为不可变集合
                    s = frozenset(s)
                    Ck.add(s)
    return Ck


def has_infrequent_subset(c, Lk_1, k):
    # 剪枝部分
    # 求c的每个大小为(k-1)的子集,若子集中有不在L(k-1)中的元素，返回true；否则返回false

    s = subSet(c, k)
    # 求c的大小为k-1的子集
    for i in s:
        if (not len((i and (Lk_1)))):
            return True

    return False


def subSet(s, k):
    # 返回一个集合的大小为k-1的子集的集合
    # 个数为CN(k-1)，组合数这里调用了itertools中的组合方法计算list的子集再转成set
    if (k == 2):
        return set(s)
    subset = set()
    s = list(s)

    s1 = itertools.combinations(s, k - 1)
    for i in s1:
        subset.add(frozenset(i))

    return subset


def generate_CK_map(CK, dataSet):
    # 扫描数据集，进行支持度计数
    CK_map = dict()
    for j in CK:
        j = set(j)
        count = 0
        for i in dataSet:
            a = set(i)
            if (j.issubset(a)):
                count = count + 1
        CK_map[frozenset(j)] = count

    return CK_map


def generate_LK(CK, CK_map, support):
    s = set()
    for key in CK_map.keys():
        if (CK_map[key] < support):
            s.add(key)
    for a in s:
        CK_map.pop(a)
    return CK_map, CK - s


def connection_rule(L, confidence, k):
    "产生关联规则"
    rule = dict()
    # 最长的频繁项集合
    longest = set()
    print("关联规则为：\n")
    # print("Lssss", L)
    for m in range(2,k+1):
        for i in L:
            # 找出所有频繁项集
            if (isinstance(i, (np.int32, float))):
                continue
            if (len(i) != m):
                continue
            longest.add(i)
        # print("longest====", longest)

        for j in longest:
            # print("j=", j)
            support_count = L[j]
            sub = set()
            for m in range(2, k + 1):
                # 求出所有非空子集
                # print("subset:", subSet(j, m))
                sub = sub | subSet(j, m)
            # print("sub=====", sub)
            # print("sub length:",len(sub))
            for n in sub:
                # print("n===", n)
                support_count_s = L[n]
                if (support_count / support_count_s >= confidence):
                    if (isinstance(n, (np.int32, float))):
                        rule[n] = frozenset(set(j).difference({n}))
                        # print("setj-setn", set(j).difference({n}))
                    else:
                        rule[n] = frozenset(set(j).difference(set(n)))
                        if(rule[n]==set()):
                            continue
                        # print("setj-setn", set(j).difference(set(n)))
                    print(n, "======>", rule[n], "  置信度为：%.2f%%" % (100 * support_count / support_count_s))


def startApriori(support, confidence):
    # 开始运行Apriori算法
    L_map = dict()
    dataSet = loadDataSet()
    L1_map, L1 = generate_L1(support)
    LK_1 = L1
    for a in L1_map:
        print("大小为", 1, "的频繁项集：", a, "   支持度计数为：", L1_map[a])
        L_map[a] = L1_map[a]
    k = 2
    while (len(LK_1) != 0):
        CK = apriori_gen(LK_1, k)
        CK_map = generate_CK_map(CK, dataSet)
        CK_map, LK_1 = generate_LK(CK, CK_map, support)
        print("Lk ( k =", k, ")")
        for a in CK_map:
            print("大小为", k, "的频繁项集：", sorted(list(a)), "   支持度计数为：", CK_map[a])
            L_map[a] = CK_map[a]
        print('\n')
        k = k + 1
    # 关联规则
    connection_rule(L_map, confidence, k - 2)


if __name__ == '__main__':
    time_start = time.time()
    support = input("请输入支持度计数：")
    confidence = input("请输入置信度：")
    startApriori(int(support), float(confidence))
    # startApriori(2000, 0.5)
    time_end = time.time()
    print('程序运行结束，共耗时', time_end - time_start, "秒")
