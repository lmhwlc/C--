#include"thread.h"
#include<windows.h>
#include<iostream>
#include<thread>
using namespace std;

int number = 1;					//����ȫ�ֱ���
CRITICAL_SECTION Critical;		//�����ٽ������

void thread1()
{
	while (number < 100) {
		EnterCriticalSection(&Critical);
		cout << "thread 1 :" << number << endl;
		++number;
		Sleep(100);
		LeaveCriticalSection(&Critical);
	}
}


void thread2()
{
	while (number < 100) {
		EnterCriticalSection(&Critical);
		cout << "thread 2 :" << number << endl;
		++number;
		Sleep(100);
		LeaveCriticalSection(&Critical);
	}
}


void TestThread() 
{
	InitializeCriticalSection(&Critical);	//��ʼ���ٽ�������
	thread task1(thread1);
	thread task2(thread2);
	task1.detach();
	task2.detach();
	Sleep(10 * 1000);
	system("pause");
}
