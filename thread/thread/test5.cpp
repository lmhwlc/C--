#include"test5.h"
#include<future>
void test5()
{
	//һ��������̨���񲢷���ֵ std::async��std::future
	//demo5 obj;
	//int tmp = 12;
	//cout << "���߳̿�ʼִ����" << endl;
	//cout << "main threadID = " << std::this_thread::get_id() << endl;
	//std::future<int> result = std::async(&demo5::print1, obj, tmp);
	//cout << "continue...." << endl;
	//cout << result.get() << endl;
	//cout << "hello wordl !" << endl;
	//cout << "���߳�ִ�н�����" << endl;

	//����packaged_task���������
	int tmp = 12;
	cout << "���߳̿�ʼִ����" << endl;
	cout << "main threadID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> pack(print2);
	thread t1(std::ref(pack), tmp);
	t1.join();
	std::future<int> result = pack.get_future();
	cout << result.get() << endl;
	cout << "hello wordl !" << endl;
	cout << "���߳�ִ�н�����" << endl;

}