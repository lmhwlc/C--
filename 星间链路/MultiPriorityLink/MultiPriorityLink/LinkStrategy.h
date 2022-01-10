#pragma once
#include"AccessDate.h"
#include<fstream>
#include<iostream>
using namespace std;

struct satelite
{
	int number;				//卫星编号
	int InNum;				//可见境内星数量
	int OutNum;				//可见境外星数量
	set<int> LinkSats;		//卫星的链路情况
	vector<int> InSat;		//可见境内星
	vector<int> OutSat;		//可见境外星
};


//获取所有的数据信息
void GetAllInfo(int num);

//统计每个卫星的可见卫星数量（境内星，境外星）
void InitialSatInfo();

/*
	将境外星建链的顺序按可见境内星数量从小到大排序，境内星数量相同的则按可见境外星的数量从大到小排序
	将境内星被分配的顺序按其可见境外星的数量从小到大排序,境外星数量相同则按可见境内星数量从大到小排序
*/
void CreatLink();

//判断时隙表中的跳数约束
bool JudgeJump();

//打印时隙表
void PrintTimeSlotTable();

//统计每个境外星的链路数量
void GetJwxLinks();

//统计时延情况
void CalJump();

//获取一个周期的时隙表
void GetAllSlot(int stateNum);