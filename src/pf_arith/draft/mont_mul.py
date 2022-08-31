"""
乘法+约减
"""
import random

def list2Int(a_list,radix):
    a=0
    i=0
    for x in a_list:
        a+=x*radix^i
        i+=1
    return a
def int2list(a,radix):
    a_list=[]
    while a:
        a_list.append(a%radix)
        a//=radix
        # print(a)
    return a_list

A_bn=random.randint(2**253,2**256-1)
B_bn=random.randint(2**253,2**256-1)

A=int2list(A_bn,2**26)
B=int2list(B_bn,2**26)

N=2^256-2^224-2^96+2^64-1 # p_sm2
R_inv=115792089102516462125480396441826910452883803264411231995480180208556130172932
N_1=0x4fffffffc00000001fffffffe00000000ffffffff000000010000000000000001
R=2**260

T_1x_values=['']*19  # T=A*B的临时digits
tx_values=[]    # T约减后的digits
Tx_1_values=[]  # T约减后并完成carry prop
Tx_values=[]    # T=A*B T约减后并压缩后的digits

i=0
while i<10:
    j=0
    while j<10:
        if T_1x_values[i+j]=='':
            T_1x_values[i+j]="T_1[{}]=A[{}]*B[{}]+".format(i+j,i,j)
        else:
            T_1x_values[i+j]+="A[{}]*B[{}]+".format(i,j)
        j+=1

    i+=1
i=0
while i<19:
    T_1x_values[i]=T_1x_values[i][:-1]
    i+=1
        
# print(T_1x_values)

Tx_1_values.append("T1_1=t1+(t0>>26)")
Tx_values.append("T0=t0&(2**26-1)")

j=0
while j<19:
    tx_values.append("t{}=T_1[{}]".format(j,j))

    if j>1 and j<10:
        Tx_1_values.append("T{}_1=t{}+(T{}_1>>26)".format(j,j,j-1))

    if j>0 and j<10:
        Tx_values.append("T{}=T{}_1&(2**26-1)".format(j,j))

    j+=1

i=0
while i<10:
    tx_values[i+2]+="+(T{}<<12)".format(i)
    tx_values[i+3]+="-(T{}<<18)".format(i)
    tx_values[i+8]+="-(T{}<<16)".format(i)
    tx_values[i+9]+="+(T{}<<22)".format(i)

    i+=1

# print(Tx_1_values)
# print(Tx_values)
# print(tx_values)
# print(len(T_1x_values),len(Tx_1_values),len(Tx_values),len(tx_values))

def printCode():
    i=0
    while i<19:
        if i<10:
            print(T_1x_values[i])
            print(tx_values[i])
            if i>0:
                print(Tx_1_values[i-1])
            print(Tx_values[i])

        else:
            print(T_1x_values[i])
            print(tx_values[i])
        i+=1

printCode()