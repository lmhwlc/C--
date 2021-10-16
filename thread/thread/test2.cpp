#include"test2.h"

void test2()
{
	//一、传递临时对象作为线程参数
	//1.要避免的陷阱（解释1） 不要传递指针变量
	//2.要避免的陷阱（解释2） 不要在线程中隐式调用参数的构造函数，可以在创建线程时构造临时对象时可行的
	//3.总结： 简单类型使用值传递，复杂类型（类对象）避免隐式类型转换，全部都在创建线程时创建临时对象来，然后
	// 在函数参数里用引用来接受实参，建议不使用detach,只使用join

	//二、线程id
	//int num = 1;
	//int num1 = 2;
	////char ch[] = "this is a test!";
	//thread obj1(myprint, num, A(num1));
	//obj1.join();
	////obj1.detach();
	////cout << "hello world !" << endl;

	//std:ref 函数
	//三、传递类对象和智能指针作为参数
	cout << "主线程的id是 " << std::this_thread::get_id() << endl;
	//a a(6);
	//thread obj(myprint2, std::ref(a));
	//obj.join();
	//unique_ptr<int> ptr(new int(100));
	//thread obj(myprint3, std::move(ptr));
	//obj.join();

	//四、用成员函数指针做线程函数
	A a(10);
	thread obj(&A::thread_work, a, 15);
	obj.join();
	return;
}