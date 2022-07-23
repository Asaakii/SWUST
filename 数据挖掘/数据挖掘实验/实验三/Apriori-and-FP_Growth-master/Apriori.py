import time

# 购物篮分析
# 载入数据集
def load_data_set():
    data_set = [
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
    return data_set


# 直接从数据集构造1-候选集，每个候选项集只有一个元素，返回C1
def create_C1(data_set):
    # 生成C1的映射表
    C1 = set()
    for t in data_set:
        for item in t:
            item_set = frozenset([item])
            C1.add(item_set)
    return C1


# 剪枝部分
def is_apriori(Ck_item, Lksub1):
    # 求c的每个大小为(k-1)的子集,若子集中有不在L(k-1)中的元素，返回false；否则返回true
    for item in Ck_item:
        sub_Ck = Ck_item - frozenset([item])
        if sub_Ck not in Lksub1:
            return False
    return True


# 生成各个候选集Ck
def create_Ck(Lksub1, k):
    Ck = set()
    len_Lksub1 = len(Lksub1)
    list_Lksub1 = list(Lksub1)
    for i in range(len_Lksub1):
        for j in range(1, len_Lksub1):
            l1 = list(list_Lksub1[i])
            l2 = list(list_Lksub1[j])
            l1.sort()
            l2.sort()
            if l1[0:k - 2] == l2[0:k - 2]:
                Ck_item = list_Lksub1[i] | list_Lksub1[j]
                if is_apriori(Ck_item, Lksub1):
                    Ck.add(Ck_item)
    return Ck


# 通过候选集Ck生成频繁集Lk
def generate_Lk_by_Ck(data_set, Ck, min_support, support_data):
    Lk = set()
    item_count = {}
    for t in data_set:
        for item in Ck:
            if item.issubset(t):
                if item not in item_count:
                    item_count[item] = 1
                else:
                    item_count[item] += 1
    t_num = float(len(data_set))
    for item in item_count:
        if (item_count[item] / t_num) >= min_support:
            Lk.add(item)
            support_data[item] = item_count[item] / t_num
    return Lk


# 生成k-阶频繁集，最小支持度为0.2
def generate_L(data_set, k, min_support):
    support_data = {}
    C1 = create_C1(data_set)
    L1 = generate_Lk_by_Ck(data_set, C1, min_support, support_data)
    Lksub1 = L1.copy()
    L = []
    L.append(Lksub1)
    for i in range(2, k + 1):
        Ci = create_Ck(Lksub1, i)
        Li = generate_Lk_by_Ck(data_set, Ci, min_support, support_data)
        Lksub1 = Li.copy()
        L.append(Lksub1)
    return L, support_data


# 生成从频繁集关联规则分析
def generate_big_rules(L, support_data, min_conf):
    big_rule_list = []
    sub_set_list = []
    for i in range(0, len(L)):
        for freq_set in L[i]:
            for sub_set in sub_set_list:
                if sub_set.issubset(freq_set):
                    conf = support_data[freq_set] / support_data[freq_set - sub_set]
                    big_rule = (freq_set - sub_set, sub_set, conf)
                    if conf >= min_conf and big_rule not in big_rule_list:
                        big_rule_list.append(big_rule)
            sub_set_list.append(freq_set)
    return big_rule_list


# 主函数
if __name__ == "__main__":
    start = time.time()
    data_set = load_data_set()
    L, support_data = generate_L(data_set, k=3, min_support=0.2)
    big_rules_list = generate_big_rules(L, support_data, min_conf=0.7)
    for Lk in L:
        print("=" * 50)
        print(str(len(list(Lk)[0])) + "-" + "频繁项集\t\t支持度")
        print("=" * 50)
        for freq_set in Lk:
            print(freq_set, support_data[freq_set])
    print("强关联")
    for item in big_rules_list:
        print(item[0], "=>", item[1], "置信度: ", item[2])

    end = time.time()
    print('运行时间：', str(end - start))
