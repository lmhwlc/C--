#pragma once
#include<iostream>
using namespace std;
#include<thread>
#include<mutex>


mutex mtx;

class demo4
{
private:
	demo4() {}
	static demo4* obj;
	
public:
	static demo4* getInstace()
	{
		if (obj == nullptr)
		{
			unique_lock<mutex> mymutex(mtx);
			if (obj == nullptr)
			{
				obj = new demo4();
				static destoryObj del;
			}
		}
		return obj;
	}

	class destoryObj
	{
	public:
		~destoryObj()
		{
			if (demo4::obj)
			{
				demo4::obj = nullptr;
			}
		}
	};

	void print()
	{
		cout << "hello world" << endl;
	}
};

demo4* demo4::obj = nullptr;

void myPrint(demo4& obj)
{
	obj.print();
}