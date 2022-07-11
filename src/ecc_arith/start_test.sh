#!/usr/sbin/zsh

# 测试1，测试elliptic.py文件中的EllipticPoint功能是否符合预期
# 使用sagemath中的椭圆曲线算出的值作为正确值
# 通过比较EllipticPoint算出的值是否与sagemath中的椭圆曲线算出的值相等
# 来判断EllipticPoint是否符合预期

if  [ "$1" = '' ]
then
    echo "==开始测试=="
    python elliptic.py
    sage test_ecdsa.sage
    python test_elliptic.py
elif [ "$1" = "clean" ]
then
    echo "删除out文件夹"
    rm -rf out/
else
    echo "请输出合适的参数"
fi