#include<stdio.h>

//stringification operator即将一个标识符转换为字符串
# define convert(var) #var

/*
*	宏函数
*	功能：打印变量的名字和值
*	input：变量var
*	output：将var以及var的值打印在终端
*	return：无
*/
// # define print_var(var) printf("%s的值为:\n",convert(var))
void print_var();


int main() {
	int nihao;
	char *buhao;
	float henhao;
	printf("%s\n",convert(niao));
	printf("%s\n",convert(buhao));
	printf("%s\n",convert(henhao));

}