#!/usr/bin/python
# -*- coding: UTF-8 -*-

# 将10*26表示法的数组转成大数
def array2BigNum(array):
    i = 0
    res = 0
    for e in array:
        res += e*2**(26*i)
        i += 1
        # print("i",i)
    return res

# 将大数转成10*26表示法的数组


def bigNum2Array(bigNum):
    array = []
    while bigNum//(2**26):
        array.append(bigNum % (2**26))
        bigNum = bigNum//(2**26)
    array.append(bigNum)
    return array

def test_mul_avx2():
    ABigNum = 0x7c977d021722d19b7f258d720c3e068dc9126bee07a598c5f36d5bd19b10a924
    BBigNum = 0xd1594bfffb715b36cda63c3366285f9222662ac0712ee551763baea68ade7b3
    CBigNum = 0x379d9eb14e0f1e95635b7aeb3446af44c398ba038cd949bde99ec7de1d713ea1
    DBigNum = 0xf1ccb5a66d36f5842b29f4b0b4f2f6e10279aaba1e745747c3188decb198c169
    # 通过脚本`a.py`，生成4个随机的256-bit大数，然后转成4个10-limb的数组A,B,C,D
    A = bigNum2Array(ABigNum)
    B = bigNum2Array(BBigNum)
    C = bigNum2Array(CBigNum)
    D = bigNum2Array(DBigNum)

    # 生成c语言代码，用于test_mul_avx2.c中
    cStrLine1 = "A_B[{}] = _mm256_set_epi64x({}, {}, {}, {});\n"  # 5个{}：i和4个大数
    cStrLine2 = "C_D[{}] = _mm256_set_epi64x({}, {}, {}, {});\n"  # 5个{}：i和4个大数

    cCodeAB = ""
    cCodeCD = ""
    for i in range(0, 5):
        # cCodeAB += cStrLine1.format(i, A[2*i], A[2*i+1], B[2*i], B[2*i+1])
        # [A[2i],A[2i+1],B[2i],B[2i+1]]
        cCodeAB += cStrLine1.format(i, B[2*i+1], B[2*i], A[2*i+1], A[2*i])

        # cCodeAB += cStrLine1.format(i, B[2*i], B[2*i+1], A[2*i], A[2*i+1]) # [A[2i+1],A[2i],B[2i+1],B[2i]]

        # cCodeCD += cStrLine2.format(i, C[2*i], C[2*i+1], D[2*i], D[2*i+1])
        cCodeCD += cStrLine2.format(i, D[2*i+1], D[2*i], C[2*i+1], C[2*i])
        # cCodeCD += cStrLine2.format(i, D[2*i], D[2*i+1], C[2*i], C[2*i+1])

    cCode = cCodeAB+cCodeCD
    print(cCode)  # 打印到控制台后，将输出内容粘贴到`test_mul_avx2.c`中

    # sm2椭圆曲线
    p = 0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff

    ETrue = (ABigNum*CBigNum) % p
    FTrue = (BBigNum*DBigNum) % p

    # 得到test_mul_avx2.c中输出的E,F，将它们转成16进制，其中：E=A*C mod p，F=B*D mod p
    # E = [0x6e850a5ae6ef4, 0x170f8581ef98de, 0x106c2715f6ecb6, 0x144603c5e98bba, 0x1994ba3cdc9bd1,
    #      0x188306fbe566e4, 0x1bdb201dd742d4, 0x1b46009bda3096, 0x434691d5d7a05, 0x2915ab6bdc1d8]
    # F = [0x28883c99ab18b, 0x71a834145dd7c, 0x796013b750edf, 0x131cce171cade8, 0x152fbe4fba4724,
    #      0x16040ad4e2d0e3, 0x16de730b19eddd, 0x15de666aaee6bf, 0xc0a100f1b8d2c, 0x2a70c8e90412f]
    # E = [0x6e850aff3d9c4, 0x170f8581ef98de, 0x106b82bf49ecb6, 0x146f1971298bba, 0x1994ba3cdc9bd1,
    #      0x188306fbe566e4, 0x1bdb201dd742d4, 0x1b46009bda3096, 0x43eae882d7a05, 0x2bdc1d8]
    # F = [0x28883d436e3bb, 0x71a834145dd7c, 0x7955778520edf, 0x13473edfdcade8, 0x152fbe4fba4724,
    #      0x16040ad4e2d0e3, 0x16de730b19eddd, 0x15de666aaee6bf, 0xc14ac414b8d2c, 0x290412f]
    # E=[0x1b8b45e,0x3a9ad07,0x3bacd71,0x2449582,0x1ee1cc3,0x64a9574,0x3f80493,0x6d0f89e,0x42efa36,0x3cadc20]
    # F=[0x1a54dbd,0x1e7fe6e,0x53baf05,0x5422e38,0x4817aa9,0x22ec077,0x49af093,0x4668382,0x49326d1,0x592c533]
    E = [0x3f3d9c4, 0x3a9ad09, 0x50dce16, 0x1446c6a, 0x1f8622e,
        0x64a9574, 0x3f80493, 0x6d0f89e, 0x2fefa2c, 0x3cd6d7b]
    F = [0x36e3bb, 0x1e7fe71, 0x218afaf, 0x5c203c6, 0x48c16db,
        0x22ec077, 0x49af093, 0x4668382, 0x2c326c7, 0x5956c40]

    E = array2BigNum(E)
    F = array2BigNum(F)
    E = E % p
    F = F % p
    # 格式化输出，左对齐
    print("ETrue=", hex(ETrue))
    print("FTrue=", hex(FTrue))
    print("E    =", hex(E))
    print("F    =", hex(F))
    print("p    =", hex(p))
    if E == ETrue and F == FTrue:
        print("正确")
    else:
        print("结论：\n使用`mul_avx2`函数算出的E和F与实际值ETrue和FTrue不符合，且E和F超过了p的大小")


def test_mul_avx2_1():
    """
    随机生成大量实例 A_B, C_D，其通过`util/mm256op.c`中的get_mm256_2bn函数生成
    并使用`mul_avx2`函数计算它们的结果 E_F
    然后对每个E_F的正确性进行验证
    并统计正确的个数
    """
    p = 0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff
    count = 0
    falseList = []

    with open("/home/tam/crypto/test/test_mul_avx2/log.txt","r") as f:
        str1="1"
        i=0
        while(str1):
            str1=f.readline()
            str2=f.readline()
            if str1:
                dicA_B=eval(str1+str2)

            str1=f.readline()
            str2=f.readline()
            if str1:
                dicC_D=eval(str1+str2)

            str1=f.readline()
            str2=f.readline()
            if str1:
                dicE_F=eval(str1+str2)

            A,B=array2BigNum(dicA_B["A"]),array2BigNum(dicA_B["B"])
            C,D=array2BigNum(dicC_D["A"]),array2BigNum(dicC_D["B"])
            ETrue,FTrue=A*C%p,B*D%p
            E,F=array2BigNum(dicE_F["A"])%p,array2BigNum(dicE_F["B"])%p

            if E == ETrue and F == FTrue:
                count+=1
            else:
                falseList.append(i)

            i+=1

    print(count)
    print(falseList)

if __name__ == '__main__':
    test_mul_avx2_1()