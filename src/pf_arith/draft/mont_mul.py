import math


T=[0x155f045, 0x1e9dc40, 0x37ea842, 0x12eb2f0, 0x25b36cb,
                       0x216bd51, 0x2faefcb, 0x224621e, 0x3791fa7, 0x3d47300,
                       0x2bf0f7,  0x3cc7bae, 0x5f9f35,  0x38363d9, 0x379adcf,
                       0x2b58b39, 0x910a46,  0x466919,  0x21ecf1c, 0x2074]
N=2^256-2^224-2^96+2^64-1 # p_sm2
R_inv=115792089102516462125480396441826910452883803264411231995480180208556130172932
N_1=0x4fffffffc00000001fffffffe00000000ffffffff000000010000000000000001
R=2**260

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

Tx_values=[]
Tx_1_values=[]
tx_values=[]

Tx_values.append("T2=t2&(2**26-1)")
Tx_1_values.append("T3_1=t3+(t2>>26)")
j=0
while j<20:
    tx_values.append("t{}=T[{}]".format(j,j))

    if j>2 and j<10:
        Tx_values.append("T{}=T{}_1&(2**26-1)".format(j,j))

    if j>3 and j<10:
        Tx_1_values.append("T{}_1=t{}+(T{}_1>>26)".format(j,j,j-1))

    j+=1

i=0
while i<10:

    if i<2:
        tx_values[i+2]+="+(t{}<<12)".format(i)
        tx_values[i+3]+="-(t{}<<18)".format(i)
        tx_values[i+8]+="-(t{}<<16)".format(i)
        tx_values[i+9]+="+(t{}<<22)".format(i)
    else:
        tx_values[i+2]+="+(T{}<<12)".format(i)
        tx_values[i+3]+="-(T{}<<18)".format(i)
        tx_values[i+8]+="-(T{}<<16)".format(i)
        tx_values[i+9]+="+(T{}<<22)".format(i)

    i+=1

print(Tx_1_values)
print(Tx_values)
print(tx_values)
