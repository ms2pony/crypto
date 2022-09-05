# T_1x=[]
# tx=[]
# Tx=[]
# Tx_1=[]


# with open("/home/tam/github/crypto/src/pf_arith/draft/生命周期.txt","r") as f:
#     str=f.read()
#     L1s=str.split("\n\n")

#     # T_1x
#     str=L1s[0]
#     L2s=str.split("\n")

#     i=0
#     while i<19:
#         str=L2s[0]
#         L3s_0=str.split("\t")
#         str=L2s[1]
#         L3s_1=str.split("\t")

#         T_1x.append([int(L3s_0[i]),int(L3s_1[i])])
#         i+=1

#     # tx
#     str=L1s[1]
#     L2s=str.split("\n")

#     i=0
#     while i<19:
#         str=L2s[0]
#         L3s_0=str.split("\t")
#         str=L2s[1]
#         L3s_1=str.split("\t")

#         tx.append([int(L3s_0[i]),int(L3s_1[i])])
#         i+=1
    
#     tx[0].append(6)

#     # Tx
#     str=L1s[2]
#     L2s=str.split("\n")

#     i=0
#     while i<10:
#         L4=[]
#         for str in L2s:
#             L3s_j=str.split("\t")
#             L4.append(int(L3s_j[i]))
#             # if i==0:
#             #     print(Tx)
#         Tx.append(L4)

#         i+=1

#     # Tx_1(1~9)
#     str=L1s[3]
#     L2s=str.split("\n")

#     i=0
#     while i<9:
#         L4=[]
#         for str in L2s:
#             L3s_j=str.split("\t")
#             L4.append(int(L3s_j[i]))
#             # if i==0:
#             #     print(Tx)
#         Tx_1.append(L4)

#         i+=1

#     # Tx_1(11~19)
#     str=L1s[4]
#     L2s=str.split("\n")
#     L2s=L2s[:-1]

#     i=0
#     while i<9:
#         L4=[]
#         for str in L2s:
#             L3s_j=str.split("\t")
#             L4.append(int(L3s_j[i]))
#             # if i==0:
#             #     print(Tx)
#         Tx_1.append(L4)

#         i+=1


# print("T_1x=",T_1x,"\n")
# print("tx=",tx,"\n")
# print("Tx=",Tx,"\n")
# print("Tx_1=",Tx_1,"\n")

T_1x= [[1, 2], [4, 5], [8, 9], [12, 13], [16, 17], [20, 21], [24, 25], [28, 29], [32, 33], [36, 37], [40, 41], [42, 43], [44, 45], [46, 47], [48, 49], [50, 51], [52, 53], [54, 55], [56, 57]] 

tx= [[2, 3, 6], [5, 6], [9, 10], [13, 14], [17, 18], [21, 22], [25, 26], [29, 30], [33, 34], [37, 38], [41, 58], [43, 60], [45, 62], [47, 64], [49, 66], [51, 68], [53, 70], [55, 72], [57, 74]] 

Tx= [[3, 9, 13, 33, 37], [7, 13, 17, 37, 41], [11, 17, 21, 41, 43], [15, 21, 25, 43, 45], [19, 25, 29, 45, 47], [23, 29, 33, 47, 49], [27, 33, 37, 49, 51], [31, 37, 41, 51, 53], [35, 41, 43, 53, 55], [39, 43, 45, 55, 57]] 

Tx_1= [[6, 7, 10], [10, 11, 14], [14, 15, 18], [18, 19, 22], [22, 23, 26], [26, 27, 30], [30, 31, 34], [34, 35, 38], [38, 39, 58], [58, 59, 60], [60, 61, 62], [62, 63, 64], [64, 65, 66], [66, 67, 68], [68, 69, 70], [70, 71, 72], [72, 73, 74], [74, 75, 76]]

counts=[]
for x in range(1,77):
    count=0
    for e in T_1x:
        if x>=e[0] and x<=e[-1]:
            count+=1
    for e in tx:
        if x>=e[0] and x<=e[-1]:
            count+=1
    for e in Tx:
        if x>=e[0] and x<=e[-1]:
            count+=1
    for e in Tx_1:
        if x>=e[0] and x<=e[-1]:
            count+=1
    counts.append(count)
print(counts)

print(len(T_1x))
print(len(tx))
print(len(Tx_1))
print(len(Tx))

        