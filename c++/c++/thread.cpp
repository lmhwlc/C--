#include"thread.h"
void TestThread() 
{
	InitializeCriticalSection(&Critical);	//初始化临界区对象
	thread task1(thread1);
	thread task2(thread2);
	task1.detach();
	task2.detach();
	Sleep(10 * 1000);
	system("pause");
}
