#pragma once
#include <iostream>
using namespace std;
#include<thread>
#include<string>
void myprint()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "�ҵ��߳̿�ʼ��..." << endl;

		//...
		//...
		cout << "�ҵ��߳̽�����..." << endl;
	}
}


void test()
{
	cout << "test �ҵ��߳̿�ʼ��" << endl;
	cout << "test1..." << endl;
	cout << "test2..." << endl;
	cout << "test3..." << endl;
	cout << "test4..." << endl;
	cout << "test5..." << endl;
	cout << "test6..." << endl;
	//...
	//...
	cout << "test �ҵ��߳̽�����..." << endl;
}


class demo
{
public:
	int &m_i;
	demo(int &i) :m_i(i)
	{
		cout << "demo()���캯����ִ����" << endl;
	}
	demo(const demo& obj) :m_i(obj.m_i)
	{
		cout << "demo()�������캯����ִ����" << endl;
	}
	~demo()
	{
		cout << "~demo()������������ִ����" << endl;
	}

	void operator()()
	{
		cout << "�ҵ��߳�operator()��ʼִ����" << endl;
		//...
		cout << "m_i1��ֵΪ��" << m_i << endl;
		cout << "m_i2��ֵΪ��" << m_i << endl;
		cout << "m_i3��ֵΪ��" << m_i << endl;
		cout << "m_i4��ֵΪ��" << m_i << endl;
		cout << "m_i5��ֵΪ��" << m_i << endl;
		cout << "m_i6��ֵΪ��" << m_i << endl;
		cout << "�ҵ��߳�operator()����ִ����" << endl;
	}
};
