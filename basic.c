#include <basic.h>

bignum *bn_new(int digits){
   bignum *ret;
   ret = (bignum *)malloc(sizeof(*ret));
   //成员a也需要分配内存
   ret->a = (unsigned long *)malloc(sizeof(unsigned long) * digits);
   ret->max = digits;
   return ret;
}

int BN_add_word(bignum *a, unsigned long w){
   unsigned long l;
   int i;

   w &= BN_MASK2;

   for (i = 0; w != 0 && i < a->last; i++)
   {
      a->a[i] = l = (a->a[i] + w) & BN_MASK2;
      w = (w > l) ? 1 : 0;
   }
   if (w && i == a->last)
   {
      //不判断last++是否大于max
      a->last++;
      a->a[i] = w;
   }

   return (1);
}

/*
输入：大整数bignum，unsigned long
输出：bignum*

得到a*w的结果(bignum *)
*/
int BN_mul_word(bignum *a, unsigned long w)
{
   unsigned long c1 = 0;
   int num = a->last;
   unsigned long *i = a->a;

   while (num)
   {
      mul(i[0], i[0], w, c1);
      i++;
      num--;
   }

   if (c1)
   {
      //这里并不判断last++是否会大于max
      a->a[a->last++] = c1;
   }
}


int dec2bn(bignum **bn, const char *a)
{
   bignum *ret = NULL;
   unsigned long l = 0;
   //我这里默认大数没有负数
   // int neg = 0;
   int i, j;
   int num;

   //输入的字符串不合理
   if ((a == NULL) || (*a == '\0'))
      return (0);

   //输入是负数该怎么处理
   // if (*a == '-') {
   //    neg = 1;
   //    a++;
   // }

   //isdigit函数检查参数是否为十进制字符串
   for (i = 0; isdigit((unsigned char)a[i]); i++)
      continue;

   // num = i + neg;
   num = i;
   if (bn == NULL)
      return (num);

   /*
   * a is the start of the digits, and it is 'i' long. We chop it into
   * BN_DEC_NUM digits at a time
   */

   ret = *bn;
   // BN_zero(ret);

   /* i is the number of digits, a bit of an over expand */
   ret = bn_new(i / 10 + 5);

   j = BN_DEC_NUM - (i % BN_DEC_NUM);
   if (j == BN_DEC_NUM)
      j = 0;
   l = 0;
   while (--i >= 0)
   {
      l *= 10;
      l += *a - '0';
      a++;
      if (++j == BN_DEC_NUM)
      {
         BN_mul_word(ret, BN_DEC_CONV);
         BN_add_word(ret, l);
         l = 0;
         j = 0;
      }
   }

   *bn = ret;

   /* Don't set the negative flag if it's zero. */
   //   if (ret->last != 0)
   //      ret->neg = neg;
   return (num);
}

unsigned long bn_div_words(unsigned long h, unsigned long l, unsigned long d)
{
   unsigned long ret, waste; //ret是商，waste是余数

   asm("divq      %4"
       : "=a"(ret), "=d"(waste)
       : "a"(l), "d"(h), "r"(d)
       : "cc");

   //返回商
   return ret;
}

unsigned long BN_div_word(bignum *a, unsigned long w){
   unsigned long ret = 0;
   int i, j;

   /* normalize input (so bn_div_words doesn't complain) */
   // j = 64 - BN_num_bits_word(w);
   // w <<= j;
   // if (!BN_lshift(a, a, j))
   //    return (unsigned long)-1;
   if (a->last == 0)
      return 0;

   for (i = a->last - 1; i >= 0; i--)
   {
      unsigned long l, d;

      l = a->a[i];
      d = bn_div_words(ret, l, w);
      ret = (l - ((d * w) & BN_MASK2)) & BN_MASK2;
      a->a[i] = d;
   }

   //除了之后bignum a的位数会变短，last可能会减小
   if ((a->last > 0) && (a->a[a->last - 1] == 0))
      a->last--;

   //余数
   return (ret);
}

int BN_num_bits_word(unsigned long l){
   unsigned long x, mask;
   int bits = (l != 0);

   //该代码能够防止泄露最高word的信息

   x = l >> 32;
   mask = (0 - x) & BN_MASK2;
   mask = (0 - (mask >> (64 - 1)));
   bits += 32 & mask;
   l ^= (x ^ l) & mask;

   x = l >> 16;
   mask = (0 - x) & BN_MASK2;
   mask = (0 - (mask >> (64 - 1)));
   bits += 16 & mask;
   l ^= (x ^ l) & mask;

   x = l >> 8;
   mask = (0 - x) & BN_MASK2;
   mask = (0 - (mask >> (64 - 1)));
   bits += 8 & mask;
   l ^= (x ^ l) & mask;

   x = l >> 4;
   mask = (0 - x) & BN_MASK2;
   mask = (0 - (mask >> (64 - 1)));
   bits += 4 & mask;
   l ^= (x ^ l) & mask;

   x = l >> 2;
   mask = (0 - x) & BN_MASK2;
   mask = (0 - (mask >> (64 - 1)));
   bits += 2 & mask;
   l ^= (x ^ l) & mask;

   x = l >> 1;
   mask = (0 - x) & BN_MASK2;
   mask = (0 - (mask >> (64 - 1)));
   bits += 1 & mask;

   return bits;
}

int BN_num_bits(bignum *a){
   int i = a->last - 1;
   return ((i * 64) + BN_num_bits_word(a->a[i]));
}

/*
输入：bignum *a
输出：返回值bignum

得到除了地址相同，其他信息与bignum *a的bitnum类型实例
*/
bignum *BN_dup(const bignum *a)
{
   //返回a的副本的指针
   bignum *b = bn_new(a->max);

   b->last = a->last;
   b->max = a->max;

   for (int i = 0; i < a->last; i++)
   {
      b->a[i] = a->a[i];
   }
   return b;
}

int BN_is_zero(const bignum *a){
   return a->last == 0;
}

char *bn2dec(bignum *a){
   int i = 0, num, ok = 0;
   char *buf = NULL;
   char *p;
   bignum *t = NULL;
   unsigned long *bn_data = NULL, *lp;
   int bn_data_num;

   /*-
   * get an upper bound for the length of the decimal integer
   * num <= (BN_num_bits(a) + 1) * log(2)
   *     <= 3 * BN_num_bits(a) * 0.101 + log(2) + 1     (rounding error)
   *     <= 3 * BN_num_bits(a) / 10 + 3 * BN_num_bits / 1000 + 1 + 1
   */

   //计算十进制的位数，2进制位数换算成10进制位数，num为10进制位数
   i = BN_num_bits(a) * 3;
   num = (i / 10 + i / 1000 + 1) + 1;

   //这个大数需要需要多少个unsigned long类型的元素存储
   bn_data_num = num / BN_DEC_NUM + 1;
   bn_data = malloc(bn_data_num * sizeof(unsigned long));

   //buf存储后面转成的10进制字符串
   buf = malloc(num + 3);

   t = BN_dup(a);

   p = buf;
   lp = bn_data;

   while (!BN_is_zero(t))
   {

      //lp接收的值是从低位开始，BN_div_word返回的是余数
      *lp = BN_div_word(t, BN_DEC_CONV);

      lp++;
   }
   lp--;
   /*
   * We now have a series of blocks, BN_DEC_NUM chars in length, where
   * the last one needs truncation. The blocks need to be reversed in
   * order.
   */

   //这里接收最高的几位
   sprintf(p, "%lu", *lp);
   while (*p)
      p++;

   while (lp != bn_data)
   {
      lp--;
      sprintf(p, "%019lu", *lp);
      while (*p)
         p++;
   }

   ok = 1;
   if (ok)
      return buf;
}

/*
输入：bignum *a，bignum *b
输出：bignum *r

得到bignum *a + bignum *b
*/
int BN_add(bignum *r, bignum *a, bignum *b)
{
   //上一次的进位标志
   int carry = 0;
   //这一次的进位标志
   int carry1 = 0;
   //较小的数的last
   int rlast;
   bignum *ret;
   //加法中一个数为0或者都为零的情况，然后是正常情况
   if (a->last == 0)
   {

      r->last = b->last;

      for (int i = 0; i < b->last; i++)
      {
         r->a[i] = b->a[i];
      }

      return 1;
   }
   else if (b->last == 0)
   {
      r->last = a->last;

      for (int i = 0; i < a->last; i++)
      {
         r->a[i] = a->a[i];
      }

      return 1;
   }
   else
   {
      //这里有bug
      if (a->last >= b->last)
      {
         ret = BN_dup(a);

         rlast = b->last;
      }
      else
      {
         ret = BN_dup(b);

         rlast = a->last;
      }

      for (int i = 0; i < rlast; i++)
      {
         //三个数相加，不止要判断一次进位
         ret->a[i] = a->a[i] + b->a[i];
         carry1 = (ret->a[i] >= a->a[i]) ? 0 : 1;

         ret->a[i] = ret->a[i] + carry;
         if (carry1 == 1)
         {
            carry = carry1;
            continue;
         }
         else
         {
            carry = (ret->a[i] >= a->a[i]) ? 0 : 1;
         }
      }
      for (int i = rlast; i < ret->last; i++)
      {
         ret->a[i] += carry;
         carry = (ret->a[i] >= carry) ? 0 : 1;
      }

      if (carry == 1)
      {

         // 这个if判断last是否大于max
         if (ret->last > ret->max)
         {
            ret->max += 1;
            free(ret->a);
            ret->a = (unsigned long *)malloc(sizeof(unsigned long) * (ret->max + 1));
         }

         ret->last++;
         ret->a[r->last - 1] = carry;
      }

      //将ret赋值给r
      r->last = ret->last;
      r->max = ret->max;
      free(r->a);
      r->a = ret->a;
   }
}

/*
输入：bignum *a, int w
输出：bignum *a

令bignum *a左移w个精度
*/
int BN_lshift64(bignum *a, int w)
{
   bignum *r = bn_new(a->max + w);
   for (int i = 0; i < w; i++)
   {
      r->a[i] = 0;
   }

   for (int i = w; i < (a->last + w); i++)
   {
      r->a[i] = a->a[i - w];
   }

   a->max = a->max + w;
   a->last = (a->last + w);
   free(a->a);
   a->a = r->a;
}

/*
输入：int digits
输出：返回值bignum *

创造一个值为0的bignum类型实例，返回指向该实例的指针
*/
bignum *BN_Zero(int digits)
{
   bignum *r;
   r = bn_new(digits);
   r->last = 0;
   return r;
}

/*
输入：bignum *a, bignum *b
输出：返回值bignum *

计算bignum *a * bignum *b
*/
bignum *BN_mul(bignum *a, bignum *b)
{
   //拆分b
   bignum **t = malloc(sizeof(bignum *) * (b->last));

   bignum *ret = BN_Zero(a->last + b->last + 3);

   for (int i = 0; i < b->last; i++)
   {
      t[i] = BN_dup(a);
      BN_mul_word(t[i], b->a[i]);

      BN_lshift64(t[i], i);
      BN_add(ret, ret, t[i]);

      /*调试*/
      if (i == 1)
      {
         bn2dec(ret);
      }
   }
   //t[0]所指向的大整数最小，将所有t[i]相加

   free(t);
   return ret;
}

// int main(){
//    // /*测试mul函数*/
//    // unsigned long r,a,w,c,temp;
//    // a=1844674407370955161;
//    // w=1234;

//    // mul(r,a,w,c);

//    // /*溢出，结果为79，unsigned long 长度为64个bit*/
//    // temp=18446744073709551615+80;

//    char *c="123979";
//    char *c1;
//    char *c2;
//    char *c3;

//    bignum *a;
//    bignum *b;
//    bignum *r;
//    int len=sizeof(*b);
//    len=sizeof(b);
//    len=sizeof(bignum);
//    dec2bn(&a,"32512356156213325621365123652135625654");
//    dec2bn(&b,"32689348815398456863434535223322395898549879739247");
//    // unsigned long r;

//    c1=bn2dec(a);
//    c2=bn2dec(b);

//    r=BN_mul(a,b);
//    c3=bn2dec(r);

// }