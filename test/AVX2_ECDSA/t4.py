# 调用openssl库中的ecp_nistz256_mul_mont函数
from ctypes import *
import struct

libcrypto=cdll.LoadLibrary('/home/tam/Desktop/bignum/openssl/libcrypto.so.1.1')

a = (c_ulong*4)(1, 2, 3, 4)
b = (c_ulong*4)(1, 2, 3, 4)
res=(c_ulong*4)(0, 0, 0, 0)
# class Array4Struct(Structure):  
#     _fields_ = [("name", c_ulong * 4)]

# a=Array4Struct()
# b=Array4Struct()
# print("a: ",a[0])
# print("b: ",b[0])


ecp_nistz256_mul_mont=libcrypto.ecp_nistz256_mul_mont
ecp_nistz256_mul_mont.argtypes=[POINTER(c_ulong),POINTER(c_ulong),POINTER(c_ulong)]
ecp_nistz256_mul_mont=(res,a,b)
# res=0
print("res: ",res[0])

# res=[12884901888,8589934590,18446744060824649730,18446744065119617027]

# big_res=0
# i=0
# for e in res:
# 	big_res+=e*2**(64*i)
# 	i+=1
# print(big_res)