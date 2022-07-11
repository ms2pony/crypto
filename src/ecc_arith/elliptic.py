# 参考：https://blog.csdn.net/weixin_45748968/article/details/121492738

from copy import copy
import math
import os
import sys
from cal_time import *

p=0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff

# @cal_time 递归函数还是不用装饰器了，因为每一次递归都会返回一个测量值
def extended_euclidean(a:int, b:int)->tuple:
    """
    给定a,b
    得到gcd(a,b)和x,y，其中gcd(a,b)=ax+by
    """
    if b==0:
        gcd=a;x=1;y=0
        return (gcd,x,y)

    gcd,x,y=extended_euclidean(b,a%b)
    t=y
    y=x-(a//b)*y    # 一定要//，这是整除；而`/`不是整除！
    x=t

    return (gcd,x,y)

# @cal_time
def mod_inverse(a:int,b:int)->int:
    gcd,x,_=extended_euclidean(a,b)
    if gcd==1:
        return x%b
    else:
        return -1

fieldPrime=0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
a=0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc
b=0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b

class EllipticPoint:
    """
    该类参考[1]：file:///F:/iii/ii/i/workStudation/workStation/paper-MD/external2/ref/ecc-guide.pdf
    p101中 k Group law for
    """
    def __init__(self,x=float('inf'),y=float('inf')) -> None:
        self.x=x
        self.y=y

    def __str__(self) -> str:
        if math.isinf(self.x) or math.isinf(self.y):
            return "O"
        else:
            return "({},{})".format(hex(self.x),hex(self.y))

    def __repr__(self) -> str:
        if math.isinf(self.x) or math.isinf(self.y):
            return "O"
        else:
            return "({},{})".format(hex(self.x),hex(self.y))

    def __eq__(self, __o: object) -> bool:
        if self.x==__o.x and self.y==__o.y:
            return True
        elif self.isIdentity() and __o.isIdentity():
            return True
        else:
            return False

    def __neg__(self):
        res=copy(self)
        if self.isIdentity():
            return res
        else:
            res.y=-res.y%p
            return res

    def __add__(self,other):
        if self==other or self==-other:
            # 参考[1]说，对于点加运算，P，Q不能相等，也不能互为相反数
            if self==-other:
                # 对于倍点运算，P，Q不能互为相反数
                # P，Q互为相反数时，相加的结果为O即identity
                return EllipticPoint()
            else:
                return self._elliptic_double(self)
        elif self.isIdentity():
            res=copy(other)
            return res
        elif other.isIdentity():
            res=copy(self)
            return res
        else:
            return self._elliptic_add(self,other)

    def __sub__(self,other):
        res=copy(other)
        res=-res
        return self.__add__(res)

    def __mul__(self,other):
        if isinstance(other, int):
            return self._elliptic_mul(other,self)
        else:
            raise TypeError("multiplier(左边的乘数factor)需要是整数类型！")

    def __rmul__(self,other):
        if isinstance(other, int):
            return self._elliptic_mul(other,self)
        else:
            raise TypeError("multiplier(左边的乘数factor)需要是整数类型！")

    def isIdentity(self)->bool:
        if math.isinf(self.x) or math.isinf(self.y):
            return True
        else:
            return False    

    def _elliptic_add(self,P,Q):
        if P.isIdentity() and Q.isIdentity():
            return EllipticPoint(0)
        elif P.isIdentity():
            return Q
        elif Q.isIdentity():
            return P
        elif P.x==Q.x and P.y==-Q.y:
            return EllipticPoint(0)
        else:
            # if P.x>Q.x:
            #     swapEllipticPoint(P,Q)

            res=EllipticPoint()

            slop=((Q.y-P.y)*mod_inverse(Q.x-P.x,fieldPrime))%fieldPrime

            res.x=(slop**2-P.x-Q.x)%fieldPrime
            res.y=(slop*(P.x-res.x)-P.y)%fieldPrime

            return res

    def _elliptic_double(self,P):
        if P.y==0:
            return EllipticPoint(0)

        res=EllipticPoint()

        slop=(3*P.x**2+a)*mod_inverse(2*P.y,fieldPrime)%fieldPrime
        res.x=(slop**2-2*P.x)%fieldPrime
        res.y=(slop*(P.x-res.x)-P.y)%fieldPrime

        return res

    def _elliptic_mul(self,k:int,P):
        """
        从左到右扫描k
        """
        res=EllipticPoint() # 此时res=O，即identity
        k_bin=bin(k)[2:]
        for ki in k_bin:
            res+=res
            if ki=='1':
                res+=P
        return res

def test_EllipticPoint():
    """
    测试类EllipticPoint的功能是否符合预期
    """
    os.chdir(sys.path[0])

    P=EllipticPoint(0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296, 0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5)
    Q=EllipticPoint(44710890534849379681007195543719586089737754824560621976448707498688874787731, 78410552107786285403689301656392479612049391334024095564584156230482213311870)
    O=EllipticPoint()
    res={}
    res['P+Q']=P+Q
    res['P-Q']=P-Q
    res['P-P']=str(P-P)
    res['P+P']=P+P
    res['2*P']=2*P
    res['2*O']=str(2*O)
    res['O+O']=str(O+O)
    res['O-O']=str(O-O)
    res['72*P']=72*P
    res['3897*P']=3897*P

    res_str=repr(res)

    try:
        with open("out/res1.log","w") as f:
            f.write(res_str)
    except FileNotFoundError:
        os.makedirs('out')
        with open("out/res1.log","w") as f:
            f.write(res_str)

if __name__ == "__main__":
    test_EllipticPoint()