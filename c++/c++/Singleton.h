#pragma once
#include<iostream>
using namespace std;
#include<mutex>

//懒汉式实现单例模式，需要二次判断空和锁机制确保线程安全
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
		cout <<"懒汉式 :"<< m << endl;
	}

};



//饿汉式实现单例模式,在构造函数
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
		cout << "饿汉式 :" << m << endl;
	}
};


void SingletonTest();