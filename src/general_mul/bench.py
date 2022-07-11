"""
形如xxx_OH表示在xxx(xxx可以是类,函数)的基础上增加计算开销的功能
eg. splitFixedInterleaveMul_OH函数,该函数在splitFixedInterleaveMul函数的基础上增加了计算开销的功能
"""
from util import randFactor
from fixed_mul import (Split_e,SplitTable,NafTable)
from inter_mul import sgn, Naf_k

class NafTable_OH(NafTable):

    def _genTable(self):
        table,addCount,doubleCount=genNAFTable_OH(self.g,self.w)
        self.table=table
        self.addCount=addCount
        self.doubleCount=doubleCount

def genNAFTable_OH(g,w):
    addCount=0
    doubleCount=0
    preCompute=[]

    doubleCount+=1 # 计算2*g需要一次double, 2*g用于计算3*g=g+2*g,5g=... 等
    for i in [x for x in range(0,2**(w-1)) if x%2==1]:
        """
        最后表preCompute=[1*g,3*g,...,2**(w-1)*g]
        """
        preCompute.append(i*g)
        
        if i==1:
            pass # 1*g=g 不用计算
        else:
            addCount+=1

    return preCompute,addCount,doubleCount

def doubleInterMul_OFQ_OH(k,l,P,Q,wp,wq):
    """
    Q为已知点
    """
    addCount=0;doubleCount=0

    tp=NafTable_OH(P,wp)
    tq=NafTable(Q,wq)

    addCount=tp.addCount
    doubleCount=tp.doubleCount

    k_NAF=Naf_k(k,wp)
    l_NAF=Naf_k(l,wq)

    t=max(k_NAF.len(),l_NAF.len())
    k_NAF.paddingZero(t)
    l_NAF.paddingZero(t)

    i=0
    R=0
    while i<t:
        doubleCount+=1
        R+=R

        ki=k_NAF.value(i);li=l_NAF.value(i)
        if ki:
            addCount+=1
            R+=sgn(ki)*tp.lookup(ki)
        if li:
            addCount+=1
            R+=sgn(li)*tq.lookup(li)

        i+=1
    return R,addCount,doubleCount

def splitFixedInterleaveMul_OH(g,e,m,w):
    """
    splitFixedInterleaveMul函数的基础上增加计算开销的功能
    """
    addCount=0;doubleCount=0

    e_L=Split_e(e,m,w)

    gi_L=SplitTable(g,e,m)

    tables=[]
    k=gi_L.len()
    i=k-1
    while i>=0:
        tables.append(NafTable_OH(gi_L.lookup(i),w))
        i-=1

    # 计算预计算阶段的开销
    for ti in tables:
        addCount+=ti.addCount
        doubleCount+=ti.doubleCount

    e_L.sameBitLen()
    b=e_L.ei_largest_binLen()

    j=0
    A=0
    while j<b:
        doubleCount+=1 #计算evaluation阶段的开销
        A+=A
        i=0
        while i<k:
            ei_part=e_L.ei_NAF_part(i,j)
            if ei_part>0:
                addCount+=1 #计算evaluation阶段的开销
                A+=tables[i].lookup(ei_part)
            elif ei_part<0:
                addCount+=1 #计算evaluation阶段的开销
                A-=tables[i].lookup(abs(ei_part))
            i+=1
        j+=1
    return A,addCount,doubleCount

def accumMul_OH(g,e,w):
    """
    在知道e的 bit length值大概是多少时,
    w的选择就比较讲究，取值取得好可以减少一些不必要的预计算
    比如: e的 bit length为51，w取10就不太好，
    因为 51%10=1，也就是说最高剩余位只有1-bit，但你还要为这个
    计算2^9-1个product(NAF形式)，甚至2^10-1(普通形式)
    """
    pass

def bench_splitMul():
    e,g=randFactor(250,256,50,60)
    m=10;w=2
    _,addCount,doubleCount=splitFixedInterleaveMul_OH(g,e,m,w)
    print("addCount:",addCount)
    print("doubleCount:",doubleCount)
    print("可调变量:")
    print("m:",m)
    print("w:",w)

def bench_doubleInterMul_OFQ():
    k,P=randFactor(250,256,50,60)
    l,Q=randFactor(250,256,50,60)
    wp=5;wq=7
    _,addCount,doubleCount=doubleInterMul_OFQ_OH(k,l,P,Q,wp,wq)
    print("addCount:",addCount)
    print("doubleCount:",doubleCount)
    print("可调变量:")
    print("wp:",wp)
    print("wq:",wq)

if __name__=="__main__":
    # bench_splitMul()
    bench_doubleInterMul_OFQ()