#pragma once
#include <iostream>
using namespace std;
#include<thread>
#include<string>
#include<list>
#include<mutex>
#include<condition_variable>


int a[] = { 1,2,3 };
int flag = 0;
void myprint(int num)
{
	//cout << "myprint线程开始执行了" << "线程编号为 ： " << num << endl;
	//cout << "myprint线程结束执行了" << "线程编号为 ： " << num << endl;
	cout << "线程id为 ： " << std::this_thread::get_id() <<" "<< a[0] << "	" << a[1] << "	" << a[2] << endl;
}

class demo3 {
	list<int> MsgRecvQueue;
	mutex mtx1, mtx2;
	condition_variable cond;

public:
	//收集数据
	void inMsgRecvObjQueue()
	{
		for (int i = 0; i < 1000; i++)
		{
			unique_lock<mutex> munique(mtx1);
			unique_lock<mutex> munique2(std::move(munique));
			//mutex *pmtx = munique.release();		//当前对象释放mutex的控制，需要自己手动解锁
			//std::chrono::milliseconds dura(20);
			//std::this_thread::sleep_for(dura);
			//mtx1.lock();
			//mtx2.lock();
			//{
			//lock_guard<mutex> mguard(mtx);
			cout << "inMsgRecvObjQueue()线程执行，往消息队列中添加一条消息" << i << endl;
			MsgRecvQueue.push_back(i);
			//}
			//pmtx->unlock();
			//mtx1.unlock();
			//mtx2.unlock();
			//其他的代码
		}
	}

	//取出数据
	void outMsgrecvObjQueue()
	{
		for (int i = 0; i < 1000; i++)
		{
			
			if (MsgRecvQueue.empty())
			{
				cout << "收集线程已经开始，但是当前消息队列中没有消息" << endl;
			}
			else
			{
				//mtx.lock();
				//{
				//lock_guard<mutex> mguard(mtx);
				//mtx1.lock();
				//mtx2.lock();
				//lock(mtx1, mtx2);
				//mtx1.lock();
				//unique_lock<mutex> munique(mtx1,std::adopt_lock);
				unique_lock<mutex> munique(mtx1, std::try_to_lock);
				if (munique.owns_lock())
				{
					//拿到了锁
					int commad = MsgRecvQueue.front();
					MsgRecvQueue.pop_front();
					cout << "outMsgRecvObjQueue(）线程执行，从消息队列中取出一条消息 " << commad << endl;
				}
				else
				{
					//没拿到锁
					cout << "没拿到锁，只能干点别的事情" << endl;
				}
				//mtx1.unlock();
				//mtx2.unlock();
				//}
				//mtx.unlock();
				//其他的代码
			}
		}
	}
};
