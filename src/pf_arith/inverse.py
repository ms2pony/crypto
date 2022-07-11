# 参考论文：Constant Time Modular Inversion 2014


def almMonInv(a,b):
	u=a;v=b;r=0;s=1;k=0
	while v != 1:
		if u%2==0:
			u//=2;s*=2
		elif v%2==0:
			v//=2;r*=2
		elif u>v:
			u=(u-v)//2;r=r+s;s*=2
			# if k==0:
			# 	print(u)
		else:
			v=(v-u)//2;s=r+s;r*=2
		k+=1

	return s,k


if __name__ == "__main__":
	print(almMonInv(0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff,33))
	# print(almMonInv(149,33))
