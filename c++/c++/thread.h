#pragma once
#include<windows.h>
#include<iostream>
#include<thread>
using namespace std;

int number = 1;	//����ȫ�ֱ���
CRITICAL_SECTION Critical;		//�����ٽ������

void thread1() {
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

