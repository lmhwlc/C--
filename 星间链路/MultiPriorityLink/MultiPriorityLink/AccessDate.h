#pragma once
#include<iostream>
#include<set>
#include<vector>
#include<string>
#include<map>
#include<unordered_set>
using namespace std;

const int PeriodNum = 8640;			//回归周期的时隙数目
const int SatNum = 30;				//星座中的卫星数目
const int LandNum = 4;				//地面站的数量

//获取状态可视矩阵
void GetStateAccess(int);

//数据初始化
void InitialData();


//空格替换逗号
void ReplaceSpace(string& str);


//处理一条可见性记录
void GetLine(string& line, double& StartTime, double& EndTime, int& Duration, int& From, int& To);


//读取星间可见性信息
void GetSatSatAccess(string& FileName);


//读取星地可见性信息
void GetSatLandAccess(string& FileName);


//按状态划分整个周期
void DivideState(int);


//打印星间可见性
void PrintSatSatAccess(vector<vector<bool>>& VecSatSat, vector<bool>& VecJnx);


//打印星地可见性
void PrintSatLandAccess(vector<bool>& VecJnx);


//获取卫星属性和可见性信息
void GetSatLandInfo();


//相邻可视矩阵是否变化
bool JudgeAccess(vector<vector<bool>>& v1, vector<vector<bool>>& v2);


//寻找下一个可视矩阵变化的时间节点
int GetAccessPoint(vector<vector<vector<bool>>>& vec, int CurPoint, int StateNum);


//求MEO11在不同时长的状态下，可见性的数量、占比
void GetAnsMeo(vector<vector<vector<bool>>>& vec, int StateNum);


//保存不同时隙长度下的可见性信息
void SaveALlInfo();

