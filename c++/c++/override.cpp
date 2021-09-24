#include"override.h"

void OverrideTest()
{
	const int a = 3;
	fun(1);
	fun(1, 2);
	fun(3);
	demo obj;
	const demo obj2;
	obj.fun(1);
	obj2.fun(a);
}