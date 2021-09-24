#pragma once
#include<iostream>
using namespace std;

//普通函数重载参数列表数量或者类型不同，不能根据返回值区分不同的函数，也不能根据参数列表中加const区分

//类的成员函数可以根据const修饰函数实现重载
void fun(int a, int b)
{
	cout << a << " " << b << endl;
}

void fun(int a)
{
	cout << a << endl;
}

/*
	普通函数不能根据参数列表加const来区分，因此这种形式不能重载
	void fun(const int a)
	{
		cout << "const" << a << endl;
	}
*/



class demo
{
	int m;
public:
	demo(int _m = 0) :m(_m) {}
	//可以根据类对象是否是常量来调用相应的成员函数实现重载
	//只根据参数是否是const不能区分函数
	void fun(const int a)const
	{
		cout << "const" << m + a << endl;
	}

	void fun(int a)
	{
		m = m + a;
		cout << m << endl;
	}
};
