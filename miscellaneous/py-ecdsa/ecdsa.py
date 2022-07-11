# 参考：https://blog.csdn.net/weixin_45748968/article/details/121492738

import math

from sympy import true
from cal_time import *

# @cal_time 递归函数还是不用装饰器了
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

fieldPrime=29;a=4;b=20

class EllipticPoint:
    def __init__(self,*args) -> None:
        # if len(args)==1 and args[0]==0:
        #     self.prop="identity"
        if len(args)==2:
            self.prop="normal"
            self.x=args[0]
            self.y=args[1]
        elif len(args)==1:
            self.prop="identity"
        else:
            self.prop="normal"
    def isIdentity(self)->bool:
        if self.prop=="identity":
            return True
        else:
            return False
    def __str__(self) -> str:
        if self.prop=="normal":
            return "({},{})".format(self.x,self.y)
        else:
            return "∞"

def swapEllipticPoint(P:EllipticPoint,Q:EllipticPoint)->None:
    P.x,Q.x=Q.x,P.x
    P.y,Q.y=Q.y,P.y
    P.prop,Q.prop=Q.prop,P.prop

def elliptic_add(P:EllipticPoint,Q:EllipticPoint)->EllipticPoint:
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

def elliptic_double(P:EllipticPoint)->EllipticPoint:
    if P.y==0:
        return EllipticPoint(0)

    res=EllipticPoint()

    slop=(3*P.x**2+a)*mod_inverse(2*P.y,fieldPrime)%fieldPrime
    res.x=(slop**2-2*P.x)%fieldPrime
    res.y=(slop*(P.x-res.x)-P.y)%fieldPrime

    return res


if __name__ == "__main__":
    P=EllipticPoint(5,22);Q=EllipticPoint(16,27)
    print(elliptic_add(P,Q))
    print(elliptic_double(P))
    print(EllipticPoint(0))