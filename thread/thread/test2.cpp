#include"test2.h"

void test2()
{
	//һ��������ʱ������Ϊ�̲߳���
	//1.Ҫ��������壨����1�� ��Ҫ����ָ�����
	//2.Ҫ��������壨����2�� ��Ҫ���߳�����ʽ���ò����Ĺ��캯���������ڴ����߳�ʱ������ʱ����ʱ���е�
	//3.�ܽ᣺ ������ʹ��ֵ���ݣ��������ͣ�����󣩱�����ʽ����ת����ȫ�����ڴ����߳�ʱ������ʱ��������Ȼ��
	// �ں���������������������ʵ�Σ����鲻ʹ��detach,ֻʹ��join

	//�����߳�id
	//int num = 1;
	//int num1 = 2;
	////char ch[] = "this is a test!";
	//thread obj1(myprint, num, A(num1));
	//obj1.join();
	////obj1.detach();
	////cout << "hello world !" << endl;

	//std:ref ����
	//������������������ָ����Ϊ����
	cout << "���̵߳�id�� " << std::this_thread::get_id() << endl;
	//a a(6);
	//thread obj(myprint2, std::ref(a));
	//obj.join();
	//unique_ptr<int> ptr(new int(100));
	//thread obj(myprint3, std::move(ptr));
	//obj.join();

	//�ġ��ó�Ա����ָ�����̺߳���
	A a(10);
	thread obj(&A::thread_work, a, 15);
	obj.join();
	return;
}