#include"test1.h"

void test1()
{
	//һ��ʹ�ú�����Ϊ�ɵ��ö���
	//0.thread�����߳�
	//1.join()����ϡ����룬���̵߳ȴ����߳�Ȼ���ټ�������ִ��
	//2.detach(), ���룬���̲߳��ȴ����̣߳�����ִ��
	//���߳�ִ��������߳�δִ����ᱨ���쳣
	//���߳�Ҫ�ȴ����е����߳�ִ�����
	//3.joinable(), �ж��Ƿ�ɹ�ʹ��join����detach�ɹ�
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

	//�������������̵߳ķ���
	//2.1 ʹ����,���߳̽��������߳�δִ���꣬�������̵߳ľֲ������ڴ�ռ���֮����գ�����ʹ��detach,�������߳�ʹ�õ��ڴ� �Ѿ���������
	//obj���������߳����и���
	//int myi = 6;
	//demo obj(myi);
	//thread mydemo(obj);
	//mydemo.join();
	//2.2 lambda���ʽ
	auto mylambada = [] {
		cout << "test �ҵ��߳̿�ʼ��" << endl;
		cout << "test1..." << endl;
		cout << "test2..." << endl;
		cout << "test3..." << endl;
		cout << "test4..." << endl;
		cout << "test5..." << endl;
		cout << "test6..." << endl;
		cout << "test �ҵ��߳̽�����" << endl;
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
