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
	//cout << "myprint�߳̿�ʼִ����" << "�̱߳��Ϊ �� " << num << endl;
	//cout << "myprint�߳̽���ִ����" << "�̱߳��Ϊ �� " << num << endl;
	cout << "�߳�idΪ �� " << std::this_thread::get_id() <<" "<< a[0] << "	" << a[1] << "	" << a[2] << endl;
}

class demo3 {
	list<int> MsgRecvQueue;
	mutex mtx1, mtx2;
	condition_variable cond;

public:
	//�ռ�����
	void inMsgRecvObjQueue()
	{
		for (int i = 0; i < 1000; i++)
		{
			unique_lock<mutex> munique(mtx1);
			unique_lock<mutex> munique2(std::move(munique));
			//mutex *pmtx = munique.release();		//��ǰ�����ͷ�mutex�Ŀ��ƣ���Ҫ�Լ��ֶ�����
			//std::chrono::milliseconds dura(20);
			//std::this_thread::sleep_for(dura);
			//mtx1.lock();
			//mtx2.lock();
			//{
			//lock_guard<mutex> mguard(mtx);
			cout << "inMsgRecvObjQueue()�߳�ִ�У�����Ϣ���������һ����Ϣ" << i << endl;
			MsgRecvQueue.push_back(i);
			//}
			//pmtx->unlock();
			//mtx1.unlock();
			//mtx2.unlock();
			//�����Ĵ���
		}
	}

	//ȡ������
	void outMsgrecvObjQueue()
	{
		for (int i = 0; i < 1000; i++)
		{
			
			if (MsgRecvQueue.empty())
			{
				cout << "�ռ��߳��Ѿ���ʼ�����ǵ�ǰ��Ϣ������û����Ϣ" << endl;
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
					//�õ�����
					int commad = MsgRecvQueue.front();
					MsgRecvQueue.pop_front();
					cout << "outMsgRecvObjQueue(���߳�ִ�У�����Ϣ������ȡ��һ����Ϣ " << commad << endl;
				}
				else
				{
					//û�õ���
					cout << "û�õ�����ֻ�ܸɵ�������" << endl;
				}
				//mtx1.unlock();
				//mtx2.unlock();
				//}
				//mtx.unlock();
				//�����Ĵ���
			}
		}
	}
};
