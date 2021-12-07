from ctypes import *

t1=cdll.LoadLibrary("./t1.so")

test1=t1.test1

test1.argtypes=[POINTER(c_int)]

a=(c_int*5)(2,2,2,2,2)

test1(a)

print(a[0])

a1=c_ulonglong(2)
print(sizeof(a1))