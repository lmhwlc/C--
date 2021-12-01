// StateliteLink.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"SateliteLink.h"
#include"GAlink.h"

int main()
{
	srand(int(time(NULL)));
	
	//随机故障1--5颗星
	//RandomSat();

	//获取境内星
	GetSatGroundAcess();
	PrintJNX();

	//获取卫星的永久可见卫星
	GetStaticLink();
	//PrintStaticSat();

	//获取星间可见性
	GetSatSatAccess();

	//获取MEO卫星与高轨卫星的可见性
	GetGMAcess();
	PrintG_MAcess();

	//初始化标志位
	InitialJNXSource();

	//分配境内星-境外星和境外星-境外星链路
	SortLink();
	AllocateJWX();
	PrintGap(Sat_Gap);

	//加入高轨卫星提高通信效率
	UpgradeLink();
	PrintGap(Sat_Gap);

	CreatRount();
	PrintRount();
	CalJump();
	PrintJump();

	/*InitialPopulation();
	Reproduce();*/

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
