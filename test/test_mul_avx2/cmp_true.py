E_true = 0x35b5ef0dfa2db43e27bf8049492a55d1f8622e601b1ad0cde16ea6b427f3d9d3

E = 0x35b5ef0dfa2db43e27bf8049492a6ec81b648b434c1ad0cde16ea6b427f3d9d3


def findDiff(E_true, E):
    str1 = bin(E_true)[::-1]
    str2 = bin(E)[::-1]
    # print(str1)
    # print(str2)

    if len(str1) != len(str2):
        print("长度不相等")
        return

    for i in range(len(str1)):
        if str1[i] != str2[i]:
            print(i//52, '\t', i % 52)


findDiff(E_true, E)
