## 一些常识

### AVX2 指令集

AVX2 于 2013 年发布，AVX2 是 AVX 的扩展，AVX 只支持 128-bit 大整数指令，AVX2 支持 256-bit 大整数指令。
主要指令如下：

1. VPMULUDQ
2. `_mm256_alignr_epi8`：

   ```c
   FOR j := 0 to 1
      i := j*128
      tmp[255:0] := ((a[i+127:i] h<< 128)[255:0] OR b[i+127:i]) >> (imm8*8)
      dst[i+127:i] := tmp[127:0]
   ENDFOR
   dst[MAX:256] := 0
   ```

   example:

   A=[a1,a2,a3,a4], B=[b1,b2,b3,b4]
   \_mm256_alignr_epi8(A,B,8)=[a1,b2,a3,b4]

3. `_mm256_srli_epi64`：
   右移
4. `_mm256_shuffle_epi32(__m256i a, const int imm8)`：

   shuffle, 位置调整，对应的功能代码如下

   ```c
   DEFINE SELECT4(src, control) {
      CASE(control[1:0]) OF
      0: tmp[31:0] := src[31:0]
      1: tmp[31:0] := src[63:32]
      2: tmp[31:0] := src[95:64]
      3: tmp[31:0] := src[127:96]
      ESAC
      RETURN tmp[31:0]
   }
   dst[31:0] := SELECT4(a[127:0], imm8[1:0])
   dst[63:32] := SELECT4(a[127:0], imm8[3:2])
   dst[95:64] := SELECT4(a[127:0], imm8[5:4])
   dst[127:96] := SELECT4(a[127:0], imm8[7:6])
   // 与前面4行对称
   dst[159:128] := SELECT4(a[255:128], imm8[1:0])
   dst[191:160] := SELECT4(a[255:128], imm8[3:2])
   dst[223:192] := SELECT4(a[255:128], imm8[5:4])
   dst[255:224] := SELECT4(a[255:128], imm8[7:6])
   dst[MAX:256] := 0
   ```

   上面代码大概意思是，分两次 shuffle，每次 128bit 分为 4 个元素，使用 imm8 进行分组，
   imm8 分为 4 个 4 进制数对 4 个元素进行选择

5. `_mm256_blend_epi32(__m256i a, __m256i b, const int imm8)`：

   blend, 从两个\_\_m256i 数组中选择元素填充到新的\_\_m256i 中

   ```c
   FOR j := 0 to 7
      i := j*32
      IF imm8[j]
         dst[i+31:i] := b[i+31:i]
      ELSE
         dst[i+31:i] := a[i+31:i]
   FI
   ENDFOR
   dst[MAX:256] := 0
   ```

   上面代码的大概意思是，将新的\_\_m256i 分成 8 个 32bit 数，
   根据 imm8 的 8 个 bit 来选择是从 a 中取还是从 b 中取

## 数据结构

### `mul_avx2.c`

实现 256bit 大数的模乘运算，$A\times B \bmod P$,
其中 $A, B, P$ 为 256-bit 大数

1. 大数的表示：使用 5 个 256-bit 的 AVX2 寄存器存放两个大数 $A, B$，
   即 `A_B[i]=[A[2*i],A[2*i+1],B[2*i],B[2*i+1]]`。

   其中，`A_B[i]`表示一个 256-bit 寄存器，里面装了 4 个 元素，前两个是 A 的 limbs，后两个是 B 的 limbs，这些元素正常情况下是 26bit 的数。
