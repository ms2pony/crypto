from fixed_mul import Multiplier, NafTable
from naf_mul import getNAFw_bin
from util import randFactor

def sgn(ki):
    if ki<0:
        return -1
    elif ki>0:
        return 1
    else: #ki=0
        ex=Exception("ki不能等于0")
        raise ex

class Naf_k(Multiplier):
    def __init__(self, k, w) -> None:
        self.w=w
        super().__init__("NAF", k)

    def _init_e_List(self):
        e_list=getNAFw_bin(self.e,self.w)
        self.e_list=e_list

def doubleInterMul_OFQ(k,l,P,Q,wp,wq):
    """
    论文参考：paper-MD/external2/重点论文/2019FLD-HIOE-arch.pdf p20 算法6
    OFQ表示one fixed, Q为已知点
    P, 未知点；Q, 已知点
    output：R=kP+lQ
    """
    # 1. 预计算P和Q
    tp=NafTable(P,wp)
    tq=NafTable(Q,wq)

    # 2. k和l转成NAF形式
    k_NAF=Naf_k(k,wp)
    l_NAF=Naf_k(l,wq)

    # 3. 得到k,l的NAF形式的最长bit length t
    #    高位补零, 补到t位
    t=max(k_NAF.len(),l_NAF.len())
    k_NAF.paddingZero(t)
    l_NAF.paddingZero(t)

    # 4. evaluation
    i=0
    R=0
    while i<t:
        R+=R

        ki=k_NAF.value(i);li=l_NAF.value(i)
        if ki:
            R+=sgn(ki)*tp.lookup(ki)
        if li:
            R+=sgn(li)*tq.lookup(li)

        i+=1

    return R

if __name__=="__main__":
    pass