#!/usr/bin/python
# -*- coding: UTF-8 -*-
"""
文件：a.py
"""
import random

bigNumStr=''
for i in range(0,256):
    bigNumStr+=str(random.randint(0,1)) 
# 通过代码生成一个256-bit的大数A：0x7c977d021722d19b7f258d720c3e068dc9126bee07a598c5f36d5bd19b10a924L
# 通过代码生成一个256-bit的大数B：0xd1594bfffb715b36cda63c3366285f9222662ac0712ee551763baea68ade7b3L
# 通过代码生成一个256-bit的大数C：0x379d9eb14e0f1e95635b7aeb3446af44c398ba038cd949bde99ec7de1d713ea1L
# 通过代码生成一个256-bit的大数D：0xf1ccb5a66d36f5842b29f4b0b4f2f6e10279aaba1e745747c3188decb198c169L


print(bigNumStr)
print(len(bigNumStr))
bigNum=hex(int(bigNumStr,2))
print(bigNum)
print(len(bigNum))