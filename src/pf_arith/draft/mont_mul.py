"""
乘法+约减
"""
from copy import copy
import re

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

A_bn=0xca1057100d08b95142ca8a6df06b95da79e786bb95e154e6311fb97e75402ac6
B_bn=0x2e3c3470e1d6ea4d43b6ed9c82c2a43af7039dd7ef26dd286d9712ce603c4cb6

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

    if j>1 and j<19:
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

T_1x= [[1, 2], [4, 5], [8, 9], [12, 13], [16, 17], [20, 21], [24, 25], [28, 29], [32, 33], [36, 37], [40, 41], [42, 43], [44, 45], [46, 47], [48, 49], [50, 51], [52, 53], [54, 55], [56, 57]]  # T_1[x]

tx= [[2, 3, 6], [5, 6], [9, 10], [13, 14], [17, 18], [21, 22], [25, 26], [29, 30], [33, 34], [37, 38], [41, 58], [43, 60], [45, 62], [47, 64], [49, 66], [51, 68], [53, 70], [55, 72], [57, 74]]     

Tx= [[3, 9, 13, 33, 37], [7, 13, 17, 37, 41], [11, 17, 21, 41, 43], [15, 21, 25, 43, 45], [19, 25, 29, 45, 47], [23, 29, 33, 47, 49], [27, 33, 37, 49, 51], [31, 37, 41, 51, 53], [35, 41, 43, 53, 55], [39, 43, 45, 55, 57]] 

Tx_1= [[6, 7, 10], [10, 11, 14], [14, 15, 18], [18, 19, 22], [22, 23, 26], [26, 27, 30], [30, 31, 34], [34, 35, 38], [38, 39, 58], [58, 59, 60], [60, 61, 62], [62, 63, 64], [64, 65, 66], [66, 67, 68], [68, 69, 70], [70, 71, 72], [72, 73, 74], [74, 75, 76]]

T_1x_name=[]
i=0
for e in T_1x:
    e_1=[]
    e_1.append("T_1[{}]".format(i))
    e_1+=e
    # print(e_1)
    T_1x_name.append(e_1)

    i+=1

tx_name=[]
i=0
for e in tx:
    e_1=[]
    e_1.append("t{}".format(i))
    e_1+=e
    # print(e_1)
    tx_name.append(e_1)

    i+=1

Tx_name=[]
i=0
for e in Tx:
    e_1=[]
    e_1.append("T{}".format(i))
    e_1+=e
    # print(e_1)
    Tx_name.append(e_1)

    i+=1

Tx_1_name=[]
i=1
for e in Tx_1:
    e_1=[]
    e_1.append("T{}_1".format(i))
    e_1+=e
    # print(e_1)
    Tx_1_name.append(e_1)

    i+=1

sit=[0]*15
counts=[]
def getSit():
    i=0
    while i<15:
        if sit[i]==0:
            return i
        i+=1

count=[None]*15
for x in range(1,77):
    # 删除
    i=0
    while i<15:
        try:
            if x<count[i][1] or x>count[i][-1]:
                count[i]=None
                sit[i]=0
        except TypeError:
            pass

        i+=1

    # 添加
    for e in T_1x_name:
        if x>=e[1] and x<=e[-1]:
            index=getSit()
            if e not in count:
                count[index]=e
                sit[index]=1
    for e in tx_name:
        if x>=e[1] and x<=e[-1]:
            index=getSit()
            if e not in count:
                count[index]=e
                sit[index]=1
    for e in Tx_name:
        if x>=e[1] and x<=e[-1]:
            index=getSit()
            if e not in count:
                count[index]=e
                sit[index]=1
    for e in Tx_1_name:
        if x>=e[1] and x<=e[-1]:
            index=getSit()
            if e not in count:
                count[index]=e
                sit[index]=1
    count_copy=copy(count)
    count_copy1=[]

    for e in count_copy:
        try:
            count_copy1.append(e[0])
        except:
            count_copy1.append(None)

    counts.append(count_copy1)

for e in counts:
    print(e)
# print(len(counts))

# print(Tx_1_values)
# print(Tx_values)
# print(tx_values)
# print(T_1x_values)
# print(len(T_1x_values),len(Tx_1_values),len(Tx_values),len(tx_values))

isCompute={}
for e in T_1x_name:
    isCompute[e[0]]=0

for e in tx_name:
    isCompute[e[0]]=0

for e in Tx_name:
    isCompute[e[0]]=0

for e in Tx_1_name:
    isCompute[e[0]]=0

# print(isCompute)

value_dic={}
for e in Tx_1_values:
    key=e.split("=")[0]
    value_dic[key]=e

for e in Tx_values:
    key=e.split("=")[0]
    value_dic[key]=e

for e in tx_values:
    key=e.split("=")[0]
    value_dic[key]=e

for e in T_1x_values:   
    key=e.split("=")[0]
    value_dic[key]=e

# print(value_dic)

express=[]
for count in counts:
    expr=[]
    for x in count:
        if x:
            if isCompute[x]==0:
                expr.append(value_dic[x])
                isCompute[x]=1

    express.append(expr)

# for e in express:
#     print(e)
# print(len(express))

express1=[]
i=1
for e in express:
    if e:
        # expr=e[0].split("=")[1]
        expr=e[0]

        idens=re.findall(r"T_1\[\d{1,2}\]",expr)
        for iden in idens:
            expr=expr.replace(iden,"R{}".format(counts[i-1].index(iden)))

        idens=re.findall(r"t\d{1,2}",expr)
        for iden in idens:
            expr=expr.replace(iden,"R{}".format(counts[i-1].index(iden)))

        idens=re.findall(r"T\d{1,2}_1",expr)
        for iden in idens:
            expr=expr.replace(iden,"R{}".format(counts[i-1].index(iden)))

        idens=re.findall(r"(T\d{1,2})[^_]{2}",expr)
        for iden in idens:
            expr=expr.replace(iden,"R{}".format(counts[i-1].index(iden)))

        express1.append(expr)

    i+=1

# for e in express1:
#     print(e)
# print(len(express1))
