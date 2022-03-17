# from PIL import Image
# imgPath = r"/mnt/f/iii/ii/i/workStudation/Studation/package/pillow/img/shiyuan.png"
# im = Image.open(imgPath)
# im.show()
import gdb

p_sm2 = 0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff


def array2BigNum(array):
    """
    将10*26表示法的数组转成大数
    """
    i = 0
    res = 0
    for e in array:
        res += e*2**(26*i)
        # print(res)
        i += 1
        # print("i",i)
    return res


class Pbig(gdb.Command):
    """
    仅仅处理 m256 A_B[5] 这种变量
    这个数组能存放2个256-bit的大数
    10个limb，每个limb正常情况下为26-bit
    """

    def __init__(self) -> None:
        super().__init__('pbig', gdb.COMMAND_USER)

    def invoke(self, para_str, from_tty):
        # gdb内部函数，根据空格将参数字符串分组
        paras = gdb.string_to_argv(para_str)
        if len(paras) != 2:
            print('need 2 para, arrary length')
            return
        Z = gdb.parse_and_eval(paras[0])
        Z_len = int(paras[1])
        # Z = para_str  # Z为字符串
        i = 0
        Z1 = []
        Z2 = []
        while(i < Z_len):
            Z1.append(int(Z[i][0].format_string())) # Z[i][2i]
            Z1.append(int(Z[i][1].format_string())) # Z[i][2i+1]
            
            Z2.append(int(Z[i][2].format_string()))
            Z2.append(int(Z[i][3].format_string())) # 同上
            
            i += 1
        Z1_p = array2BigNum(Z1)
        Z2_p = array2BigNum(Z2)
        # print(Z1)
        # print(Z2)
        print("{}其1：".format(paras[0]), hex(Z1_p))
        print("{}其2：".format(paras[0]), hex(Z2_p))
        return

Pbig()
