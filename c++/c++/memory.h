#pragma once
#include<iostream>
using namespace std;
void memory()
{
	/*
		sizeof 计算的是数组所在内存的大小，和它里面的元素无关
		ch1的内存大小是 6字节,5个字符加一个结束符‘\0’，支符号串的长度是5
		ch2计算的是指针的大小，指针大小为 4字节，指向的字符串长度为5
		ch3的内存大小是 10字节，字符串长度为5
	*/
	char ch1[] = "abcde";
	const char *ch2 = "abcde";
	char ch3[10] = "abcde";
	cout << sizeof(ch1) << " " << strlen(ch1) << endl;
	cout << sizeof(ch2) << " " << strlen(ch2) << endl;
	cout << sizeof(ch3) << " " << strlen(ch3) << endl;
	/*
		输出：
		6 5
		4 5
		10 5
	*/
}

