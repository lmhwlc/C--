#pragma once
#include<iostream>
using namespace std;
#include<mutex>

//����ʽʵ�ֵ���ģʽ����Ҫ�����жϿպ�������ȷ���̰߳�ȫ
class SingletonA
{
private:
	SingletonA(){}
	static SingletonA *pInstance;
	int m;
public:

	static SingletonA* getInstanceA()
	{
		mutex mtx;
		if (pInstance == nullptr)
		{
			mtx.lock();
			if (pInstance == nullptr)
			{
				pInstance = new SingletonA();
			}
			mtx.unlock();
		}
		return pInstance;
	}

	void set(int _m)
	{
		m = _m;
	}

	void show()
	{
		cout <<"����ʽ :"<< m << endl;
	}

};



//����ʽʵ�ֵ���ģʽ,�ڹ��캯��
class SingletonB
{
private:
	SingletonB(){};
	static SingletonB instance;
	int m;

public:
	static SingletonB* getInstanceB()
	{
		return &instance;
	}

	void set(int _m)
	{
		m = _m;
	}

	void show()
	{
		cout << "����ʽ :" << m << endl;
	}
};


void SingletonTest();