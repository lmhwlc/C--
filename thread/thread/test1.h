#pragma once
#include <iostream>
using namespace std;
#include<thread>
#include<string>
void myprint()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "我的线程开始了..." << endl;

		//...
		//...
		cout << "我的线程结束了..." << endl;
	}
}


void test()
{
	cout << "test 我的线程开始了" << endl;
	cout << "test1..." << endl;
	cout << "test2..." << endl;
	cout << "test3..." << endl;
	cout << "test4..." << endl;
	cout << "test5..." << endl;
	cout << "test6..." << endl;
	//...
	//...
	cout << "test 我的线程结束了..." << endl;
}


class demo
{
public:
	int &m_i;
	demo(int &i) :m_i(i)
	{
		cout << "demo()构造函数被执行了" << endl;
	}
	demo(const demo& obj) :m_i(obj.m_i)
	{
		cout << "demo()拷贝构造函数被执行了" << endl;
	}
	~demo()
	{
		cout << "~demo()的析构函数被执行了" << endl;
	}

	void operator()()
	{
		cout << "我的线程operator()开始执行了" << endl;
		//...
		cout << "m_i1的值为：" << m_i << endl;
		cout << "m_i2的值为：" << m_i << endl;
		cout << "m_i3的值为：" << m_i << endl;
		cout << "m_i4的值为：" << m_i << endl;
		cout << "m_i5的值为：" << m_i << endl;
		cout << "m_i6的值为：" << m_i << endl;
		cout << "我的线程operator()结束执行了" << endl;
	}
};
