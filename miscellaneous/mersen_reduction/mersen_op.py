# 使用了sage
from sage.all_cmdline import *


def bn2vec(bn: list):
    """
    return: 向量形式
    """
    # 算出bn有几位(2^26进制)
    len = bn[0]//26+1
    vec = [0 for i in range(len)]
    if(not mod(bn[0], 26)):
        vec[-1] = 1
    for bn_e in bn:
        vec_e = mod(bn_e, 26)
        vecIndex = bn_e//26
        if(vec_e):
            vec[vecIndex] = vec_e
    vec.reverse()
    return vec

# 测试函数 bn2vec`


def bn2vecTest():
    p1 = [256, 224, 96, 64, 1]
    p2 = [260]
    print(bn2vec(p1), bn2vec(p2))


def mersenReduction(bn, module):
    while len(bin(bn)) > 260+2:
        leftShifCount = len(bin(bn))-len(bin(module))-1
        # print(leftShifCount)
        correction = module << leftShifCount
        # print(bin(correction))
        bn -= correction

    return bn


def mersenReductionTest():
    """测试函数mersenReduction
    """
    bn = 2**260
    p_sm2 = 0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff
    # bin(mersenReduction(bn,p_sm2))
    print(bin(mersenReduction(bn, p_sm2)))


def bn2mersen(a_str):
    """将一个大数转化成伪梅森素数形式

    Args:
        a_str (str): 二进制形式，字符串，开头无'0b'

    Returns:
        _type_: _description_
    """
    a_strOutput = ""
    subpower = 0
    addpower = 0

    subpowerPre = 0
    # addpowerPre=0

    while a_str:
        a_len = len(a_str)
        a_0index = a_str.find('0')

        # print(a_0index)
        if a_0index > 1 or a_0index == -1:
            addpower = a_len
            subpower = a_len-a_0index if a_0index > 1 else 0
            if subpowerPre-addpower == 1:
                a_strOutput = a_strOutput.replace(
                    "-2^{{{}}}".format(subpowerPre), "-2^{{{}}}-2^{{{}}}".format(addpower, subpower))
                subpowerPre = subpower
            elif addpower-subpower == 1:
                # a_strOutput+="+2^{{{}}}-2^{{{}}}".format(a_len,a_len-a_0index if a_0index>1 else 0)
                a_strOutput += "+2^{{{}}}".format(subpower)
                # addpowerPre=addpower
                subpowerPre = subpower
            else:
                a_strOutput += "+2^{{{}}}-2^{{{}}}".format(addpower, subpower)
                subpowerPre = subpower

        elif a_0index == 1:

            # a_strOutput+="+2^{{{}}}".format(a_len-1)
            addpower = a_len-1
            if subpowerPre-addpower == 1:
                a_strOutput = a_strOutput.replace(
                    "-2^{{{}}}".format(subpowerPre), "-2^{{{}}}".format(addpower))
                subpowerPre = addpower
            else:
                a_strOutput += "+2^{{{}}}".format(addpower)
                # addpowerPre=addpower

        a_str = None if a_0index == -1 else a_str[a_0index+1:]

    # return a_strOutput[1:].replace('2^{0}','1')
    return a_strOutput[1:].replace('2^0', '1')


def bn2mersenTest():
    # 测试函数convert
    # p_sm2=0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff
    # p_sm2Str=bin(p_sm2)[2:]
    bn = 2**260
    p_sm2 = 0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff
    # bin(mersenReduction(bn,p_sm2))
    a_str = bin(mersenReduction(bn, p_sm2))[2:]
    print(bn2mersen(a_str))


if __name__ == "__main__":
    bn2mersenTest()
