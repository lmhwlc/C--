#include"test3.h"
#include<vector>
void test3()
{
	//一、创建多个线程
	//vector<thread> mythreads;
	//for (int i = 0; i < 10; i++)
	//{
	//	mythreads.push_back(thread(myprint, i));
	//}
	//for (auto it = mythreads.begin(); it != mythreads.end(); it++)
	//{
	//	it->join();
	//}
	//cout << "hello world !" << endl;

	//二、共享数据
	//1. 只读数据
	//2. 有读有写

	//共享数据的保护案例
	demo3 a;
	thread obj1(&demo3::inMsgRecvObjQueue, &a);
	thread obj2(&demo3::outMsgrecvObjQueue, &a);
	thread obj3(&demo3::outMsgrecvObjQueue, &a);
	obj1.join();
	obj2.join();
	obj3.join();

	//三、保护共享数据
	//1.互斥量（mutex）
	//2.std::lock_guard,自动解锁
	//3.lock()函数同时锁住多个互斥量
	//死锁

	//使用unique_lock取代lock_guard
	//unique的第二个参数1.adopt_lock, 自动解锁 2.try_to_lock， 尝试去锁住mutex，3.def_lock,没有加锁的mutex
	//unique_lock的成员函数
	//1.lock,默认上锁	unique_lock<mutex> cLock(mtx),
	//2.unlock,默认脱离作用范围自动解锁	
	//3.try_lock.尝试给互斥量加锁，拿不到锁返回false,拿到则返回true,这个函数不阻塞
	//4.release,返回它管理的mutex对象指针，并释放所有权，这个unique_lock与mutex不再有关系

	//四、所有权的传递 mutex

	//condition_variable 等待一个条件达成的类
	return;
}