#include <basic.h>

int bn_cmp(bignum *A, bignum *B);
unsigned long inverse(unsigned long, unsigned long);
int BN_sub(bignum *R, bignum *A)
{
	//只做结果为非负数的减法
	if (bn_cmp(R, A) < 0)
	{
		print("BN_sub异常，结果会为负数\n");
		return -1;
	}
	else
	{
		//上一次的进位标志
		int carry = 0;
		//这一次的进位标志
		int carry1 = 0;
		//较小的数的last字段
		int rlast;
		bignum *ret;
		//加法中一个数为0或者都为零的情况，然后是正常情况
		if (A->last == 0)
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
}

int BN_rshift64(bignum *a, int w)
{
	bignum *r = bn_new(a->max + w);

	for (int i = 0; i < w; i++)
	{
		r->a[i] = 0;
	}

	for (int i = w; i < (a->last); i++)
	{
		r->a[i - w] = a->a[i];
	}

	a->max = a->max + w;
	a->last = (a->last - w);
	free(a->a);
	a->a = r->a;
}

/*
* @description: 2^64 base

* @input:  A   a big number
* @input:  B   a big number
* @input:  a   head pointer, not malloced
* @output: a   array to which saves A's digits in base-r representation
* @return:     the last index of array 'a', i.e. 'K'
*/
bignum *montgomery_mult(bignum *A, bignum *B, bignum *M)
{
	bignum *R = BN_Zero(A->max + 2);
	bignum *temp = BN_Zero(A->max + 2);
	int array_len_B = B->last;
	unsigned long A0 = A->a[0];
	unsigned long inverse_M0 = inverse(M->a[0], BN_MASK2 + 1); //;todo

	int R0 = 0;
	bignum *q = BN_Zero(5);

	for (int i = 0; i <= array_len_B; i++)
	{
		BN_mul_word(A, B->a[i]);
		BN_add(R, R, A);

		//q=(R0+A0*B->a[i])*(BN_MASK2+1-inverse_M0);
		BN_UMULT_LOHI(q->a[0], q->a[1], A0, B->a[i]);
		BN_add_word(q, R0);
		BN_mul_word(q, BN_MASK2 + 1 - inverse_M0);

		//R+=q*M;
		temp = BN_mul(q, M);
		BN_mul(temp, R);

		//R/=(BN_MASK2+1);
		BN_rshift64(R, 1);

		R0 = R->a[0];
	}

	if (bn_cmp(R, M) > 0)
	{
		BN_sub(R, M); //todo
	}
	return R;
}

int main()
{
}