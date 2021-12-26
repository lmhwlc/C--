// c++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include"mutiIO.h"
#include"thread.h"
#include"stl.h"
#include"Singleton.h"
#include"memory.h"
#include"Observer.h"
#include"override.h"
#include<queue>
struct student
{
	string name;
	int a;
	int b;
	int c;
	int d;
	student(string _name, int _a, int _b, int _c, int _d) :name(_name),a(_a), b(_b), c(_c), d(_d) {}
};

bool operator<(student st1, student st2)
{
	if (st1.a < st2.a)
		return true;
	else if (st1.a == st2.a)
	{
		if (st1.b < st2.b)
			return true;
		else if (st1.b == st1.b)
		{
			if (st1.c < st2.c)
				return true;
			else if (st1.c == st1.c)
			{
				if (st1.d < st2.d)
					return true;
			}
		}
	}
	return false;
}
int main()
{
	student st1("小明",73, 80, 86, 79);
	student st2("小花",77, 78, 60, 90);
	student st3("小刚",73, 79, 90, 90);
	student st4("小刚",73, 79, 90, 90);
	vector<student> vec{st1, st2, st3, st4};
	priority_queue<student> que;
	for (auto it : vec)
	{
		cout << it.name << " " << it.a << " " << it.b << " " << it.c << " " << it.d << endl;
	}
	for (int i = 0; i < vec.size(); i++)
		que.push(vec[i]);
	cout << endl << endl;
	while (!que.empty())
	{
		student it = que.top();
		cout << it.name << " " << it.a << " " << it.b << " " << it.c << " " << it.d << endl;
		que.pop();
	}

	//ObserverTest();
	return 0;
}
