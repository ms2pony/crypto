/**
 * @file t1.c
 * 
 * @brief 
 * 
 * @version 0.1
 * @date 2022-01-04
 * @author pony (mspony@163.com)
 */

#include<x86intrin.h>
#include<stdio.h>

/**
 * @brief 使用rdtsc测试函数func的性能
 * 
 * @tparam T1 
 * @tparam T2 
 * @param func 
 * @return T1 
 */
template <typename T1,typename T2>
T1 time(T2 (*func)()){
	T1 t1,t2;
	t1=_rdtsc();
	func();
	t2=_rdtsc();

	return t2-t1;
}


double func(){
	return 1.0+2.0;
}

#define Dprint(s) printf("test s is:%s\n",#s)

#define TIME(func) time<unsigned long long,double>(func);

int main(){
	unsigned long long time1;
	unsigned long long time2;

	time1=time<unsigned long long,double>(func);
	Dprint(helloni);
	TIME(func);
}