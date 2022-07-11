"""
montgomery ladder 乘法
"""
from fixed_mul import Multiplier
from util import randFactor

class Bin_k(Multiplier):
    def __init__(self, k) -> None:
        super().__init__("bin",k)

    def _init_e_List(self):
        e_list=gen_BinForm(self.e)
        self.e_list=e_list

def gen_BinForm(k):
    k_binStr=getBinStr(k)

    k_bin=[int(x) for x in k_binStr]
    return k_bin

def getBinStr(k):
        return bin(k)[2:]

def cswap(b,x,y):
    """
    condition swap
    参考论文 2019FLD 中的算法9
    """
    m=0-b
    d=m&(x^y)

    x_prime=x^d #命名来源于$x^\prime$
    y_prime=y^d
    return x_prime,y_prime

def cmov(b,x,y):
    """
    condition move
    参考论文 2019FLD 中的算法10
    """
    m=0-b

    x_prime=(~m&x)^(m&y) # 命名来源于$x^\prime$
    return x_prime

def ladderMulNormal_R(k,P):
    """
    参考：本地 paper-MD/external2/重点论文/2019FLD-HIOE-arch.pdf
    p20 k The Montgomery ladder algorithm calculates
    """
    k_L=Bin_k(k)

    R0=0;R1=P

    i=0
    while i< k_L.len():
        ki=k_L.value(i)

        if ki==0:
            R1=R0+R1
            R0=2*R0
        else: #此时ki=1
            R0=R0+R1
            R1=2*R1
        i+=1

    return R0

def ladderMulNormal_Pki(k,P):
    """
    参考: 本地 paper-MD/external2/密码算法优化论文/延伸论文/2010VD.pdf
    p5 算法3
    """
    P0=P
    P1=2*P

    P_L=[P0,P1]

    k_L=Bin_k(k)

    i=1
    while i<k_L.len():
        ki=k_L.value(i)
        ki_bar=~ki

        P_L[ki_bar]=P_L[0]+P_L[1]
        P_L[ki]=2*P_L[ki]

        i+=1

    return P_L[0]

def ladderMulAdd(k,P):
    """
    参考: 本地 paper-MD/external2/密码算法优化论文/延伸论文/2010VD.pdf
    p5 算法4
    """
    P1=P
    P2=2*P

    k_L=Bin_k(k)

    i=1
    while i<k_L.len():
        ki=k_L.value(i)
        ki_bar=(~ki)%2

        P1=P1+P2
        P2=P1+(-1)**ki_bar*P

        i+=1
    # 2010VD的算法4有错误,以下是修改
    P_L=[P1,P2]
    return P_L[ki_bar]

def ladderMulCswap(k,P):
    """
    参考: 本地 paper-MD/external2/密码算法优化论文/延伸论文/2010VD.pdf
    p20 算法7
    """
    k_L=Bin_k(k)

    R0=0;R1=P

    i=0;ki_pre=0
    while i< k_L.len():
        ki=k_L.value(i)
        b=ki^ki_pre
        R0,R1=cswap(b,R0,R1)
        R0,R1=2*R0,R0+R1

        ki_pre=ki
        i+=1

    R0,R1=cswap(k_L.value(i-1),R0,R1)
    Q=R0
    return Q

def ladderMulCmov(k,P):
    """
    参考: 本地 paper-MD/external2/密码算法优化论文/延伸论文/2010VD.pdf
    p20 算法8
    """
    k_L=Bin_k(k)

    R0=0;R1=P

    i=0;ki_pre=0
    while i< k_L.len():
        ki=k_L.value(i)
        b=ki^ki_pre

        R2=R0+R1
        R0=cmov(b,R0,R1)
        R0,R1=2*R0,R2

        ki_pre=ki
        i+=1

    Q=cmov(k_L.value(i-1),R0,R1)
    return Q

def test_ladderMulNormal_R():
    k,P=randFactor(250,256,60,70)
    res=ladderMulNormal_R(k,P)
    res2=k*P
    print(res)
    print(res2)
    print(res==res2)

def test_ladderMulNormal_Pki():
    k,P=randFactor(250,256,60,70)
    res=ladderMulNormal_Pki(k,P)
    res2=k*P
    print(res)
    print(res2)
    print(res==res2)

def test_ladderMulAdd():
    # k,P=3,1
    for i in range(1000):
        k,P=randFactor(250,256,60,70)
        res=ladderMulAdd(k,P)
        res2=k*P
        # print(res)
        # print(res2)
        # print(res==res2)
        if res!=res2:
            print(False)
    print("通过")

def test_ladderMulCswap():
    k,P=randFactor(250,256,60,70)
    res=ladderMulCswap(k,P)
    res2=k*P
    print(res)
    print(res2)
    print(res==res2)

def test_ladderMulCmov():
    k,P=randFactor(250,256,60,70)
    res=ladderMulCmov(k,P)
    res2=k*P
    print(res)
    print(res2)
    print(res==res2)

if __name__=="__main__":
    # test_ladderMulNormal_R()
    # test_ladderMulNormal_Pki()
    # test_ladderMulAdd()
    # test_ladderMulCswap()
    test_ladderMulCmov()