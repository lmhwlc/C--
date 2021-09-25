// c++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"test.h"

int main()
{
	OverrideTest();
	int *p = new int[10];
	_CrtDumpMemoryLeaks();
	return 0;
}
