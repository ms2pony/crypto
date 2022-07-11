"""
参考[1]：file:///F:/iii/ii/i/workStudation/workStation/paper-MD/external2/ref/ecc-guide.pdf
"""
from overhead import overhead
import random as rd

def _NAFmod(k:int,w:int)->int:
    if k%2**w>=2**(w-1):
        return k%2**w-2**w
    else:
        return k%2**w

def _JSFmod(Li:int,n:int)->int:
    if Li%n>=n//2:
        return Li%n-n
    else:
        return Li%n

def getNAF_bin(k:int)->list:
    i=0
    k_NAF_bin=[]
    while k>=1:
        if k%2==1:
            ki=2-(k%4);k=k-ki
        else:
            ki=0
        k//=2;i+=1
        k_NAF_bin.append(ki)
    k_NAF_bin=k_NAF_bin[::-1]
    return k_NAF_bin

def getNAFw_bin(k:int,w:int)->list:
    """
    得到k的NAFw表示
    """
    i=0
    k_NAF_bin=[]
    while k>=1:
        if k%2==1:
            ki=_NAFmod(k,w);k=k-ki
        else:
            ki=0
        k//=2;i+=1
        k_NAF_bin.append(ki)
    k_NAF_bin=k_NAF_bin[::-1]
    return k_NAF_bin

@overhead
def binary_mul1(k,p):
    """
    从左到右扫描k
    """
    addCount=0
    doubleCount=0
    res=0
    k_bin=bin(k)[2:]
    for ki in k_bin:
        res*=2
        doubleCount+=1
        if ki=='1':
            res+=p
            addCount+=1
    return res,addCount,doubleCount

@overhead
def binary_mul2(k,p):
    """
    从右到左扫描k
    """
    addCount=0
    doubleCount=0
    res=0
    k_bin=bin(k)[2:][::-1]
    for ki in k_bin:
        if ki=='1':
            res+=p
            addCount+=1
        p*=2
        doubleCount+=1
    return res,addCount,doubleCount

@overhead
def binary_mulNAF(k,p):
    """
    从左到右扫描k_NAF
    """
    k_NAF=getNAF_bin(k)
    res=0
    addCount=0
    doubleCount=0
    for ki in k_NAF:
        res*=2
        doubleCount+=1
        if ki==1:
            res+=p
            addCount+=1
        elif ki==-1:
            res-=p
            addCount+=1
    return res,addCount,doubleCount

@overhead
def window_mulNAFw(k:int,p:int,w:int)->int:
    """
    从左到右扫描k_NAFw
    """
    addCount=0
    doubleCount=0
    res=0
    preCompute={}

    k_NAFw=getNAFw_bin(k,w)

    # 预计算阶段
    for i in [x for x in range(0,2**(w-1)) if x%2==1]:
        preCompute[str(i)]=i*p
    doubleCount+=1
    addCount+=2**(w-2)-1

    # 评估阶段
    for ki in k_NAFw:
        res*=2
        doubleCount+=1
        if ki:
            if ki>0:
                res+=preCompute[str(abs(ki))]
            else:
                res-=preCompute[str(abs(ki))]
            addCount+=1

    doubleCount-=1 # 除去上面循环第一次迭代的倍加操作，因为这次操作res=res*2=0*2，没有意义

    return res,addCount,doubleCount

def _findLargest_t(k_NAF:list,i:int,w:int)->tuple:
    t=1;u=0
    j=1 # j=0对应的k_NAF[j]已经知道是非0了
    while j<w and i+j<len(k_NAF):
        if k_NAF[i+j]:
            t=j+1
        j+=1

    u_binList=k_NAF[i:i+t][::-1]
    j=0
    while j<t:
        u+=u_binList[j]*2**j
        j+=1

    return t,u

def slideWinMul_NAF(k:int,p:int,w:int)->int:
    res=0
    addCount=0
    doubleCount=0
    preCompute={}

    k_NAF=getNAF_bin(k)

    # 预计算
    for i in [x for x in range(0,2*(2**w-(-1)**w)//3) if x%2==1]:
        preCompute[str(i)]=i*p

    # 评估阶段
    i=0
    while i<len(k_NAF):
        ki=k_NAF[i]

        if ki==0:
            t=1;u=0
        else:
            t,u=_findLargest_t(k_NAF,i,w)

        res*=2**t
        if u:
            if u>0:
                res+=preCompute[str(abs(u))]
            else:
                res-=preCompute[str(abs(u))]
        i+=t

    return res,addCount,doubleCount

def getJSF_bin(k1:int,k2:int)->tuple:
    """
    参数k1,k2不能同时为0
    返回值为k1,k2的Joint sparse form，二进制列表形式，
    因为返回的二进制表示有负数，所以不适合用str存储，因为字符串变量s的s[i]只能访问"-1"的一部分
    这两个字符串k1_JSF_bin和k2_JSF_bin，
    只有k1,k2在一起产生的JSF才会产生这两个字符串

    参考：file:///F:/iii/ii/i/workStudation/workStation/paper-MD/external2/ref/ecc-guide.pdf 中的算法3.50
    上面参考资料的算法3.50有一处指代不明，具体下面的代码中有说明
    """
    l=0;d1=0;d2=0
    L=[0,0]
    k_JSF_bin=[[],[]]

    while k1+d1>0 or k2+d2>0:
        L[0]=d1+k1;L[1]=d2+k2
        for i in range(2):
            if L[i]%2==0:
                u=0
            else:
                u=_JSFmod(L[i],4)
                # 注意下面if语句中的abs(_JSFmod(L[i],8))==3和L[1-i]%4==2，
                # 在原资料中为li=+-3(mod8)和l_{3-i}=2(mod 4)
                # 正确意思应该是两个剩余类的范围分别为[-4,3]和[0,3]
                # 可是这剩余类的定义不一样啊(一个有负，一个全正)
                # 这难免让人觉得有些指代不明
                if abs(_JSFmod(L[i],8))==3 and L[1-i]%4==2:
                    u=-u
            k_JSF_bin[i].append(u)
        
        if 2*d1==1+k_JSF_bin[0][l]:
            d1=1-d1
        k1//=2
        if 2*d2==1+k_JSF_bin[1][l]:
            d2=1-d2
        k2//=2

        l+=1

    return k_JSF_bin[0][::-1],k_JSF_bin[1][::-1]

def test_getNAF_bin():
    k=1122334455
    k_bin=[int(ki) for ki in bin(k)[2:]]
    k_NAF=getNAF_bin(k)
    # print(bin(k))
    print(k_bin)
    print(k_NAF)

def test_binary_mul():
    k=1122334455
    p=79
    res1=binary_mul1(k,p)
    res2=binary_mul2(k,p)
    print(res1)
    print(res2)
    print(k*p)
    print(res1==res2)

def test_binary_mulNAF():
    k=1122334455
    p=79
    res1=binary_mulNAF(k,p)

    print(k*p)
    print(res1)

def test_window_mulNAFw():
    k=1122334455
    p=79
    w=5
    res1=window_mulNAFw(k,p,w)

    print(k*p)
    print(res1)

def test_slideWinMul_NAF():
    w=5
    for _ in range(20):
        k=rd.randint(2**252,2**256-1)
        p=rd.randint(100,200)

        res1=slideWinMul_NAF(k,p,w)[0]

        print(k*p==res1)

def test_getJSF_bin():
    k=53;l=102
    K=getJSF_bin(k,l)
    print(K) # 预期得到的结果和参考资料[1]的例子的JSF一样

if __name__=="__main__":
    test_getJSF_bin()
    # test_slideWinMul_NAF()
    # test_getNAF_bin()
    # test_window_mulNAFw()
    # test_binary_mul()
    # test_binary_mulNAF()