# 四种算法
# 1. 直接法

# 2. exponent splitting with wNAF-base interleaving method
# 参考本地 "F:\iii\ii\i\workStudation\workStation\paper-MD\external2\密码算法优化论文\延伸论文\2001Mol.pdf" 5.1节中提到的公式
from naf_mul import getNAFw_bin
from util import randFactor

class Multiplier:
    def __init__(self,type,e) -> None:
        self.e=e
        self._init_e_List()
        self.type=type

    def _init_e_List(self):
        """
        初始化self.e_list
        """
        self.e_list=[]

    def value(self,index):
        return self.e_list[index]

    def paddingZero(self,t):
        paddingZero(self.e_list,t)

    def sameBitLen(self):
        """
        令list中所有元素的bit length
        记ei最大的 bit length 为 b
        bit length达不到b的ei高位都补0
        """
        sameBitLen(self.e_list)

    def ei_largest_binLen(self):
        largest_len=ei_largest_binLen(self.list)
        return largest_len

    def len(self):
        return len(self.e_list)

class Accum_e(Multiplier):
    def __init__(self, e, w) -> None:
        self.w=w
        super().__init__("accum", e)

    def _init_e_List(self):
        e_list=gen_AccumForm(self.e,self.w)
        self.e_list=e_list

    def ei_value(self,i):
        """
        返回第i个e对应的value
        """
        return ei_value(self.e_list,i)

class Split_e(Multiplier):
    def __init__(self, e, m, w) -> None:
        self.m=m
        self.w=w
        super().__init__("split", e)
        self._eiConvertNAF()

    def _init_e_List(self):
        e_list=gen_SplitForm(self.e,self.m)
        self.e_list=e_list

    def ei_NAF_part(self,i,j):
        """
        i:第i个e
        j:第j个ei_NAF_part
        """
        return e_NAF_part(self.e_list2[i],j)

    def _eiConvertNAF(self):
        """
        初始化e_list2
        e_list中的每个ei转成NAFw并存储到e_list2,
        而不是e转成NAF
        """
        self.e_list2=[]
        for x in self.e_list:
            xNAF=getNAFw_bin(x,self.w)
            self.e_list2.append(xNAF)

    def sameBitLen(self,choice=2):
        """
        choose为1时, 对self.e_list进行操作
        choose为2时, 对self.e_list2进行操作
        """
        if choice==1:
            return super().sameBitLen()
        elif choice==2:
            sameBitLen(self.e_list2)
        else:
            ex = Exception("choose值不对！")
            raise ex

    def ei_largest_binLen(self,choice=2):
        if choice==1:
            return super().ei_largest_binLen()
        elif choice==2:
            largest_len=ei_largest_binLen(self.e_list2)
            return largest_len
        else:
            ex = Exception("choose值不对！")
            raise ex

    def len(self,choice=2):
        if choice==1:
            return super().len()
        elif choice==2:
            return len(self.e_list2)
        else:
            ex = Exception("choose值不对！")
            raise ex

def paddingZero(e,t):
    """
    补0到n bit位
    """
    count=t-len(e)
    
    if count<0:
        ex=Exception("不需要补零！")
        raise ex
    else: #包括count=0,这种情况什么也不做
        for _ in range(count):
            e.insert(0,0)


def gen_AccumForm(k,d):
    """
    参考：本地 "F:\iii\ii\i\workStudation\workStation\paper-MD\external2\重点论文\2019FLD-HIOE-arch.pdf" p18的算法5
    """
    k_bin=bin(k)[2:]
    n=len(k_bin)

    if n%d==0:
        t=n//d
    else:
        t=n//d+1

    k_list=[]
    i=0
    while i<t:
        s=k%2**d
        c=s//2**(d-1)
        ki=(s&(~2**(d-1)))-(s&2**(d-1))
        k=k//2**d+c
        k_list.append(ki)
        i+=1
    
    # 2019FLD的算法5有错误没有这一步，不加这一步就不能正确进行形式转换
    # 具体看2019FLD中p18的算法5的step6的注释
    if k!=0:
        k_list.append(k)

    return k_list

def gen_SplitForm(k,m):
    """
    return: e_list, eg. e_list=[e1,e2,...,ei]
        ei=[32,78,21,11]
    """
    k_bin=bin(k)[2:]

    high_remain_len=len(k_bin)%m

    count=len(k_bin)//m

    e_list=[int(k_bin[high_remain_len:][i*m:(i+1)*m],2) for i in range(count)]

    if high_remain_len:
        e_list.insert(0,int(k_bin[:high_remain_len],2))

    return e_list

def ei_value(e,i):
    """
    e形如[[1,-7,3],[0,1,-1]]
    """
    value=e[i]
    return value

def e_NAF_part(e,i):
    """
    获取e_part
    k的形式为NAFw, k形如[0,0,1,0,-19,-3]
    """
    return e[i]

def ei_largest_binLen(e_list):
        largest_len=0
        for ei in e_list:
            ei_binLen=len(ei)
            if ei_binLen>largest_len:
                largest_len=ei_binLen

        return largest_len

def sameBitLen(e_list):
    """
    令e_list中所有元素的bit length
    记ei最大的 bit length 为 b
    bit length达不到b的ei高位都补0
    """
    # split form 只有第一个元素可能是最短的
    largest_len=ei_largest_binLen(e_list)

    i=0
    while i<len(e_list):
        ei=e_list[i]
        ei_len=len(ei)
        while ei_len<largest_len:
            ei.insert(0,0)
            ei_len+=1
        e_list[i]=ei
        i+=1

class PreTable:
    def __init__(self,type,g) -> None:
        self.type=type
        self.g=g
        self._genTable()
        # self.w=w
    
    def _genTable(self):
        self.table=[]

    def lookup(self,index):
        pass

    def len(self):
        return len(self.table)

class AccumTable(PreTable):
    def __init__(self, g, e, w) -> None:
        self.e=e
        self.w=w
        super().__init__("accum", g)

    def _genTable(self):
        table=genAccumTable(self.g,self.e,self.w)
        self.table=table

    def lookup(self, u, v):
        """
        参数u,v命名参考: 论文2019FLD 详见全局函数lookupAccum
        """
        res_part=lookupAccum(self.table,u,v)
        return res_part

class SplitTable(PreTable):
    def __init__(self, g, e, m) -> None:
        self.e=e
        self.m=m
        super().__init__("split", g)

    def _genTable(self):
        table=genSplitTable(self.g,self.e,self.m)
        self.table=table

    def lookup(self,index):
        gi=lookupSplit(self.table,index)
        return gi

class NafTable(PreTable):
    def __init__(self, g, w) -> None:
        self.w=w
        super().__init__("NAF", g)

    def _genTable(self):
        table=genNAFTable(self.g,self.w)
        self.table=table

    def lookup(self,e_part):
        # res_part=g*e_part
        res_part=lookupNaf(self.table,e_part)
        return res_part

def genAccumTable(g,e,w):
    table=[]

    e_bin=bin(e)[2:]

    if len(e_bin)%w==0:
        gi_count=len(e_bin)//w
    else:
        gi_count=len(e_bin)//w+1

    i=0
    while i<gi_count:
        j=1
        T=[]
        gi=g*2**(i*w)
        # NAF形式
        while j<=2**(w-1):
            T.append(gi*j)
            j+=1
        table.append(T)
        i+=1

    # 修复2019FLD中p18的算法5中的step6的错误
    # 2019FLD 本地位置 "F:\iii\ii\i\workStudation\workStation\paper-MD\external2\重点论文\2019FLD-HIOE-arch.pdf"
    T=[g*2**(gi_count*w)]
    table.append(T)

    return table

def genSplitTable(g,e,m):
    table=[]

    e_bin=bin(e)[2:]
    count=len(e_bin)//m+1

    for i in range(count):
        table.append(g*2**(m*i))

    return table

def genNAFTable(g,w):
    preCompute=[]
    for i in [x for x in range(0,2**(w-1)) if x%2==1]:
        preCompute.append(i*g)
    return preCompute

def lookupAccum(T,u,v):
    """
    参考：论文 2019FLD p17 4.1节中的公式(23)
    论文位置：本地 paper-MD/external2/重点论文/2019FLD-HIOE-arch.pdf
    u: 是查找表Tu的index
    v: 本次需要查询值 v*2^(du)*P 中的v, 而不是该值在查询表中的index
    """
    # v*2^(du)*P在查询表中的inxdex等于v-1
    if v>0:
        v_index=v-1
        return T[u][v_index] # v>0 返回 Tu(v)
    elif v<0:
        v_index=-v-1
        return -T[u][v_index] # v<0 返回 -Tu(-v)
    else: # v=0时
        return None

def lookupNaf(table,e_part):
    """
    查询NAFw类型的预计算表
    根据e_part查询预计算表
    e_part: 整数, 可以为负数和整数，但不能为0
    """
    return table[abs(e_part)//2]

def lookupSplit(table,index):
    """
    查询split类型的预计算表
    根据index查询预计算表
    """
    return table[index]

def splitFixedInterleaveMul(g,e,m,w):
    # 1. 分割e，得到ei
    e_L=Split_e(e,m,w)

    # 2. 预计算g^2im (fixed, 不计入计算开销)
    gi_L=SplitTable(g,e,m)

    # 3. wNAF预计算
    # 每一个gi都有一个NAF预计算表
    tables=[]
    k=gi_L.len() # ei和gi的数量相同
    i=k-1
    while i>=0:
        tables.append(NafTable(gi_L.lookup(i),w))
        i-=1

    # 4. evaluation interleaving
    # 参考论文 本地 paper-MD/external2/密码算法优化论文/延伸论文/2001Mol.pdf 3.2节的evaluation stage
    e_L.sameBitLen()
    b=e_L.ei_largest_binLen()

    j=0
    A=0
    while j<b:
        A+=A
        i=0
        while i<k:
            ei_part=e_L.ei_NAF_part(i,j)
            if ei_part>0:
                A+=tables[i].lookup(ei_part)
            elif ei_part<0:
                A-=tables[i].lookup(abs(ei_part))
            i+=1
        j+=1
    return A

def accumMul(g,e,w):
    """
    accumulation 累加链
    类似splitFixedInterleaveMul,将e,g分割
    生成g1=g,g2=g^(2*w),...
    区别是2*w而不是2*m
    """
    A=0
    # 1.分割e
    e_L=Accum_e(e,w)

    # 2.预计算
    table=AccumTable(g,e,w)

    # 3.evaluation
    for u in range(e_L.len()):
        v=e_L.ei_value(u)
        # phi表示$\phi$
        # $\phi$命名来源 2019FLD 公式(23) 详见全局函数lookupAccum
        phi=table.lookup(u,v)

        if phi:
            A+=phi
        # phi=None时,表示v=0,此时不用进行累加

    return A

if __name__=='__main__':
    k,_=randFactor(250,256,50,60)
    k_list=gen_AccumForm(k,5)
    print(k_list)
    # test_accumMul()