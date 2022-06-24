#include <util/bn_avx2/bn_avx2_info.h>
#include <util/bn_avx2/get_bn_avx2.h>
#include <util/bn_avx2/show_bn_avx2.h>

static int bit_count(uint64_t a)
{

	int count = 0;
	do
	{
		count++;
	} while (a >>= 1);
	return count;
}

void limb_size(__m256i A_B[5], int size[20])
{
	uint64_t *temp;
	for (int i = 0; i < 5; i++)
	{
		temp = (uint64_t *)&A_B[i];
		size[2 * i] = bit_count(temp[0]);
		size[2 * i + 1] = bit_count(temp[1]);
		size[2 * i + 10] = bit_count(temp[2]);
		size[2 * i + 10 + 1] = bit_count(temp[3]);
	}
}

void test_mm256_2bn_limbsize()
{

	__m256i A_B[5];
	get_bn_avx2(A_B, 23322);
	show_bn_avx2_2(A_B);

	int size[20];
	limb_size(A_B, size);
	printf("A各个limb的bit长度：");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", size[i]);
	}
	printf("\n");

	printf("B各个limb的bit长度：");
	for (int i = 10; i < 20; i++)
	{
		printf("%d ", size[i]);
	}
	printf("\n");
}

// int main()
// {
//     // printf("%10d\n", 3);

//     __m256i A_B[5];
//     get_bn_avx2(A_B);
//     // show_bn_avx2_2(A_B);

//     int size[20];
//     limb_size(A_B, size);

//     show_bn_avx2(A_B, size);
// }