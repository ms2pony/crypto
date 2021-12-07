from array import array


def bigNum2Array(bigNum):
	array=[]
	while bigNum//(2**26):
		array.append(bigNum%(2**26))
		bigNum=bigNum//(2**26)
	array.append(bigNum)
	return array

def array2BigNum(array):
	i=0
	res=0
	for e in array:
		res+=e*2**(26*i)
		i+=1
		# print("i",i)
	return res

A=51651651231321654651321
# print("A：",bin(A)[2:][0:29])

array=bigNum2Array(A)
print(array)

bigNum=array2BigNum(array)
print(bigNum)

# print("A：",bin(array[-1])[2:])
