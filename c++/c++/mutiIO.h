#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<sstream>
#include<fstream>

/*
	如何输入多行数据，形如：
	a 12 13
	b 14 15
	c 16 17

	...
	输入的行数未知
*/

void mutilIO();


/*
	eg.一个txt文本demo.txt，里面内容如下：
	1 2 3 6 5 4 7 8 9 6 5 4 2
	将其存放到数组中
*/

void GetFile();
