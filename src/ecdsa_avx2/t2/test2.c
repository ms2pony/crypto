//测试ecp_nistz256_mul_montx的执行过程
#  define BN_ULONG        unsigned long
#define P256_LIMBS      (256/BN_BITS2)
# define BN_BITS2       64

void ecp_nistz256_mul_mont(BN_ULONG res[P256_LIMBS],
                           const BN_ULONG a[P256_LIMBS],
                           const BN_ULONG b[P256_LIMBS]);

int main(){

	const BN_ULONG a[4]={319875643198,323298,3232879827,23239823};
	const BN_ULONG b[4]={12212165412,998872324,5161623123,65165123};
	BN_ULONG res[4]={0,0,0,0};

	ecp_nistz256_mul_mont(res,a,b);

	
}