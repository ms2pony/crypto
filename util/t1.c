#include<time.h>
#include <stdlib.h>
#include<stdio.h>

/* 解决使用time()作为srand函数参数产生随机数这个方法在
短时间内产生的随机数是相同的问题 */

int main(){
    unsigned time_now=(unsigned)(time(NULL));
    for(int i=0;i<30;i++){
        srand(time_now++);
        printf("%d\n",rand());
    }
}