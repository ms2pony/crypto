# 测试`src/ecc/elliptic.py`中的类EllipticPoint的功能是否正常
import os
import sys

def test_elliptic():
    os.chdir(sys.path[0])

    with open("out/res1.log","r") as f:
        content1=f.read()

    with open("out/res2.log","r") as f:
        content2=f.read()

    res1=eval(content1)
    res2=eval(content2)
    # print(res1)
    # print(res2)
    for e1,e2 in zip(res1.values(),res2.values()):
        if e1 != e2:
            print("有一些测试值并不符合预期！")
            return
    
    print("所有测试值都符合预期")

if __name__=='__main__':
    test_elliptic()