#!/usr/bin/python
# -*- coding: UTF-8 -*-

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

# 通过脚本`a.py`，生成4个随机的256-bit大数，然后转成4个10-limb的数组A,B,C,D
A=bigNum2Array(0x7c977d021722d19b7f258d720c3e068dc9126bee07a598c5f36d5bd19b10a924)
B=bigNum2Array(0xd1594bfffb715b36cda63c3366285f9222662ac0712ee551763baea68ade7b3)
C=bigNum2Array(0x379d9eb14e0f1e95635b7aeb3446af44c398ba038cd949bde99ec7de1d713ea1)
D=bigNum2Array(0xf1ccb5a66d36f5842b29f4b0b4f2f6e10279aaba1e745747c3188decb198c169)

# 生成c语言代码，用于test_mul_avx2.c中
cStrLine1="A_B[{}] = _mm256_set_epi64x({}, {}, {}, {});\n" # 5个{}：i和4个大数
cStrLine2="C_D[{}] = _mm256_set_epi64x({}, {}, {}, {});\n" # 5个{}：i和4个大数

cCodeAB=""
cCodeCD=""
for i in range(0,5):
    cCodeAB+=cStrLine1.format(i,A[2*i],A[2*i+1],B[2*i],B[2*i+1])
    cCodeCD+=cStrLine2.format(i,C[2*i],C[2*i+1],D[2*i],D[2*i+1])
cCode=cCodeAB+cCodeCD
# print(cCode) #打印到控制台后，将输出内容粘贴到`test_mul_avx2.c`中

# 得到test_mul_avx2.c中输出的E,F，将它们转成16进制，其中：E=A*C mod p，F=B*D mod p
# p=0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff (取自椭圆曲线P-256，参考：https://neuromancer.sk/std/nist/P-256#)
p=0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
ABigNum=0x7c977d021722d19b7f258d720c3e068dc9126bee07a598c5f36d5bd19b10a924
BBigNum=0xd1594bfffb715b36cda63c3366285f9222662ac0712ee551763baea68ade7b3
CBigNum=0x379d9eb14e0f1e95635b7aeb3446af44c398ba038cd949bde99ec7de1d713ea1
DBigNum=0xf1ccb5a66d36f5842b29f4b0b4f2f6e10279aaba1e745747c3188decb198c169
ETrue=(ABigNum*CBigNum)%p
FTrue=(BBigNum*DBigNum)%p
E=[67880615,34901173,71215497,103277320,76446430,76367253,82952132,22596550,77203173,6491518]
F=[68945793,31231784,48420513,75857380,29707574,82669268,69312715,70620149,82669130,22319601]
E=array2BigNum(E)
F=array2BigNum(F)
# 格式化输出，左对齐
print("ETrue=",ETrue)
print("FTrue=",FTrue)
print("E    =",E)
print("F    =",F)
print("p    =",p)
print("结论：\n使用`mul_avx2`函数算出的E和F与实际值ETrue和FTrue不符合，且E和F超过了p的大小")



