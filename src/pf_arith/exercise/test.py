def list2Int(a_list,radix):
    a=0
    i=0
    for x in a_list:
        a+=x*radix**i
        i+=1
    return a
def int2list(a,radix):
    a_list=[]
    while a:
        a_list.append(a%radix)
        a//=radix
    return a_list

T=[0x155f045, 0x1e9dc40, 0x37ea842, 0x12eb2f0, 0x25b36cb,
                       0x216bd51, 0x2faefcb, 0x224621e, 0x3791fa7, 0x3d47300,
                       0x2bf0f7,  0x3cc7bae, 0x5f9f35,  0x38363d9, 0x379adcf,
                       0x2b58b39, 0x910a46,  0x466919,  0x21ecf1c, 0x2074]
T_bn=list2Int(T,2**26)
N=2**256-2**224-2**96+2**64-1 # p_sm2
R_inv=0x4fffffff700000005fffffffc00000002fffffff90000000afffffff90000000
N_1=0x4fffffffc00000001fffffffe00000000ffffffff000000010000000000000001
R=2**260

t0=T[0];t1=T[1]
t2=T[2]+(t0<<12);t3=T[3]-(t0<<18)+(t1<<12)
T2=t2&(2**26-1);T3_1=t3+(t2>>26)
T3=T3_1&(2**26-1);t4=T[4]-(t1<<18)+(T2<<12)
t5=T[5]-(T2<<18)+(T3<<12);T4_1=t4+(T3_1>>26)
T4=T4_1&(2**26-1);T5_1=t5+(T4_1>>26)
T5=T5_1&(2**26-1);t6=T[6]-(T3<<18)+(T4<<12)
t7=T[7]-(T4<<18)+(T5<<12);T6_1=t6+(T5_1>>26)
T6=T6_1&(2**26-1);T7_1=t7+(T6_1>>26)
T7=T7_1&(2**26-1);t8=T[8]-(t0<<16)-(T5<<18)+(T6<<12)
t9=T[9]+(t0<<22)-(t1<<16)-(T6<<18)+(T7<<12);T8_1=t8+(T7_1>>26)
T8=T8_1&(2**26-1);T9_1=t9+(T8_1>>26)
T9=T9_1&(2**26-1)

t10=T[10]+(t1<<22)-(T2<<16)-(T7<<18)+(T8<<12)
T10_1=t10+(T9_1>>26)
T10=T10_1&(2**26-1)

print(T10)

res=T_bn*R_inv%N
print(int2list(res,2**26))