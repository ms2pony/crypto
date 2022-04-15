#include "mm256op.h"

void get_mm256_2bn(__m256i A_B[5],unsigned int seed)
{
    srand(seed);

    for (int i = 0; i < 5; i++)
    {
        A_B[i] = _mm256_set_epi64x(
            // 32-bit转成26-bit
            rand() >> 6, rand() >> 6, rand() >> 6, rand() >> 6);
    };
}

int bit_count(uint64_t a)
{

    int count = 0;
    do
    {
        count++;
    } while (a >>= 1);
    return count;
}

void mm256_2bn_limbsize(__m256i A_B[5], int size[20])
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

/**
 * @brief 打印出的A_B兼容python的字典
 *
 * @param A_B
 * @require
 */
void show_mm256_2bn(__m256i A_B[5])
{
    printf("{\"A\":[");
    for (int i = 0; i < 5; i++)
    {
        printf("%llu,", A_B[i][0]);
        if (i < 4)
        {
            printf("%llu,", A_B[i][1]);
        }
        else
        {
            printf("%llu", A_B[i][1]);
        }
    }
    // printf("]}\n");
    printf("],\n");

    printf("\"B\":[");
    for (int i = 0; i < 5; i++)
    {
        printf("%llu,", A_B[i][2]);
        if (i < 4)
        {
            printf("%llu,", A_B[i][3]);
        }
        else
        {
            printf("%llu", A_B[i][3]);
        }
    }
    printf("]}\n");
}

void show_mm256_2bn1(__m256i A_B[5], int size[20])
{
    printf("A:  ");
    for (int i = 0; i < 5; i++)
    {
        printf("%16llx  ", A_B[i][0]);
        printf("%16llx  ", A_B[i][1]);
    }
    printf("\n");

    printf("    ");
    for (int i = 0; i < 10; i++)
    {
        printf("%16d  ", size[i]);
    }
    printf("\n");

    printf("B:  ");
    for (int i = 0; i < 5; i++)
    {
        printf("%16llx  ", A_B[i][2]);
        printf("%16llx  ", A_B[i][3]);
    }
    printf("\n");

    printf("    ");
    for (int i = 10; i < 20; i++)
    {
        printf("%16d  ", size[i]);
    }
    printf("\n");
}

void test_mm256_2bn_limbsize()
{
    
    __m256i A_B[5];
    get_mm256_2bn(A_B,23322);
    show_mm256_2bn(A_B);

    int size[20];
    mm256_2bn_limbsize(A_B, size);
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
//     get_mm256_2bn(A_B);
//     // show_mm256_2bn(A_B);

//     int size[20];
//     mm256_2bn_limbsize(A_B, size);

//     show_mm256_2bn1(A_B, size);
// }