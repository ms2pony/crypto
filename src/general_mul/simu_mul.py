"""
SimuMult类，simultaneous mult，用于计算g1*e1+g2*e2+...+gn*ek
simultaneous mult和simultaneous exponentiation等价
参考论文："F:\iii\ii\i\workStudation\workStation\paper-MD\external2\延伸密码算法论文\2001mol.pdf"
"""

import random as rd
from naf_mul import getNAFw_bin

class SimuMult:
    """
    计算g1*e1+g2*e2，g1对应g[0]，e1对应e[0]
    1.gi或ei的个数k<=2
    2.ei的二进制位数的极差应该小于w
    对2举例解释：g1,g2对应的e1和e2为(3 7)_{8}, (5 9 2)_{8},即w=3(2**w=8)，
    这两个值为8进制表示，因为w=3；这个时候ei的极差已经等于w，不满足要求了；
    这种情况下强行计算会出现，g1多乘了一个2**w
    """

    def __init__(self,method:str="normal") -> None:
        self.preTable=[]
        self.method=method

    def __call__(self,g:list,e:list,w:int)->int:
        """
        计算g1*e1+g2*e2
        1.g1对应g[0]，e1对应e[0]
        2.ei的二进制位数的极差应该小于w
        """

        self.g=g
        self.w=w
        self.e=e
        self.preAddCount=0
        self.preDoubleCount=0
        self.addCount=0
        self.doubleCount=0
        self._preCompute() # precomputation stage，使用该方法后,self.preTable会更新

        if self.method=="normal":
            # e2i的bit length等长
            e2=list(self._getNormal_bin())
            return self.simuMult(e2)
        elif self.method=="JSF": # ei为joint sparse form
            """
            只支持w=2的JSF，因为目前只知道转成JSF(w=2)的算法
            所以method="JSF"时，w不能>2
            """
            if w>2:
                ex = Exception("JSF方法的w不能超过2！")
                raise ex
            # 将e转成JSF形式
            e2=list(self._getJSF_bin())
            return self.simuMult(e2)
        elif self.method=="NAF":
            e2=list(self._getNAF_bin())
            return self.simuMult(e2)
        elif self.method=="NAF_fixed" or self.method=="NAF_slide":
            e2=list(self._getNAF_bin())
            return self.simuMult(e2)
        elif self.method=="normal_slide":
            # 与normal不一样，我用_getNormal_bin2将e转成二进制列表形式
            e2=list(self._getNormal_bin2())
            return self.simuMult(e2)
        elif self.method=="JSF_fixed" or self.method=="JSF_slide":
            e2=list(self._getJSF_bin())
            return self.simuMult(e2)

    def simuMult(self,e:list)->int:
        """
        计算g1*e1+g2*e2,
        g1对应g[0]，e1对应e[0]
        1. normal simultaneous multiplication
        e(list):元素类型为字符串，表示ei的二进制形式
        2. JSF simultaneous multiplication
        ei,e[i-1]为二进制列表JSF形式，eg. [-1,0,0,1]
        一般多点乘法才会有JSF形式
        """

        currentRes,e,winSize=self._evaluaPreproc(e) # evaluation stage preprocess
        res=self._evaluationCompute(currentRes,e,winSize) # evaluation stage
        return res

    def _evaluaPreproc(self,e:list)->tuple:
        """
        evaluation stage preprocess:
        进入evaluation阶段核心阶段之前的过渡工作,
        主要是处理指数e不能被w整除的问题，详见...
        """

        e1_binaryLenth=len(e[0])
        e2_binaryLenth=len(e[1])
        if self.method=="JSF":
            winSize=1
            e1_high_remain_lenth=(e1_binaryLenth-1)%winSize+1
            e2_high_remain_lenth=(e2_binaryLenth-1)%winSize+1
            e1_highPart=self._binList2Int(e[0][0:e1_high_remain_lenth])
            e2_highPart=self._binList2Int(e[1][0:e2_high_remain_lenth])
        elif self.method=="normal":
            winSize=self.w
            e1_high_remain_lenth=(e1_binaryLenth-1)%winSize+1
            e2_high_remain_lenth=(e2_binaryLenth-1)%winSize+1
            e1_highPart=self._getIntFromBase2(e[0][0:e1_high_remain_lenth]) # 形如"010"，短字符串
            e2_highPart=self._getIntFromBase2(e[1][0:e2_high_remain_lenth])
        elif self.method=="NAF":
            winSize=1
            e1_high_remain_lenth=(e1_binaryLenth-1)%winSize+1
            e2_high_remain_lenth=(e2_binaryLenth-1)%winSize+1
            e1_highPart=self._binList2Int(e[0][0:e1_high_remain_lenth])
            e2_highPart=self._binList2Int(e[1][0:e2_high_remain_lenth])
        elif self.method=="normal_slide" or self.method=="NAF_fixed" or self.method=="NAF_slide" or self.method=="JSF_slide" or self.method=="JSF_fixed":
            winSize=self.w
            e1_high_remain_lenth=(e1_binaryLenth-1)%winSize+1
            e2_high_remain_lenth=(e2_binaryLenth-1)%winSize+1
            e1_highPart=self._binList2Int(e[0][0:e1_high_remain_lenth])
            e2_highPart=self._binList2Int(e[1][0:e2_high_remain_lenth])

        # 初始化currentRes
        if e1_highPart==0 and e2_highPart==0:
            currentRes=0
        elif e1_highPart==1 and e2_highPart==0:
            currentRes=self.g[0]
        elif e1_highPart==0 and e2_highPart==1:
            currentRes=self.g[1]
        else:
            currentRes=self.preTable[self._getTableIndex(e1_highPart,e2_highPart)]
        # 修改e，除去高位的e_highPart
        e[0]=e[0][e1_high_remain_lenth:]
        e[1]=e[1][e2_high_remain_lenth:]

        return currentRes,e,winSize

    def _evaluationCompute(self,currentRes:int,e_remain:list,winSize:int)->int:
        """
        e_remain(list):除去高位剩余位后的e
        evaluation阶段的核心部分
        """

        if self.method=="JSF" or self.method=="normal" or self.method=="NAF" or self.method=="NAF_fixed" or self.method=="JSF_fixed":
            i=0
            # ei_remain等长，所以用哪个ei的bit len都无所谓
            while i<len(e_remain[0])//winSize:

                self.doubleCount+=winSize

                currentRes*=2**winSize      
                if isinstance(e_remain[0],str):
                    e1_part=self._getIntFromBase2(e_remain[0][i*winSize:(i+1)*winSize])
                    e2_part=self._getIntFromBase2(e_remain[1][i*winSize:(i+1)*winSize])
                elif isinstance(e_remain[0],list):
                    e1_part=self._binList2Int(e_remain[0][i*winSize:(i+1)*winSize])
                    e2_part=self._binList2Int(e_remain[1][i*winSize:(i+1)*winSize])

                ei=self._get_e_part(e_remain,i,winSize)

                # ei非0
                if e1_part==0 and e2_part==-1:
                    currentRes-=ei
                    self.addCount+=1
                elif e1_part>=0 and ei:
                    # 不包含e1_part==0且e2_part==-1的情况
                    currentRes+=ei
                    self.addCount+=1
                elif e1_part<0 and ei:
                    currentRes-=ei
                    self.addCount+=1
                i+=1
        elif self.method=="normal_slide" or self.method=="JSF_slide" or self.method=="NAF_slide":
            """
            参考：paper-MD/external2/密码算法优化论文/延伸论文/2001Mol.pdf 2.2节提到的多点窗口算法
            """
            i=0
            while i<len(e_remain[0]):
                if e_remain[0][i]==0 and e_remain[1][i]==0:
                    self.doubleCount+=1
                    currentRes+=currentRes
                    i+=1
                else:
                    i_new=min(i+winSize,len(e_remain[0]))
                    I=i_new-1
                    while e_remain[0][I]==0 and e_remain[1][I]==0:
                        I-=1 # I的最终结果一定不会比i小(最多和i相等)，因为e_remain[0][I]!=0 or e_remain[1][I]!=0
                    # 此时i<I<i_new
                    e1_part=self._binList2Int(e_remain[0][i:I+1])
                    e2_part=self._binList2Int(e_remain[1][i:I+1])
                    while i<=I:
                        self.doubleCount+=1
                        currentRes+=currentRes
                        i+=1

                    if e1_part==0 and e2_part==0:
                        pass
                    elif abs(e1_part)==1 and e2_part==0:
                        self.addCount+=1
                        currentRes+=self.g[0]
                    elif e1_part==0 and abs(e2_part)==1:
                        self.addCount+=1
                        currentRes+=self.g[1]
                    else:
                        index=self._getTableIndex(e1_part,e2_part) # 得到[]
                        ei=self.preTable[index]

                        if e1_part==0 and e2_part==-1:
                            self.addCount+=1
                            currentRes-=ei
                        elif e1_part>=0 and ei:
                            # 不包含e1_part==0且e2_part==-1的情况
                            self.addCount+=1
                            currentRes+=ei
                        elif e1_part<0 and ei:
                            self.addCount+=1
                            currentRes-=ei

                    while i<i_new:
                        self.doubleCount+=1
                        currentRes+=currentRes
                        i+=1

        return currentRes

    def _JSFmod(self,Li:int,n:int)->int:
        if Li%n>=n//2:
            return Li%n-n
        else:
            return Li%n
        
    def _getNormal_bin(self)->tuple:
        """
        转换后的ei的bit length相等
        """
        e1_bin=self._getBin(self.e[0])
        e2_bin=self._getBin(self.e[1])

        # paddingLen表示bit length少的ei需要填充的0的个数
        paddingLen=abs(len(e1_bin)-len(e2_bin))

        paddingStr=""

        for _ in range(paddingLen):
            paddingStr=paddingStr+"0"
            
        if len(e1_bin)>len(e2_bin):
            e2_bin=paddingStr+e2_bin
        elif len(e1_bin)<len(e2_bin):
            e1_bin=paddingStr+e1_bin

        return e1_bin,e2_bin

    def _getNormal_bin2(self)->tuple:
        """
        res(tuple):元素类型为列表
        返回二进制列表
        """
        e1_bin, e2_bin = self._getNormal_bin()

        e1_bin=[int(x) for x in e1_bin]
        e2_bin=[int(x) for x in e2_bin]

        return e1_bin,e2_bin

    def _getJSF_bin(self)->tuple:
        """
        return(tuple):元素类型为列表，元素中的元素类型为int
        参数e1,e2不能同时为0
        转换后的ki_JSF_bin的bit length相等
        返回值为e1,e2的Joint sparse form，二进制列表形式，
        因为返回的二进制表示有负数，所以不适合用str存储，因为字符串变量s的s[i]只能访问"-1"的一部分
        这两个字符串k1_JSF_bin和k2_JSF_bin，
        只有k1,k2在一起产生的JSF才会产生这两个字符串

        参考：file:///F:/iii/ii/i/workStudation/workStation/paper-MD/external2/ref/ecc-guide.pdf 中p132的算法3.50
        上面参考资料的算法3.50的step2.2同一行代码剩余类范围定义不明确，指代不明，具体下面的代码中有说明
        """
        e1=self.e[0];e2=self.e[1]
        l=0;d1=0;d2=0
        L=[0,0]
        k_JSF_bin=[[],[]]

        while e1+d1>0 or e2+d2>0:
            L[0]=d1+e1;L[1]=d2+e2
            for i in range(2):
                if L[i]%2==0:
                    u=0
                else:
                    u=self._JSFmod(L[i],4)
                    # 注意下面if语句中的abs(_JSFmod(L[i],8))==3和L[1-i]%4==2，
                    # 在原资料中为li=+-3(mod8)和l_{3-i}=2(mod 4)
                    # 正确意思应该是两个剩余类的范围分别为[-4,3]和[0,3]
                    # 可是这剩余类的定义不一样啊(一个有负，一个全正)
                    # 这难免让人觉得有些指代不明
                    if abs(self._JSFmod(L[i],8))==3 and L[1-i]%4==2:
                        u=-u
                k_JSF_bin[i].append(u)
            
            if 2*d1==1+k_JSF_bin[0][l]:
                d1=1-d1
            e1//=2
            if 2*d2==1+k_JSF_bin[1][l]:
                d2=1-d2
            e2//=2

            l+=1

        return k_JSF_bin[0][::-1],k_JSF_bin[1][::-1]

    def _getNAF_bin(self)->tuple:
        k_NAF_bin=[[],[]]

        if self.method=="NAF_fixed" or self.method=="NAF_slide":
            w=2
        else:
            w=self.w

        k=self.e

        i=0
        while i<2:
            k_NAF_bin[i]=getNAFw_bin(k[i],w)
            i+=1

        e1_bin=k_NAF_bin[0];e2_bin=k_NAF_bin[1]
        padding=[]
        paddingLen=abs(len(e1_bin)-len(e2_bin))

        for _ in range(paddingLen):
            padding.append(0)
            
        if len(e1_bin)>len(e2_bin):
            e2_bin=padding+e2_bin
        elif len(e1_bin)<len(e2_bin):
            e1_bin=padding+e1_bin

        return e1_bin,e2_bin

    def _getIntFromBase2(self,a_bin:str)->int:
        """
        通过a_bin(二进制形式的字符串)得到对应的int(10进制)
        """
        if not a_bin:
            return 0
        else:
            return int(a_bin,2)

    def _getBin(self,a:int)->str:
        return bin(a)[2:]

    def _get_e_part(self,e_bin:list,i:int,winSize:int)->int:
        """
        e_bin[i]，一个数的二进制形式，可以为str和list形式
        得到e的二进制的部分位的乘法和，即g1*e1_part+g2*e2_part
        """

        if isinstance(e_bin[0],str):
            e1_part=self._getIntFromBase2(e_bin[0][i*winSize:(i+1)*winSize])
            e2_part=self._getIntFromBase2(e_bin[1][i*winSize:(i+1)*winSize])
        elif isinstance(e_bin[0],list):
            e1_part=self._binList2Int(e_bin[0][i*winSize:(i+1)*winSize])
            e2_part=self._binList2Int(e_bin[1][i*winSize:(i+1)*winSize])            

        if e1_part==0 and e2_part==0:
            return 0
        elif abs(e1_part)==1 and e2_part==0:
            return self.g[0]
        elif e1_part==0 and abs(e2_part)==1:
            return self.g[1]
        else:
            index=self._getTableIndex(e1_part,e2_part) # 得到[]
            return self.preTable[index]

    def _getTableIndex(self,e1_part:int,e2_part:int)->int:
        """
        e1_part和e2_part的绝对值组合不会为以下的组合：
        (1,0) (0,1) (0,0)

        得到ei(i=1,2)的某个部分的值的e1_part和e2_part的乘法和e1_part*p1+e2_part*p2对应在预计算表中index
        举例：e1、e2分别为101 011 001, 111 011 010；w=3
        此时第2个w(从左往右)对应的两个值e1_part，e2_part为：011，011
        预计算表中存放了预先计算好的g1*e1_part+g2*e2_part
        该函数的作用就是根据e1_part和e2_part找到这个值(返回这个值在预计算表中的index)
        """
        # index=e1_part*rangeLen+e2_part
        if self.method=="normal" or self.method=="normal_slide":
            rangeLen=2**self.w
            e2_index=e2_part

            if e1_part==0:
                return e2_index-2
            elif e1_part==1:
                # rangeLen-3=rangeLen-2-1
                # -2是第0行少了0,1
                # -1是第1行少了0
                return rangeLen-3+e2_index
            else:
                return e1_part*rangeLen+e2_index-3
        elif self.method=="JSF" or self.method=="NAF":
            halfRangeLen=2**(self.w-1)-1
            rangeLen=2**self.w-1            

            if e1_part<0:
                e1_part=-e1_part
                e2_part=-e2_part

            e2_index=e2_part+halfRangeLen
            
            if e1_part==0 and e2_part<=-2:
                return e2_index
            elif e1_part==0 and e2_part>=2:
                # 第0行少了-1,0,1三个元素
                return e2_index-3
            elif e1_part==1 and e2_part<=-1:
                return rangeLen-3 + e2_index
            elif e1_part==1 and e2_part>=1:
                # rangeLen-4=rangeLen-3-1
                # 第1行少了0这一个元素
                return rangeLen-4 + e2_index
            else:
                return e1_part*rangeLen-4 + e2_index
        elif self.method=="NAF_slide" or self.method=="NAF_fixed" or self.method=="JSF_fixed" or self.method=="JSF_slide":
            halfRangeLen=2**(self.w)-1
            rangeLen=2**(self.w+1)-1

            if e1_part<0:
                e1_part=-e1_part
                e2_part=-e2_part

            e2_index=e2_part+halfRangeLen
            
            if e1_part==0 and e2_part<=-2:
                return e2_index
            elif e1_part==0 and e2_part>=2:
                # 第0行少了-1,0,1三个元素
                return e2_index-3
            elif e1_part==1 and e2_part<=-1:
                return rangeLen-3 + e2_index
            elif e1_part==1 and e2_part>=1:
                # rangeLen-4=rangeLen-3-1
                # 第1行少了0这一个元素
                return rangeLen-4 + e2_index
            else:
                return e1_part*rangeLen-4 + e2_index

    def _preCompute(self):
        """
        关于预计算表preTable，描述如下(分了几种情况)：
        1.窗口算法
        计算g1*E1+g2*E2+...+gn*Ek，其中(E1,E2,...,Ek)属于{0,...,2^w-1}^k，^ 为乘方符号
        preTable存放上面描述的每一个g1*E1+g2*E2+...+gn*Ek的结果，共有2^(kw)-1-k个entries
        所有可能的组合如下：
        0:        2,3,...,2^w-1
        1:      1,2,3,...,2^w-1
        2:    0,1,2,3,...,2^w-1
        ...
        2^w-1:0,1,2,3,...,2^w-1
        上面的关系描述了，k=2时的情况，第一列的元素表示E1(冒号左边)的所有可能值，
        某一行随后的元素表示E2的可能值，而index就是从第1行开始从左往右，
        然后从第2行开始从左往右

        2.JSF和NAF
        只考虑两个点的情况
        计算g1*E1+g2*E2+...+gn*Ek，其中(E1,E2,...,Ek)属于{0,...,2^(w-2)-1}*{2^(w-2)-1,...,0,...,2^(w-2)-1}，
        ^ 为乘方符号, preTable存放上面描述的每一个g1*E1+g2*E2+...+gn*Ek的结果，共有2^(w-1)*(2^w-1)-1-k个entries
        下标与元素关系如下：
        0:          -(2^(w-1)-1),...,-2,2,3,...,2^(w-1)-1       # -2和2之间少了3个
        1:          -(2^(w-1)-1),...,-1,1,2,3,...,2^(w-1)-1     # -1和1之间少了1个
        2:          -(2^(w-1)-1),...,-1,0,1,2,3,...,2^(w-1)-1   # 没少，总数为2^w-1
        ...
        2^(w-1)-1:  -(2^(w-1)-1),...,-1,0,1,2,3,...,2^(w-1)-1   # 没少，总数为2^w-1
        上面的关系描述了，k=2时的情况，第一列的元素表示E1(冒号左边)的所有可能值，
        某一行随后的元素表示E2的可能值，而index就是从第1行开始从左往右，
        然后从第2行开始从左往右
        """
        if self.method=="JSF" or self.method=="NAF":
            num1=2**(self.w-1)
            num2=2**(self.w-1)
            i=0
            while i<num1:
                j=-2**(self.w-1)+1
                while j<num2:
                    # 满足前面的3个"if,elif,elif"条件的元素不需要计算
                    # 然后又为了满足内存最小使用，就决定不存储它们，所以pass
                    # 这样就会导致预计算表的元素存储不是很规律
                    # 于是后续就要_get_e_part，_getTableIndex等方法辅助
                    # note：_get_e_part调用_getTableIndex
                    if i==0 and j==0:
                        pass
                    # j可为负数，所以加绝对值
                    elif i==0 and abs(j)==1:
                        pass
                    elif i==1 and j==0:
                        pass
                    else:
                        if i%2==0 and j%2==0:
                            self.preDoubleCount+=1
                        else:
                            self.preAddCount+=1
                        self.preTable.append(self.g[0]*i+self.g[1]*j)
                    j+=1
                i+=1
        elif self.method=="NAF_fixed" or self.method=="JSF_fixed":
            num1=2**self.w
            num2=2**self.w
            i=0
            while i<num1:
                j=-2**(self.w)+1
                while j<num2:
                    # 满足前面的3个"if,elif,elif"条件的元素不需要计算
                    # 然后又为了满足内存最小使用，就决定不存储它们，所以pass
                    # 这样就会导致预计算表的元素存储不是很规律
                    # 于是后续就要_get_e_part，_getTableIndex等方法辅助
                    # note：_get_e_part调用_getTableIndex
                    if i==0 and j==0:
                        pass
                    # j可为负数，所以加绝对值
                    elif i==0 and abs(j)==1:
                        pass
                    elif i==1 and j==0:
                        pass
                    else:
                        if i%2==0 and j%2==0:
                            self.preDoubleCount+=1
                        else:
                            self.preAddCount+=1
                        self.preTable.append(self.g[0]*i+self.g[1]*j)
                    j+=1
                i+=1
        elif self.method=="NAF_slide" or self.method=="JSF_slide":
            num1=2**self.w
            num2=2**self.w
            i=0
            while i<num1:
                j=-2**(self.w)+1
                while j<num2:
                    # 满足前面的3个"if,elif,elif"条件的元素不需要计算
                    # 然后又为了满足内存最小使用，就决定不存储它们，所以pass
                    # 这样就会导致预计算表的元素存储不是很规律
                    # 于是后续就要_get_e_part，_getTableIndex等方法辅助
                    # note：_get_e_part调用_getTableIndex
                    if i==0 and j==0:
                        pass
                    # j可为负数，所以加绝对值
                    elif i==0 and abs(j)==1:
                        pass
                    elif i==1 and j==0:
                        pass
                    else:
                        if i%2==1 or j%2==1:
                            self.preAddCount+=1
                        self.preTable.append(self.g[0]*i+self.g[1]*j)
                    j+=1
                i+=1
            if self.w>1:
                self.preDoubleCount+=2
        elif self.method=="normal":
            num1=2**self.w
            num2=2**self.w
            i=0
            while i<num1:
                j=0
                while j<num2:
                    # 满足前面的3个"if,elif,elif"条件的元素不需要计算
                    # 然后又为了满足内存最小使用，就决定不存储它们，所以pass
                    # 这样就会导致预计算表的元素存储不是很规律
                    # 于是后续就要_get_e_part，_getTableIndex等方法辅助
                    # note：_get_e_part调用_getTableIndex
                    if i==0 and j==0:
                        pass
                    elif i==0 and j==1:
                        pass
                    elif i==1 and j==0:
                        pass
                    else:
                        if i%2==0 and j%2==0:
                            self.preDoubleCount+=1
                        else:
                            self.preAddCount+=1
                        self.preTable.append(self.g[0]*i+self.g[1]*j)
                    j+=1
                i+=1
        elif self.method=="normal_slide":
            num1=2**self.w
            num2=2**self.w
            i=0
            while i<num1:
                j=0
                while j<num2:
                    # 满足前面的3个"if,elif,elif"条件的元素不需要计算
                    # 然后又为了满足内存最小使用，就决定不存储它们，所以pass
                    # 这样就会导致预计算表的元素存储不是很规律
                    # 于是后续就要_get_e_part，_getTableIndex等方法辅助
                    # note：_get_e_part调用_getTableIndex
                    if i==0 and j==0:
                        pass
                    elif i==0 and j==1:
                        pass
                    elif i==1 and j==0:
                        pass
                    else:
                        if i%2==1 or j%2==1:
                            self.preAddCount+=1
                        self.preTable.append(self.g[0]*i+self.g[1]*j)
                    j+=1
                i+=1
            if self.w>1:
                self.preDoubleCount+=2

    def _binList2Int(self,a:list)->int:
        res=a[0]
        if len(a)==0:
            ex = Exception("a的二进制位数等于0！")
            raise ex
        elif len(a)==1:
            return res
        for x in a[1:]:
            res*=2
            if x:
                res+=x

        return res

    def _preCompute2(self):
        """
        JSF专属预计算
        """
        self.preTable.append(self.g[0]-self.g[1])
        self.preTable.append(self.g[0]+self.g[1])


def testSimuMult1():
    """
    single normal
    """
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=1
    e=[rd.randint(2**252,2**256-1),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult()
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def testSimuMult2():
    """
    normal fixed window
    """
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=5
    e=[rd.randint(2**252,2**256-1),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult()
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def testSimuMult3():
    """
    JSF的winSize=w-1=1，w只能等于2
    """
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=2
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("JSF")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def testSimuMult4():
    """
    NAF的winSize=w-1，w=2
    """
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=2
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("NAF")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def testSimuMult5():
    """
    NAFw的winSize=w-1，w>2
    """
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=3
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("NAF")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def testSimuMult6():
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=2
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("normal_slide")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def testSimuMult7():
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=2
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("NAF_slide")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)
    print("NAF_slide end!\n")

    return res2==res

def testSimuMult8():
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=2
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("JSF_slide")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)
    print("JSF_slide end!\n")

    return res2==res

def testSimuMult9():
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=3
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("JSF_fixed")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def testSimuMult10():
    g=[rd.randint(2**3,2**64-1),rd.randint(2**3,2**64-1)]
    w=3
    e=[rd.randint(2**251,2**252),rd.randint(2**252,2**256-1)]

    simuMult=SimuMult("NAF_fixed")
    res=simuMult(g,e,w)

    res2=g[0]*e[0]+g[1]*e[1]
    # print(res2==res)
    # print(res)
    # print(res2)

    print("e's bit length:",max(len(bin(e[0]))-2,len(bin(e[1]))-2))
    print("preAddCount:",simuMult.preAddCount)
    print("preDoubleCount:",simuMult.preDoubleCount)
    print("addCount:",simuMult.addCount)
    print("doubleCount:",simuMult.doubleCount)

    return res2==res

def test_loop():
    for _ in range(100):
        if testSimuMult6()==False:
            print("有错误")
    print("成功")

def test_all():
    if testSimuMult1()==False:
        print("错误")
        return
    if testSimuMult2()==False:
        print("错误")
        return
    if testSimuMult3()==False:
        print("错误")
        return
    if testSimuMult4()==False:
        print("错误")
        return
    if testSimuMult5()==False:
        print("错误")
        return
    if testSimuMult6()==False:
        print("错误")
        return
    if testSimuMult7()==False:
        print("错误")
        return
    if testSimuMult8()==False:
        print("错误")
        return
    if testSimuMult9()==False:
        print("错误")
        return
    if testSimuMult10()==False:
        print("错误")
        return
    print("正确")

if __name__=='__main__':    
    # test_all()
    # testSimuMult3()
    testSimuMult6()
