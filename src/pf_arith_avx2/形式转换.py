"""
文件：a.py
"""

import ctypes
import struct


#将10*26表示法的数组转成大数
def array2BigNum(array):
	i=0
	res=0
	for e in array:
		res+=e*2**(26*i)
		i+=1
		# print("i",i)
	return res

#将大数转成10*26表示法的数组
def bigNum2Array(bigNum):
	array=[]
	while bigNum//(2**26):
		array.append(bigNum%(2**26))
		bigNum=bigNum//(2**26)
	array.append(bigNum)
	return array

A=[542542,3454,5015684,40823,55160,416450,50231,40515,502391,405195]
C=[542542,34554,542542,38454,542542,348754,542542,34854,542542,34854]
BigNumA=array2BigNum(A)
BigNumC=array2BigNum(C)

print("A: ",BigNumA)
print("C: ",BigNumC)
print("A*C: ",BigNumA*BigNumC)


t2=ctypes.cdll.LoadLibrary('./t2.so')

test1=t2.test1
test1.restype=ctypes.POINTER(ctypes.c_ulonglong*40)
# test1.restype=ctypes.c_ulonglong*4


p=test1()

# print(dir(p))
# print(type(p))
str="L"
unpackStr=""
for i in range(40):
	unpackStr+=str
# print(unpackStr)
# print(struct.unpack(unpackStr,p.contents))
resArray=struct.unpack(unpackStr,p.contents)
print(resArray)

# 从resArray得到A*C的结果，长度为20
# print("lenth",len(resArray))
i=0
resAC=[]
while i<10:
	resAC.append(resArray[i*4])
	resAC.append(resArray[i*4+1])
	i+=1
print("resAC[0]: ",resAC[0])
# 将resAC转成大数
i=0
res=0
for e in resAC:
	res+=e*2**(26*i)
	i+=1
	# print("i",i)
print("A*C: ",res)
