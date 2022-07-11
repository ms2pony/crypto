import random as rd
import sys
import os

def randFactor(l1,r1,l2,r2):
    """
    生成两个随机的factor用于乘法
    范围分别为[2**l1,2**r1-1], [2**l2,2**r2-1]
    """
    f1=rd.randint(2**l1,2**r1-1)
    f2=rd.randint(2**l2,2**r2-1)

    return f1,f2

def addsearchPath(path):
    if os.path.isabs(path):
        sys.path.append(path)
    else:
        sys.path.append(os.path.join(sys.path[0],path))