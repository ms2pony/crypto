#include<stdlib.h>

int main(){
	int *a=(int*)malloc(sizeof(int)*8);
	int num=sizeof(a);
	int b[10]={0};
	num=sizeof(b);
	num=sizeof(b)/sizeof(b[0]);

}