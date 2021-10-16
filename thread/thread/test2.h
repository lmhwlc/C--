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
		cout << "A()���캯����ִ����" << this << "thread_id = " << std::this_thread::get_id() << endl;
	}

	A(const A &a) :m_a(a.m_a)
	{
		cout << "A(A &a)�������캯����ִ����" << this << "thread_id = " << std::this_thread::get_id() << endl; 
	}

	~A()
	{
		cout << "~A()����������ִ����" << this << "thread_id = " << std::this_thread::get_id() << endl;
	}

	void thread_work(int num)
	{
		cout << "thread_work ���̵߳�id " << std::this_thread::get_id() << endl;
	}
};

void myprint1(const int i, const string &pmybuf)
{
	cout << i << endl;			//i������ʵ�ε����ã�����ֵ���ݣ����Լ������߳̽��������߳���Ȼ��������
	cout << pmybuf << endl;		//ָ����detach���߳�ʱ������ڰ�ȫ����,(ָ�봫�ݱ����ϻ���ָ�������ֵ���ݣ�
								//�����߳̽���ʱ���ͷ�ʵ��ָ��ָ����ڴ�
								//�ռ䣬��ʱ�β���ָ��ĵ�ַ��δ���壬���ܻᵼ�²������ϵĴ���)
}



void myprint2(const A &obj)
{
	obj.m_a = 10;
	cout << "���̵߳�id�� " << std::this_thread::get_id() << endl;
	return;
}

void myprint3(const unique_ptr<int> &p)
{
	cout << "���̵߳�id�� " << std::this_thread::get_id() << endl;
}