#include"test5.h"
#include<future>
void test5()
{
	//一、创建后台任务并返回值 std::async、std::future
	//demo5 obj;
	//int tmp = 12;
	//cout << "主线程开始执行了" << endl;
	//cout << "main threadID = " << std::this_thread::get_id() << endl;
	//std::future<int> result = std::async(&demo5::print1, obj, tmp);
	//cout << "continue...." << endl;
	//cout << result.get() << endl;
	//cout << "hello wordl !" << endl;
	//cout << "主线程执行结束了" << endl;

	//二、packaged_task：打包任务
	int tmp = 12;
	cout << "主线程开始执行了" << endl;
	cout << "main threadID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> pack(print2);
	thread t1(std::ref(pack), tmp);
	t1.join();
	std::future<int> result = pack.get_future();
	cout << result.get() << endl;
	cout << "hello wordl !" << endl;
	cout << "主线程执行结束了" << endl;

}