#pragma once
#include <iostream>
using namespace std;
#include<thread>
#include<string>

class A {
	
public:
	mutable int m_a;
	A(int a) :m_a(a)
	{
		cout << "A()构造函数被执行了" << this << "thread_id = " << std::this_thread::get_id() << endl;
	}

	A(const A &a) :m_a(a.m_a)
	{
		cout << "A(A &a)拷贝构造函数被执行了" << this << "thread_id = " << std::this_thread::get_id() << endl; 
	}

	~A()
	{
		cout << "~A()析构函数被执行了" << this << "thread_id = " << std::this_thread::get_id() << endl;
	}

	void thread_work(int num)
	{
		cout << "thread_work 子线程的id " << std::this_thread::get_id() << endl;
	}
};

void myprint1(const int i, const string &pmybuf)
{
	cout << i << endl;			//i并不是实参的引用，而是值传递，所以即便主线程结束，子线程仍然可以运行
	cout << pmybuf << endl;		//指针在detach子线程时，会存在安全隐患,(指针传递本质上还是指针变量的值传递，
								//当主线程结束时会释放实参指针指向的内存
								//空间，此时形参所指向的地址就未定义，可能会导致不可意料的错误)
}



void myprint2(const A &obj)
{
	obj.m_a = 10;
	cout << "子线程的id是 " << std::this_thread::get_id() << endl;
	return;
}

void myprint3(const unique_ptr<int> &p)
{
	cout << "子线程的id是 " << std::this_thread::get_id() << endl;
}