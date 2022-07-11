import os
import sys

def compatibleRepr(point):
    pointHex=[]
    if point.is_zero():
        return "O"
    else:
        point=point.xy()
        for e in point:
            pointHex.append(e)
        return (pointHex[0],pointHex[1])

p = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
K = GF(p)
a = K(0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc)
b = K(0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b)
E = EllipticCurve(K, (a, b))
P = E(0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296, 0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5)
Q=E(44710890534849379681007195543719586089737754824560621976448707498688874787731, 78410552107786285403689301656392479612049391334024095564584156230482213311870)
O=E(0,1,0)

def test_ecdsa():
    os.chdir(sys.path[0])
    res={}
    res['P+Q']=compatibleRepr(P+Q)
    res['P-Q']=compatibleRepr(P-Q)
    res['P-P']=compatibleRepr(P-P)
    res['P+P']=compatibleRepr(P+P)
    res['2*P']=compatibleRepr(2*P)
    res['2*O']=compatibleRepr(2*O)
    res['O+O']=compatibleRepr(O+O)
    res['O-O']=compatibleRepr(O-O)
    res['72*P']=compatibleRepr(72*P)
    res['3897*P']=compatibleRepr(3897*P)

    res_str=repr(res)

    try:
        with open("out/res2.log","w") as f:
            f.write(res_str)
    except FileNotFoundError:
        os.makedirs('out')
        with open("out/res2.log","w") as f:
            f.write(res_str)

if __name__=='__main__':
    test_ecdsa()