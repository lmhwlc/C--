#include"test3.h"
#include<vector>
void test3()
{
	//һ����������߳�
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

	//������������
	//1. ֻ������
	//2. �ж���д

	//�������ݵı�������
	demo3 a;
	thread obj1(&demo3::inMsgRecvObjQueue, &a);
	thread obj2(&demo3::outMsgrecvObjQueue, &a);
	thread obj3(&demo3::outMsgrecvObjQueue, &a);
	obj1.join();
	obj2.join();
	obj3.join();

	//����������������
	//1.��������mutex��
	//2.std::lock_guard,�Զ�����
	//3.lock()����ͬʱ��ס���������
	//����

	//ʹ��unique_lockȡ��lock_guard
	//unique�ĵڶ�������1.adopt_lock, �Զ����� 2.try_to_lock�� ����ȥ��סmutex��3.def_lock,û�м�����mutex
	//unique_lock�ĳ�Ա����
	//1.lock,Ĭ������	unique_lock<mutex> cLock(mtx),
	//2.unlock,Ĭ���������÷�Χ�Զ�����	
	//3.try_lock.���Ը��������������ò���������false,�õ��򷵻�true,�������������
	//4.release,�����������mutex����ָ�룬���ͷ�����Ȩ�����unique_lock��mutex�����й�ϵ

	//�ġ�����Ȩ�Ĵ��� mutex

	//condition_variable �ȴ�һ��������ɵ���
	return;
}