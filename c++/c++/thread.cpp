#include"thread.h"
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
