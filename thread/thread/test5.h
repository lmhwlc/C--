#pragma once
#include<iostream>
using namespace std;
#include<thread>
#include<mutex>

class demo5
{
public:
	int print1(int a)
	{
		cout << a << endl;
		cout << "�߳̿�ʼִ����" << endl;
		cout << "threadID : " << std::this_thread::get_id() << endl;
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "�߳�ִ�н�����" << endl;
		return 666;
	}
};

int print2(int a)
{
	cout << a << endl;
	cout << "�߳̿�ʼִ����" << endl;
	cout << "threadID : " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "�߳�ִ�н�����" << endl;
	return 5;
}