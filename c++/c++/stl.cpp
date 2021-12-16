#include"stl.h"
#include<iostream>
using namespace std;
#include<unordered_set>
#include<unordered_map>

void myUnoderedSet()
{
	unordered_map<int, int> myset;
	for (int i = 0; i < 200; i++)
	{
		cout << "元素个数 ： " << myset.size() << "桶的大小 : " << myset.bucket_count() << endl;
		myset[i] = i;
	}
}
