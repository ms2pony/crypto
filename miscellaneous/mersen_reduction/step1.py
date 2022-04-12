#!/usr/bin/env python
# coding: utf-8

# ## sm2广义梅森素数乘法约减
# 相关代码如下
# ### 几种大数的表示形式
# 对于$p=0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff\\=2^{256}-2^{224}-2^{96}+2^{64}-1$
# 
# 本内容定义2个表示形式，
# 
# 1. 本文的大数形式定义如下：
# 
#     `[256, 224, 96, 64, 1]`, 等价$p=2^{256}-2^{224}-2^{96}+2^{64}-1$，从高位到低位
#     
# 2. 向量形式：
#     以$2^{26}$为一个单位划分，即$2^{26}$进制
# 
#     `[22, 16, 0, 0, 0, 0, 18, 13, 0, 1]`，从高位到低位, 等价$p=2^{256}-2^{224}-2^{96}+2^{64}-1$
#     
# ### 两种形式之间的转化
# 定义函数`bn2vec`，用于两种形式之间的转化
# 
# ### 约减函数
# 定义伪梅森素数约减函数，输入数的形式为向量形式

# In[1]:


from mersen_op import *

def bn2mersenTest():
    p_sm2=0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff
    bnSets=[2^260,2^286,2^312,2^338,2^364,2^390,2^416,2^442,2^468,2^494]

    i=10
    outputLatex=""
    for bn in bnSets:

        bnRec_str=bin(mersenReduction(bn,p_sm2))[2:]
        # outputLatex+=r"z_{{{}}} 2^{{{}}} \equiv z_{{{}}}({}) \bmod p ".format(i,len(bnRec_str)-1,i,bnRec_str)
        # print(convert(bnRec_str))
        outputLatex+=r"&z_{{{}}} 2^{{{}}} \equiv z_{{{}}}({}) \bmod p\\".format(i,len(bin(bn))-3,i,bn2mersen(bnRec_str))

        
        i+=1
    outputLatex=r"\begin{aligned}"+outputLatex[:-2]+r"\end{aligned}"
    # outputLatex=r"\begin{flalign}"+outputLatex[:-2]+r"\end{flalign}"
    # 根据论文中的表示再做修改
    outputLatexSp=outputLatex.replace("2^{240}-2^{238}",r"3\cdot 2^{238}")
    from IPython.display import Latex

    return Latex(outputLatexSp)

outputmd=bn2mersenTest();outputmd


# In[2]:


# 10个分量的向量表示10个limbs的大数, 20个分量则是20个limbs的大数
# 每一个分量的权重分别为：
# [2^234, 2^208, 2^182, 2^156, 2^130, 2^104, 2^78, 2^52, 2^26, 1]
p_sm2=vector([22, 16, 0, 0, 0, 0, 18, 12, 0, 1])

z10_bn=[260]
z10_vec=bn2vec(z10_bn)

var('z10')
print(p_sm2*z10)
v1=vector([22, 16, 0, 0, 0, 0, 18, 12, 0, 1]);v1


# In[3]:


v2=vector([1,2,3])
matrix2= v2.column()*v2.row();matrix2
print(matrix2[0])


# In[ ]:




