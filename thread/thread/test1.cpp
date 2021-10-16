#include"test1.h"

void test1()
{
	//一、使用函数作为可调用对象
	//0.thread创建线程
	//1.join()，汇合、加入，主线程等待子线程然后再继续往下执行
	//2.detach(), 分离，主线程不等待子线程，各自执行
	//主线程执行完而子线程未执行完会报告异常
	//主线程要等待所有的子线程执行完毕
	//3.joinable(), 判断是否成功使用join或者detach成功
	//thread myobj(myprint);
	//thread testobj(test);
	//if (testobj.joinable())
	//{
	//	cout << "detach : joinable() == true" << endl;
	//	testobj.detach();
	//	
	//}
	//else
	//{
	//	cout << "detach : joinable() == false" << endl;
	//}
	//myobj.detach();

	//二、其他创建线程的方法
	//2.1 使用类,主线程结束而子线程未执行完，属于主线程的局部变量内存空间随之会回收，即便使用detach,但是子线程使用的内存 已经被回收了
	//obj对象在子线程中有副本
	//int myi = 6;
	//demo obj(myi);
	//thread mydemo(obj);
	//mydemo.join();
	//2.2 lambda表达式
	auto mylambada = [] {
		cout << "test 我的线程开始了" << endl;
		cout << "test1..." << endl;
		cout << "test2..." << endl;
		cout << "test3..." << endl;
		cout << "test4..." << endl;
		cout << "test5..." << endl;
		cout << "test6..." << endl;
		cout << "test 我的线程结束了" << endl;
	};
	thread myobj(mylambada);
	myobj.join();
	cout << "hello world1!" << endl;
	cout << "hello world2!" << endl;
	cout << "hello world3!" << endl;
	cout << "hello world4!" << endl;
	cout << "hello world5!" << endl;
	//testobj.join();
	//myobj.join();
}
