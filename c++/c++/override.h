#pragma once
#include<iostream>
using namespace std;

//��ͨ�������ز����б������������Ͳ�ͬ�����ܸ��ݷ���ֵ���ֲ�ͬ�ĺ�����Ҳ���ܸ��ݲ����б��м�const����

//��ĳ�Ա�������Ը���const���κ���ʵ������
void fun(int a, int b)
{
	cout << a << " " << b << endl;
}

void fun(int a)
{
	cout << a << endl;
}

/*
	��ͨ�������ܸ��ݲ����б��const�����֣����������ʽ��������
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
	//���Ը���������Ƿ��ǳ�����������Ӧ�ĳ�Ա����ʵ������
	//ֻ���ݲ����Ƿ���const�������ֺ���
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
