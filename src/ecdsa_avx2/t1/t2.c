#include <immintrin.h>

__m256i Z[10]={0};
__m256i A_B[5];
__m256i C_D[5];

__m256i* computer_256(__m256i A_B[5], __m256i C_D[5]){
	__m256i C_D1[5];

	__m256i U[5],V[5];
	__m256i temp,temp1,temp2;
	__m256i zero=_mm256_set_epi64x(0,0,0,0);

	for(int i=0;i<5;i++){
		if(i<4){
			C_D1[i]=_mm256_alignr_epi8(C_D[i+1],C_D[i],8);
		}else{
			C_D1[i]=_mm256_alignr_epi8(C_D[0],C_D[4],8);
		}
		

	}

	for(int i=0;i<5;i++){
		U[i]=_mm256_shuffle_epi32(A_B[i],0x44);

		for(int j=0;j<5;j++){
			temp=_mm256_mul_epu32(U[i],C_D[j]);
			Z[i+j]=_mm256_add_epi64(Z[i+j],temp);
		}

		V[i]=_mm256_shuffle_epi32(A_B[i],0xEE);
		for(int j=0;j<4;j++){
			temp=_mm256_mul_epu32(V[i],C_D1[j]);
			Z[i+j+1]=_mm256_add_epi64(Z[i+j+1],temp);
		}
		// W = MUL(V,<C,D>4)
		temp= _mm256_mul_epu32(V[i],C_D1[4]);
		temp1=_mm256_blend_epi32(temp,zero,0x33);
		temp2=_mm256_blend_epi32(temp,zero,0xcc);
		Z[i]=_mm256_add_epi64(Z[i],temp1);
		Z[i+5]=_mm256_add_epi64(Z[i+5],temp2);
	}

	return Z;
}