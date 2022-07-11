from util import randFactor
from fixed_mul import splitFixedInterleaveMul,accumMul
from inter_mul import doubleInterMul_OFQ

def test_splitMul():
    e,g=randFactor(250,256,50,60)
    res=splitFixedInterleaveMul(g,e,10,5)
    res2=g*e
    print(res)
    print(res2)
    print(res2==res)

def test_accumMul():
    e,g=randFactor(250,256,50,60)
    # e,g=42478659187420620719342634746493691070817993804748017773431741007980399125478,201947628819756738
    res=accumMul(g,e,4)
    res2=g*e
    print(res)
    print(res2)
    print(res2==res)

def test_doubleInterMul_OF():
    k,P=randFactor(250,256,50,60)
    l,Q=randFactor(250,256,50,60)
    wp=5;wq=7
    res=doubleInterMul_OFQ(k,l,P,Q,wp,wq)
    res2=k*P+l*Q
    print(res)
    print(res2)
    print(res2==res)

if __name__=="__main__":
    # test_splitMul()
    test_accumMul()
    # test_doubleInterMul_OF()