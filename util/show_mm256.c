#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <x86intrin.h>
#include <stdint.h>


void show_mm256_2bn_py(__m256i A_B[5]){
    printf("E=[");
    for(int i=0;i<5;i++){
        printf("0x%llx,",A_B[i][0]);
        if(i<4){
            printf("0x%llx,",A_B[i][1]);
        }else{
            printf("0x%llx",A_B[i][1]);
        } 
    }
    printf("]\n");

    printf("F=[");
    for(int i=0;i<5;i++){
        printf("0x%llx,",A_B[i][2]);
        if(i<4){
            printf("0x%llx,",A_B[i][3]);
        }else{
            printf("0x%llx",A_B[i][3]);
        } 
    }
    printf("]\n");
}