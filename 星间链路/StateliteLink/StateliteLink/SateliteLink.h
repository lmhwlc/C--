#pragma once
#include "Satelite.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
#define Sat_Num  25
#define GSat 7
#define Gap 21
#define Gzx 0

bool ResearchLinkSat(int index, vector<int> &sat);
/*
根据时隙表生成星间路由表
*/

//传感器
string	StkSensor[] = { "", "Sensor11","Sensor12" ,"Sensor13" ,"Sensor14" ,"Sensor15","Sensor16","Sensor17","Sensor18",
							"Sensor21","Sensor22" ,"Sensor23" ,"Sensor24" ,"Sensor25","Sensor26","Sensor27","Sensor28",
							"Sensor31","Sensor32" ,"Sensor33" ,"Sensor34" ,"Sensor35","Sensor36","Sensor37","Sensor38",
							"SensorG1","SensorG2", "SensorG3", "SensorG4", "SensorG5", "SensorG6"};

//地面站
string StkGround[] = { "","From Target KASHI","From Target kUNMING","From Target MIYUN","From Target SANYA" };

//卫星名
string SatName[] = { " ","BEIDOU-3 M1","BEIDOU-3 M2","BEIDOU-3 M3","BEIDOU-3 M4","BEIDOU-3 M5","BEIDOU-3 M6","BEIDOU-3 M7","BEIDOU-3 M8","BEIDOU-3 M9","BEIDOU-3 M10",
						 "BEIDOU-3 M11","BEIDOU-3 M12","BEIDOU-3 M13","BEIDOU-3 M14","BEIDOU-3 M15","BEIDOU-3 M16","BEIDOU-3 M17","BEIDOU-3 M18",
						 "BEIDOU 12","BEIDOU 13","BEIDOU 15","BEIDOU 18","BEIDOU 19","BEIDOU 21",
						 "GEO1","GEO2","GEO3","IGSO1","IGSO2","IGSO3" };

//卫星对象
Satelite satelite[Sat_Num+6];

//星地可见性
int StaGroundKJX[5][Sat_Num];

//星间可见性
int SatSatKJX[Sat_Num][Sat_Num];

//星间距离
int StaStaDistance[Sat_Num][Sat_Num][Gap+1];

//星间路由表
int Sat_SatLink[Sat_Num][Gap];

//地面路由表
int Sat_LandLink[Sat_Num][Gap];

//卫星的时隙表
int Sat_Gap[Sat_Num][Gap] = {0};

//存放境内星
set<int> In_Set;
set<int> Geo_set;
set<int> Meo_set;

//存放所有的卫星
vector<int> Sat;

//轮询标志位
int mark1 = 0;
int mark2 = 0;

//存放故障星
vector<int> DefaultSat;

//存放每个卫星对应的静态链路卫星
vector<int> StaticLink[Sat_Num];
//存放每个卫星对应的动态链路卫星；
vector<int> DynamicLink[Sat_Num];

//存放某个时刻每个卫星可见的卫星
vector<int> KJSat[Sat_Num+6];
vector<int> SKJSat[Sat_Num];
vector<int> DKJSat[Sat_Num];
queue<int> QKJSat[Sat_Num];

//MEO_GEO可见信息
int G_Mkjx[GSat][Sat_Num];

//卫星的待机数
typedef struct AwaitNum
{
	int index;
	int num;
};
AwaitNum await[Sat_Num];


float jump = 0;//总跳数
int jump1 = 0;  //一跳总数
int jump2 = 0;  //二跳总数
int jump3 = 0;  //三跳总数
float avgjump = 0.0;//平均每次信息传递的跳数


//卫星初始化
void InitialSatelite()
{
	int JW[] = { 3,4,5,6,7,9,14,15,16,20,21,22,23 };
	for (int i = 0; i < 13; i++)
	{
		satelite[JW[i]].SetSateliteJN_JW(false);
	}
	satelite[0].SetSateliteJN_JW(false);
	for (int j = 0; j < Sat_Num + 6; j++)
		satelite[j].SetSateliteName(SatName[j]);
}


//读取时隙表
void GetGap()
{
	ifstream infile;
	infile.open("gap.txt");
	if (!infile.eof())
	{
		for (int i = 1; i < Sat_Num; i++)
		{
			for (int j = 1; j < Gap; j++)
			{
				infile >> Sat_Gap[i][j];
			}
		}
	}
	else
		cout << "文件打开失败" << endl;
	infile.close();
}



//
//
////选择可见星i在时隙j中距离最小的卫星
//int SelectMinDis(int i, int j)
//{
//	int JW_MinDistance = 100000;
//	int JN_MinDistance = 100000;
//	int JN_min = 0;
//	int JW_min = 0;
//
//	//如果当前卫星没建链
//	if (satelite[i].GetSateliteJL() == false)
//	{
//		//获取与卫星i距离最小的境内星和距离最小的境外星
//		for (int k = 1; k < Sat_Num; k++)
//		{
//			if (satelite[k].GetSateliteJL() == false && SatSatKJX[i][k])
//			{
//				//距离最小的境内星
//				if (satelite[k].GetSateliteJN_JW())
//				{
//					if (JN_MinDistance > StaStaDistance[i][k][j])
//					{
//						JN_MinDistance = StaStaDistance[i][k][j];
//						JN_min = k;
//					}
//				}
//				//距离最小的境外星
//				else
//				{
//					if (JW_MinDistance > StaStaDistance[i][k][j])
//					{
//						JW_MinDistance = StaStaDistance[i][k][j];
//						JW_min = k;
//					}
//				}
//			}
//		}
//	}
//	
//
//	//如果当前卫星i是境内星，则优先其与距离最小的境外星建链,否则与距离最小的境内星建链
//	if (satelite[i].GetSateliteJN_JW())
//	{
//		if (JW_min)
//			return JW_min;
//		else
//			return JN_min;
//	}
//	else
//	{
//		if (JN_min)
//			return JN_min;
//		else
//			return JW_min;
//	}	
//}
//
//
////初始化卫星建链状态
//void InitilaSatJL()
//{
//	for (int j = 1; j < Sat_Num; j++)
//		satelite[j].SetSateliteJL(false);
//}
//
//
//读取星间距离信息
//void GetSatSatDis()
//{
//	ifstream fin("distance2.csv");
//	string line;
//	int index = 1;
//	int index1 = 0;
//	int index2 = 0;
//	while (getline(fin, line))
//	{
//		定位当前卫星
//		int npos1 = line.find("to");
//		if (npos1 != -1)
//		{
//			string sensor = line.substr(npos1 - 9, 8);
//			string meo = line.substr(npos1 + 3, 5);
//			index1 = GetIndex(sensor, StkSensor);
//			index2 = GetIndex(meo, StkSensor);
//			index = 1;
//			continue;
//		}
//		istringstream is;
//		is.str(line);
//		int distance;
//		is >> distance;
//		StaStaDistance[index1][index2][index] = distance;
//		index++;
//	}
//	fin.close();
//}
//

//随机1~5颗故障星
void RandomSat()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		Sat.push_back(i);
	}
	random_shuffle(Sat.begin(), Sat.end());

	cout << "故障的卫星为：" << endl;
	for (int j = 0; j < Gzx; j++)
	{
		DefaultSat.push_back(Sat[j]);
		cout << Sat[j] << "		";
		satelite[Sat[j]].SetSatNomral(false);
	}
	cout << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//获取地面站、传感器、卫星的编号
int GetIndex(string a, string* b)
{
	for (int i = 1; i < Sat_Num+6; i++)
		if (strcmp(a.c_str(), b[i].c_str()) == 0)
			return i;
	return 0;
}


//获取每卫星的静态链路卫星
void GetStaticLink()
{
	ifstream fin("SLS.csv");
	string line;
	while (getline(fin, line))
	{
		int index1 = 0;
		int index2 = 0;
		int npos = line.find("8640");
		if (npos != -1)
		{
			int npos1 = line.find("To");
			int npos2 = line.find("Sensor");
			string sensor = line.substr(npos2 + 7, 8);
			string meo = line.substr(npos1+10, 8);
			index1 = GetIndex(sensor, StkSensor);
			index2 = GetIndex(meo, StkSensor);
			if(index1&&index2&&satelite[index1].GetSatNormal() && satelite[index2].GetSatNormal())
				StaticLink[index1].push_back(index2);
		}
	}
	fin.close();
}

//获取卫星对应的动态卫星
void GetDynamicLink()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		for (int j = 1; j < Sat_Num; j++)
		{
			if (ResearchLinkSat(j, StaticLink[i]) == false)
			{
				DynamicLink[i].push_back(j);
			}
		}
	}
}

//判断某个卫星是否是当前卫星的静态链路卫星
bool JudgeStaticSat(int i, int j)
{
	for (int k = 0; k < StaticLink[i].size(); k++)
	{
		if (j == StaticLink[i][k])
			return true;
	}
	return false;
}


//获取卫星属性以及星地可见性
void GetSatGroundAcess()
{
	ifstream fin("SLL visibility.csv");
	string line;
	while (getline(fin, line))
	{
		int index1 = 0;
		int index2 = 0;
		int npos = line.find("60");
		if (npos != -1)
		{
			int npos1 = line.find("To");
			if (npos1 == -1)
				break;
			string ground = line.substr(8, npos1 - 11);
			string meo = line.substr(npos1 + 10, 8);
			index1 = GetIndex(ground, StkGround);
			index2 = GetIndex(meo, StkSensor);
			if (index1&&index2&&satelite[index1].GetSatNormal() && satelite[index2].GetSatNormal())
			{
				In_Set.insert(index2);
				if (index2 < 25)
					Meo_set.insert(index2);
				else
					Geo_set.insert(index2);
				satelite[index2].SetSateliteJN_JW(true);
				StaGroundKJX[index1][index2] = 1;
			}		
		}
	}
	fin.close();
}


//获取MEO星间可见性信息
void GetSatSatAccess()
{
	ifstream fin("SLS visibility.csv");
	string line;
	while (getline(fin, line))
	{
		int index1 = 0;
		int index2 = 0;
		int npos = line.find("60");
		if (npos != -1)
		{
			int npos1 = line.find("To");
			int npos2 = line.find("Sensor");
			if (npos1 == -1)
				break;
			string sensor = line.substr(npos2 + 7, 8);
			string meo = line.substr(npos1 + 10, 8);
			index1 = GetIndex(sensor, StkSensor);
			index2 = GetIndex(meo, StkSensor);
			if (index1&&index2&&satelite[index1].GetSatNormal()&& satelite[index2].GetSatNormal())
			{
				SatSatKJX[index1][index2] = 1;
				KJSat[index1].push_back(index2);
				QKJSat[index1].push(index2);
				if (JudgeStaticSat(index1, index2))
					SKJSat[index1].push_back(index2);
				else
					DKJSat[index1].push_back(index2);
			}
		}
	}
	fin.close();
}


//获取MEO与GEO,IGSO之间的可见性信息
void GetGMAcess()
{
	ifstream fin("G_Mkjx.csv");
	string line;
	while (getline(fin, line))
	{
		int index1 = 0;
		int index2 = 0;
		int npos = line.find("60");
		if (npos != -1)
		{
			int npos1 = line.find("To");
			int npos2 = line.find("Sensor");
			if (npos1 == -1)
				break;
			string meo = line.substr(npos2 + 7, 8);
			string sensor = line.substr(npos1 + 10, 8);
			index1 = GetIndex(sensor, StkSensor);
			index2 = GetIndex(meo, StkSensor);
			if (index1&&index2&&satelite[index1].GetSatNormal() && satelite[index2].GetSatNormal())
			{
				G_Mkjx[index1 - 24][index2] = 1;
			}
		}
	}
	fin.close();
}


//随机境外星
//打印时隙表
void PrintGap(int p[Sat_Num][Gap])
{
	cout << "星间链路况如下：" << endl;
	for (int i = 1; i < Sat_Num; i++)
	{
		int from = await[i].index;
		cout << setw(5) << left << i;
		for (int j = 1; j < Gap; j++)
		{
			cout << setw(5) << left << p[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//打印当前的境内星
void PrintJNX()
{
	cout << "境内星为：" << endl;
	for (auto i : In_Set)
		cout << i << "	";
	cout << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//判断某个时隙卫星i是否建链
bool SatJL(int i,int time)
{
	for (int j = 1; j < Sat_Num; j++)
	{
		if ( i == Sat_Gap[j][time])
			return true;
	}
	return false;
}


//初始化时隙表
void InitialGap()
{
	for (int i = 0; i < Sat_Num; i++)
		for (int j = 0; j < Gap; j++)
			Sat_Gap[i][j] = 0;
}


//静态卫星是否分配过
bool AllocatStaticSat(int from,int sat)
{
	for (int i = 1; i < Gap; i++)
		if (sat == Sat_Gap[from][i])
			return true;
	return false;
}


//寻找卫星的可用空闲时隙
void SelectValidGap(int from,int to)
{
	for (int i = 1; i < Gap; i++)
	{
		if (!AllocatStaticSat(from,to)&&Sat_Gap[to][i] == 0 && Sat_Gap[from][i] == 0 && !SatJL(to, i))
		{
			Sat_Gap[from][i] = to;
			Sat_Gap[to][i] = from;
			break;
		}
	}
}

//删除已经建链的静态链路
bool RemoveStaLink(int &index,vector<int> &sat)
{
	vector<int>::iterator it = sat.begin();
	for (; it != sat.end(); *it++)
	{
		if (*it == index)
		{
			sat.erase(it);
			return true;
		}
	}
	return false;
}

//打乱可见星的顺序
void SortLink()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		for (int j = 0; j < KJSat[i].size(); j++)
		{
			int num = rand() % (KJSat[i].size() - 1);
			swap(KJSat[i][j], KJSat[i][num]);
		}
	}
}

int JNXSource[25][3];
void InitialJNXSource()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		if (satelite[i].GetSateliteJNX() == false)
		{
			for (int j = 0; j < KJSat[i].size(); j++)
			{
				int index = KJSat[i][j];
				if (satelite[index].GetSateliteJNX())
					JNXSource[i][0]++;
				else
					JNXSource[i][1]++;
			}
		}
		JNXSource[25][2] = 0;
	}
}

void PrintJNXSource()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		cout << "卫星"<<i<<": "<<JNXSource[i][0] << "	" << JNXSource[i][1] << "	" << JNXSource[i][0] + JNXSource[i][1] << endl;;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


int SatSource[25][21];
//初始化每个境外星可分配的境内星资源
void InitialSatSource()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			SatSource[i][j] = 9 - j;
		}
	}

	for (int i = 1; i < Sat_Num; i++)
	{
		for (int j = 13; j < Gap; j++)
		{
			SatSource[i][j] = Gap - j;
		}
	}
}

void PrintSource()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		cout << "卫星" << setw(5) << left <<i << ":" ;
		for (int j = 1; j < Gap; j++)
		{
			cout << setw(5) << left << SatSource[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}

//查找境内星资源最多的境外星
int ResearchMaxJNX()
{
	int max1 = -1;
	int max2 = -1;
	int index1 = -1;
	int index2 = -1;
	bool flag = false;
	for (int i = 1; i < Sat_Num; i++)
	{
		if (satelite[i].GetSateliteJL() == false && satelite[i].GetSateliteJNX() == false)
		{
			if (JNXSource[i][0])
			{
				flag = true;
				if (JNXSource[i][0] > max1)
				{
					max1 = JNXSource[i][0];
					index1 = i;
				}
			}
			else
			{
				if (JNXSource[i][1] > max2)
				{
					max2 = JNXSource[i][1];
					index2 = i;
				}
			}
		}
	}

	if (flag)
		return index1;
	else
		return index1;
}

//循环遍历每个境外星的可见星
int ResearchKJX(int sat,int mark,bool flag)
{
	int size = KJSat[sat].size();

	//境内星与境内星建链
	if(flag)
		while (1)
		{
			int index = KJSat[sat][mark%size];
			if (satelite[index].GetSateliteJNX())
			{
				return index;
			}
			mark++;
			if (mark > size * 2)
			{
				return mark;
			}
		}
	//境外星与境外星建链
	else
	{
		while (1)
		{
			int index = KJSat[sat][mark%size];

			if (satelite[index].GetSateliteJNX()==false)
			{
				return index;
			}
			mark++;
			if (mark > size * 2)
			{
				return mark;
			}
		}
	}
}


//查找资源数最小的未建链境外星
int ResearchMinSource(int _gap)
{
	int min = 100;
	int index = -1;
	for (int i = 1; i < Sat_Num; i++)
	{
		if (satelite[i].GetSateliteJL() == false&&satelite[i].GetSateliteJNX()==false)
		{
			if (SatSource[i][_gap] < min)
			{
				min = SatSource[i][_gap];
				index = i;
			}
		}
	}
	return index;
}

//查找资源数最小的未建链境外星（上一时隙为境外-境外链路）
int ResearchMinSource(int _gap, vector<int> &jw_jw)
{
	int min = 100;
	int index = -1;
	for (int i = 0; i < jw_jw.size(); i++)
	{
		int jw = jw_jw[i];
		if (satelite[jw].GetSateliteJL() == false)
		{
			if (SatSource[jw][_gap] < min)
			{
				min = SatSource[jw][_gap];
				index = jw;
			}
		}
	}
	RemoveStaLink(index, jw_jw);
	return index;
}

//查找卫星的资源是否被使用
bool ResearchLinkSat(int index, vector<int> &sat)
{
	vector<int>::iterator it = sat.begin();
	for (; it != sat.end(); it++)
	{
		if (*it == index)
			return true;
	}
	return false;
}

//每次分配资源后更新卫星的资源数
void UpdataSource(int from,int to,int _gap)
{
	for (int i = 1; i < Sat_Num; i++)
	{
		if (ResearchLinkSat(from, StaticLink[i]))
		{
			SatSource[i][_gap]--;
		}
		if (ResearchLinkSat(to, StaticLink[i]))
		{
			SatSource[i][_gap]--;
		}
	}
	//PrintSource();
}


//将静态链路分配到各个不同时隙中
void AllocateStaLink()
{
	bool flag = false;
	vector<int> JW_JW;
	vector<int> temp;
	for (int i = 1; i < 9; i++)
	{
		//第一个时隙建链
		if (i == 1)
		{
			for (int j = 1; j < 13; j++)
			{
				int min = ResearchMinSource(i);
				//int min = ResearchMaxJNX();
				flag = false;
				//优先进行境外星与境内星建链
				for (int k = 0; k < StaticLink[min].size(); k++)
				{
					int index = StaticLink[min][k];

					if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX())
					{
						Sat_Gap[min][i] = index;
						Sat_Gap[index][i] = min;
						satelite[min].SetSateliteJL(true);
						satelite[index].SetSateliteJL(true);
						StaticLink[min].erase(StaticLink[min].begin() + k);
						RemoveStaLink(min, StaticLink[index]);
						//PrintGap(Sat_Gap);

						UpdataSource(min, index, i);
						//PrintSource();
						flag = true;
						//JNXSource[min][0]--;
						//PrintJNXSource();
						break;
					}
				}
				//不存在境外星与境内星的链路则进行境外星与境外星的建链
				for (int k = 0; k < StaticLink[min].size()&&(flag==false); k++)
				{
					int index = StaticLink[min][k];

					if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX() == false)
					{
						Sat_Gap[min][i] = index;
						Sat_Gap[index][i] = min;
						JW_JW.push_back(index);
						JW_JW.push_back(min);
						satelite[min].SetSateliteJL(true);
						satelite[index].SetSateliteJL(true);
						StaticLink[min].erase(StaticLink[min].begin() + k);
						RemoveStaLink(min, StaticLink[index]);
						//PrintGap(Sat_Gap);

						UpdataSource(min, index, i);
						//PrintSource();
						//JNXSource[min][1]--;
						//JNXSource[index][1]--;
						//PrintJNXSource();
						break;
					}
				}
			}

			//PrintGap(Sat_Gap);
			//PrintSource();
			for (int m = 1; m < Sat_Num; m++)
			{
				satelite[m].SetSateliteJL(false);
				satelite[m].SetSatVisit(false);
			}
		}
		//剩下的时隙建链，优先建链上一时隙中的境外星与境外星的链路
		else
		{
			int start = 0;
			while (JW_JW.size())
			{
				int min = ResearchMinSource(i, JW_JW);
				start++;
				//优先进行境外星与境内星建链
				for (int k = 0; k < StaticLink[min].size(); k++)
				{
					int index = StaticLink[min][k];

					if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX())
					{
						Sat_Gap[min][i] = index;
						Sat_Gap[index][i] = min;
						satelite[min].SetSateliteJL(true);
						satelite[index].SetSateliteJL(true);
						StaticLink[min].erase(StaticLink[min].begin() + k);
						RemoveStaLink(min, StaticLink[index]);
						//PrintGap(Sat_Gap);

						UpdataSource(min, index, i);
						PrintSource();
						//JNXSource[min][0]--;
						//PrintJNXSource();
						break;
					}
				}
			}

			PrintGap(Sat_Gap);
//PrintSource();

//对剩下的境内星-境外星链路进行分配
for (int j = start; j < 13; j++)
{
	int min = ResearchMinSource(i);
	//int min = ResearchMaxJNX();
	//优先进行境外星与境内星建链
	flag = false;
	for (int k = 0; k < StaticLink[min].size(); k++)
	{
		int index = StaticLink[min][k];

		if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX())
		{
			Sat_Gap[min][i] = index;
			Sat_Gap[index][i] = min;
			satelite[min].SetSateliteJL(true);
			satelite[index].SetSateliteJL(true);
			StaticLink[min].erase(StaticLink[min].begin() + k);
			RemoveStaLink(min, StaticLink[index]);
			PrintGap(Sat_Gap);
			flag = true;
			UpdataSource(min, index, i);
			//PrintSource();
			//JNXSource[min][0]--;
			//PrintJNXSource();
			break;
		}
	}
	//不存在境外星与境内星的链路则进行境外星与境外星的建链
	for (int k = 0; k < StaticLink[min].size() && (flag == false); k++)
	{
		int index = StaticLink[min][k];

		if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX() == false)
		{
			Sat_Gap[min][i] = index;
			Sat_Gap[index][i] = min;
			JW_JW.push_back(index);
			JW_JW.push_back(min);
			satelite[min].SetSateliteJL(true);
			satelite[index].SetSateliteJL(true);
			StaticLink[min].erase(StaticLink[min].begin() + k);
			RemoveStaLink(min, StaticLink[index]);
			PrintGap(Sat_Gap);

			UpdataSource(min, index, i);
			//PrintSource();
			//JNXSource[min][1]--;
			//JNXSource[index][1]--;
			//PrintJNXSource();
			break;
		}
	}
}
//PrintGap(Sat_Gap);
//PrintSource();

for (int m = 1; m < Sat_Num; m++)
{
	satelite[m].SetSateliteJL(false);
	satelite[m].SetSatVisit(false);
}
		}
	}
}

////将静态链路分配到各个不同时隙中
//void AllocateLink()
//{
//	vector<int> temp;
//	for (int i = 1; i < Sat_Num; i++)
//	{
//		temp.push_back(i);
//	}
//
//	for (int i = 0; i < temp.size(); i++)
//	{
//		int num = rand() % (temp.size()-1);
//		swap(temp[i], temp[num]);
//	}
//
//	for (int i = 1; i < Sat_Num; i++)
//	{
//		int index = temp[i-1];
//		if (satelite[index].GetSatNormal())
//		{
//			int from = index;
//			for (int j = 0; j < SKJSat[index].size(); j++)
//			{
//				int to = SKJSat[index][j];
//				SelectValidGap(from, to);
//			}	
//		}
//	}
//	vector<int>().swap(temp);
//}

//为所有境外卫星分配境内星或者境外星
void AllocateJWX()
{
	bool flag = true;
	vector<int> JW_JW;

	//第一个时隙建链
	for (int j = 1; j < Sat_Num; j++)
	{
		if (satelite[j].GetSateliteJNX() == false&&satelite[j].GetSateliteJL()==false)
		{
			int mark = SatSource[j][2];
			int size = KJSat[j].size();

			//优先进行境外星与境内星建链
			while (1)
			{
				int t = mark % size;
				int index = KJSat[j][t];
				if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX())
				{
					Sat_Gap[j][1] = index;
					Sat_Gap[index][1] = j;
					satelite[j].SetSateliteJL(true);
					satelite[index].SetSateliteJL(true);
					SatSource[j][2] = t + 1;
					//PrintGap(Sat_Gap);
					break;
				}
				mark++;
				//没有可建链的境内星
				if (mark > size * 2)
				{
					flag = false;
					mark = SatSource[j][2];
					break;
				}
			}

			//不存在境外星与境内星的链路则进行境外星与境外星的建链
			if (flag == false)
			{
				while (1)
				{
					int t = mark % size;
					int index = KJSat[j][t];
					if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX() == false)
					{
						Sat_Gap[j][1] = index;
						Sat_Gap[index][1] = j;
						JW_JW.push_back(j);
						JW_JW.push_back(index);
						satelite[j].SetSateliteJL(true);
						satelite[index].SetSateliteJL(true);
						SatSource[1][2] = t + 1;
						//PrintGap(Sat_Gap);
						break;
					}
					mark++;
					//存在未建链的境外星
					if (mark > size * 2)
					{
						JW_JW.push_back(j);
						break;
					}
				}
				flag = true;
			}
		}
	}

	for (int m = 1; m < Sat_Num; m++)
	{
		satelite[m].SetSateliteJL(false);
		satelite[m].SetSatVisit(false);
	}

	//对剩余时隙卫星进行建链
	for (int i = 2; i < Gap; i++)
	{
		//优先对上个时隙中未建链和境外——境外的情况建链
 		int s = JW_JW.size();
		while (s--)
		{
			int jw = JW_JW[s];
			int mark = SatSource[jw][2];
			int size = KJSat[jw].size();

			while (1)
			{
				int t = mark % size;
				int index = KJSat[jw][t];
				if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX())
				{
					Sat_Gap[jw][i] = index;
					Sat_Gap[index][i] = jw;
					satelite[jw].SetSateliteJL(true);
					satelite[index].SetSateliteJL(true);
					SatSource[jw][2] = t + 1;
					RemoveStaLink(jw, JW_JW);
					//PrintGap(Sat_Gap);
					break;
				}
				mark++;
				if (mark > size * 2)
				{
					//cout << "无法在两跳完成" << endl;
					
					break;
				}
			}
		}

		//对剩下的境外星建链
		for (int j = 1; j < Sat_Num; j++)
		{
			if (satelite[j].GetSateliteJNX() == false && satelite[j].GetSateliteJL() == false)
			{
				int mark = SatSource[j][2];
				int size = KJSat[j].size();

				//优先进行境外星与境内星建链
				while (1)
				{
					int t = mark % size;
					int index = KJSat[j][t];
					if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX())
					{
						Sat_Gap[j][i] = index;
						Sat_Gap[index][i] = j;
						satelite[j].SetSateliteJL(true);
						satelite[index].SetSateliteJL(true);
						SatSource[j][2] = t + 1;
						//PrintGap(Sat_Gap);
						break;
					}
					mark++;
					//没有可建链的境内星
					if (mark > size * 2)
					{
						flag = false;
						mark = SatSource[j][2];
						break;
					}
				}

				//不存在境外星与境内星的链路则进行境外星与境外星的建链
				if (flag == false)
				{
					while (1)
					{
						int t = mark % size;
						int index = KJSat[j][t];
						if (satelite[index].GetSateliteJL() == false && satelite[index].GetSateliteJNX() == false)
						{
							Sat_Gap[j][i] = index;
							Sat_Gap[index][i] = j;
							JW_JW.push_back(j);
							JW_JW.push_back(index);
							satelite[j].SetSateliteJL(true);
							satelite[index].SetSateliteJL(true);
							SatSource[j][2] = t + 1;
							//PrintGap(Sat_Gap);
							break;
						}
						mark++;
						//存在未建链的境外星
						if (mark > size * 2)
						{
							JW_JW.push_back(j);
							break;
						}
					}
					flag = true;
				}
			}
		}

		for (int m = 1; m < Sat_Num; m++)
		{
			satelite[m].SetSateliteJL(false);
			satelite[m].SetSatVisit(false);
		}
	}
}

//根据卫星可见性将不可见的链路置为待机状态
void InitialLink()
{
	for (int i = 9; i < Gap; i++)
	{
		for (int j = 1; j < Gap; j++)
		{
			int from = i;
			int to = Sat_Gap[i][j];
			if (SatSatKJX[from][to] == 0)
			{
				Sat_Gap[i][j] = 0;
			}
		}
	}
}


//建立MEO境内星与境外星之间的链路
void IncreaseM_MLink(vector<int> in, int from)
{
	int insize = in.size();
	for (int gap = 1; gap < Gap; gap++)
	{
		if (!insize)
			break;
		int flag = 0;
		if (Sat_Gap[from][gap] == 0)
		{
			while (1)
			{
				int to = in[mark2%insize];
				if (SatJL(to, gap) == false && Sat_Gap[to][gap] == 0)
				{
					Sat_Gap[from][gap] = to;
					Sat_Gap[to][gap] = from;
					mark2++;
					break;
				}
				flag++;
				if (flag > 10)
					break;
				mark2++;
			}
		}
	}
}


//初始化卫星在20个时隙的建链顺序
void CreatLink()
{
	//某个卫星可见的境内星和境外星
	vector<int> KJ_JNX;

	//境内星和境外星建链
	for (int i = 1; i < Sat_Num; i++)
	{
		if (satelite[i].GetSateliteJNX() == false)
		{
			mark2 = 0;
			for (int j = 0; j < KJSat[i].size(); j++)
			{
				int sat = KJSat[i][j];
				if (satelite[sat].GetSateliteJNX())
					KJ_JNX.push_back(sat);
			}
			IncreaseM_MLink(KJ_JNX, i);
		}
		vector<int>().swap(KJ_JNX);
	}
}


//选择境内GEO_IGSO与境外MEO之间的链路
void IncreaseG_MLink(vector<int> out,int from)
{
	int outsize = out.size();
	
	for (int gap = 1; gap < Gap; gap++)
	{
		if (outsize == 0)
			break;
		int flag = 0;
		if (Sat_Gap[from][gap] == 0)
		{
			while (1)
			{
				int to = out[mark1%outsize];
				if (SatJL(to, gap) == false)
				{
					Sat_Gap[from][gap] = to;
					mark1++;
					break;
				}
				flag++;
				if (flag > 10)
					break;
				mark1++;
			}
		}
	}
}


//将空闲时隙建立境外星与境外星之间的链路
void IncreaseMW_MWlink(vector<int> out, int from)
{
	int outsize = out.size();

	for (int gap = 1; gap < Gap; gap++)
	{
		if (outsize == 0)
			break;
		int flag = 0;
		if (Sat_Gap[from][gap] == 0)
		{
			while (1)
			{
				int to = out[mark2%outsize];
				if (SatJL(to, gap) == false)
				{

					Sat_Gap[from][gap] = to;
					mark2++;
					break;
				}
				flag++;
				if (flag > 10)
					break;
				mark2++;
			}
		}
	}
}


//统计每个卫星对应的空闲时隙
void MarkAwaitNum()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		await[i].index = i;
		for (int j = 1; j < Gap; j++)
		{
			if (Sat_Gap[i][j] == 0)
				await[i].num++;
		}
	}
}


//判断卫星中是否存在空闲时隙
bool JudgeAwait(int i)
{
	for (int gap = 0; gap < Gap; gap++)
	{
		if (Sat_Gap[i][gap] == 0)
			return true;
	}
	return false;
}


//打印空闲时隙
void printawait()
{
	for (int i = 1; i < Sat_Num; i++)
		cout << await[i].index << " " << await[i].num << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//优化链路
void UpgradeLink()
{
	//计算每个卫星的空闲时隙
	MarkAwaitNum();

	//从大到小排序
	for (int i = 1; i < Sat_Num -1; i++)
	{
		for (int j = 1; j < Sat_Num - i; j++)
		{
			if (await[j].num < await[j+1].num)
			{
				AwaitNum tep;
				tep.index = await[j].index;
				tep.num = await[j].num;
				await[j].index = await[j+1].index;
				await[j].num = await[j+1].num;
				await[j+1].index = tep.index;
				await[j+1].num = tep.num;
			}
		}	
	}


	//加入高轨卫星建立境外——境内星间链路
	vector<int> KJ_JNX;

	for (int i = 1; i < Sat_Num; i++)
	{
		int from = await[i].index;
		mark1 = 0;
		if (!satelite[from].GetSateliteJNX() && JudgeAwait(from)&&satelite[from].GetSatNormal())
		{
			for (int k = 1; k < GSat; k++)
			{
				if (G_Mkjx[k][from] && satelite[k+24].GetSateliteJNX())
					KJ_JNX.push_back(k+24);
			}
			IncreaseG_MLink(KJ_JNX,from);	
			vector<int>().swap(KJ_JNX);
		}
	}
	//对剩下的境外星对应的空闲时隙安排与境外星建链
	vector<int> KJ_JWX;

	for (int i = 1; i < Sat_Num; i++)
	{
		int from = await[i].index;
		mark2 = 0;
		if (!satelite[from].GetSateliteJNX() && JudgeAwait(from) && satelite[from].GetSatNormal())
		{
			for (int j = 0; j < KJSat[i].size(); j++)
			{
				int sat = KJSat[i][j];
				if (!satelite[sat].GetSateliteJNX())
					KJ_JWX.push_back(sat);
			}
			IncreaseMW_MWlink(KJ_JWX, from);
			vector<int>().swap(KJ_JWX);
		}
	}
}

//交换时隙的顺序
void Exchange()
{ 
	int temp;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < Sat_Num; j++)
		{
			temp = Sat_Gap[j][i];
			Sat_Gap[j][i * 2 - 1] = Sat_Gap[j][21 - 2 * i + 1];
			Sat_Gap[j][8 + 2 * i - 1] = temp;
		}
	}
}
//根据时隙表生成路由表
bool CreatRount()
{
	//计算一个帧里前18个时隙的路由
	for (int i = 1; i < Gap - 2; i++)
	{
		for (int j = 1; j < Sat_Num; j++)
		{
			if (satelite[j].GetSatNormal())
			{
				int index1 = Sat_Gap[j][i];

				//当前卫星为境内星
				if (satelite[j].GetSateliteJNX())
				{
					//境内星与境内星建链
					if (index1&&satelite[index1].GetSateliteJNX())
					{
						Sat_SatLink[j][i] = index1;
						if (index1 < Sat_Num)
							Sat_SatLink[index1][i] = j;
					}
					continue;
				}

				int index2 = Sat_Gap[j][i + 1];
				int index3 = Sat_Gap[j][i + 2];

				//当前卫星为境外星且i时隙与境内星建链
				if (index1 && satelite[index1].GetSateliteJNX())
				{
					Sat_SatLink[j][i] = index1;
					if (index1 < Sat_Num)
						Sat_SatLink[index1][i] = j;

					continue;
				}
				//当前卫星为境外星且i+1时隙与境内星建链
				if (index2&&satelite[index2].GetSateliteJNX())
				{
					Sat_SatLink[j][i+1] = index2;
					if (index1 < Sat_Num)
						Sat_SatLink[index2][i+1] = j;

					continue;
				}
				//当前卫星为境外星且i+2时隙与境内星建链
				if (index3&&satelite[index3].GetSateliteJNX())
				{
					Sat_SatLink[j][i + 2] = index2;
					if (index1 < Sat_Num)
						Sat_SatLink[index2][i + 2] = j;

					continue;
				}
				//index1,index2,index3都不是境内星，则经过中转星进行数据回传
				if (!satelite[index1].GetSateliteJNX() && !satelite[index2].GetSateliteJNX() && !satelite[index3].GetSateliteJNX())
				{
					//i时隙连接境外星(index1)作为中转星
					if (index1)
					{
						//在i+1时隙与境内星建链
						int index4 = Sat_Gap[index1][i + 1];
						if (index4 && satelite[index4].GetSateliteJNX())
						{
							//j->index1
							Sat_SatLink[j][i] = index1;
							if (index1 < Sat_Num)
								Sat_SatLink[index1][i] = j;

							//index1->index4
							Sat_SatLink[index1][i + 1] = index4;
							if (index4 < Sat_Num)
								Sat_SatLink[index4][i + 1] = index1;

							continue;
						}

						//在i+2时隙与境内星建链
						int index5 = Sat_Gap[index1][i + 2];
						if (index5 && satelite[index5].GetSateliteJNX())
						{
							//j->index1
							Sat_SatLink[j][i] = index1;
							if (index1 < Sat_Num)
								Sat_SatLink[index1][i] = j;

							//index1->index5
							Sat_SatLink[index1][i + 2] = index5;
							if (index5 < Sat_Num)
								Sat_SatLink[index5][i + 2] = index1;

							continue;
						}

						//通过index4再次中转到中转星index7的下个时隙（i+2）
						int index7 = Sat_Gap[index4][i + 2];
						if (index7 && satelite[index7].GetSateliteJNX())
						{
							//j->index1
							Sat_SatLink[j][i] = index1;
							if (index1 < Sat_Num)
								Sat_SatLink[index1][i] = j;

							//index1->iddex4
							Sat_SatLink[index1][i + 1] = index4;
							if (index4 < Sat_Num)
								Sat_SatLink[index4][i + 1] = index1;

							//index4->index7

							Sat_SatLink[index4][i + 2] = index7;
							if (index7 < Sat_Num)
								Sat_SatLink[index7][i + 2] = index4;

							continue;
						}
					}

					//i+1时隙连接境外星(index2)作为中转星
					if (index2)
					{
						//在i+2时隙与境内星建链
						int index6 = Sat_Gap[index2][i + 2];
						if (index6 && satelite[index6].GetSateliteJNX())
						{
							//j->index2
							Sat_SatLink[j][i + 1] = index2;
							if (index2 < Sat_Num)
								Sat_SatLink[index2][i + 1] = j;

							//index2->index6
							Sat_SatLink[index1][i + 2] = index6;
							if (index6 < Sat_Num)
								Sat_SatLink[index6][i + 2] = index1;

							continue;
						}
					}

					//境外星无法在10s内将数据回穿
					cout << "从时隙" << i << "开始时境外星" << j << "无法在10s内完成数据回传" << endl;
					break;
				}
			}

		}
	}
	return true;
}


//计算各个跳数情况
void CalJump()
{
	//前18个时隙的跳数情况
	for (int gap = 1; gap < Gap - 2; gap++)
	{
		for (int i = 1; i < Sat_Num; i++)
		{
			if (satelite[i].GetSatNormal())
			{
				if (!satelite[i].GetSateliteJNX())
				{
					int to1 = Sat_SatLink[i][gap];
					int to2 = Sat_SatLink[i][gap + 1];
					if (to1)
					{
						if (satelite[to1].GetSateliteJNX())
							jump1++;
						else if (to2)
						{
							if (satelite[to2].GetSateliteJNX())
								jump2++;
							else
								jump3++;
						}
					}
					else if (to2)
					{
						if (satelite[to2].GetSateliteJNX())
							jump2++;
						else
							jump3++;
					}
					else
						jump3++;
				}
			}

		}
		jump = jump1 + jump2 + jump3;
		avgjump = (jump1 + jump2 * 2 + jump3 * 3) / jump;
	}
}


//打印星地可见性信息
void PrintStaGroundAcesss()
{
	cout << "星地可见性为：" << endl;
	for (int i = 1; i < 5; i++)
	{
		cout << setw(5) << left << i;
		for (int j = 1; j < Sat_Num; j++)
		{
			cout << setw(5) << left << StaGroundKJX[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//打印MEO星间可见性信息
void PrintStaStaAccess()
{
	cout << "每个卫星对应的动态链路卫星为：" << endl;
	for (int i = 1; i < Sat_Num; i++)
	{
		cout << "卫星" << i << "对应的静态链路卫星为：" << endl;
		for (int j = 0; j < DKJSat[i].size(); j++)
		{
			cout << setw(5) << left << DKJSat[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//打印GEO_IGSO与MEO之间的可见性
void PrintG_MAcess()
{
	cout << "GEO_IGSO与MEO之间的可见性：" << endl;
	for (int i = 1; i < GSat; i++)
	{
		cout << setw(5) << left << i;
		for (int j = 1; j < Sat_Num; j++)
		{
			cout << setw(5) << left << G_Mkjx[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//打印星间距离信息
void PrintSatSatDist()
{
	for (int k = 1; k < 3; k++)
	{
		cout << "---------------------------第" << k << "时隙距离信息" << "---------------------------" << endl;
		for (int i = 1; i < 2; i++)
		{
			cout << setw(8) << left << i;
			for (int j = 1; j < Sat_Num; j++)
			{
				cout << setw(8) << left << StaStaDistance[i][j][k];
			}
			cout << endl;
		}
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;
	}
}
	

//打印路由表
void PrintRount()
{
	//路由表
	cout << "路由情况如下：" << endl;
	ofstream out;
	out.open("Rounter.txt");
	for (int i = 1; i < Sat_Num; i++)
	{
		cout << setw(5) << left << i ;
		out << setw(5) << left << i ;
		for (int j = 1; j < Gap; j++)
		{
			out << setw(5) << left << Sat_SatLink[i][j];
			cout << setw(5) << left << Sat_SatLink[i][j];
		}
		cout << endl;
		out << endl;
	}	
	out.close();
}


//打印每个卫星对应的静态链路卫星
void PrintStaticSat()
{
	cout << "每个卫星对应的八个静态链路卫星为：" << endl;
	for (int i = 1; i < Sat_Num; i++)
	{
		cout << "卫星" << i << "对应的静态链路卫星为："<<endl;
		for (int j = 0; j < StaticLink[i].size(); j++)
			cout << StaticLink[i][j] << "	";
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//输出所有的跳数情况
void PrintJump()
{
	cout << "所有的跳数情况如下：" << endl;
	cout << "一跳情况：" << jump1 << "占比：" << jump1 / jump << endl;
	cout << "二跳情况：" << jump2 << "占比：" << jump2 / jump << endl;
	cout << "三跳情况：" << jump3 << "占比：" << jump3 / jump << endl;
	cout << "平均跳数为：" << avgjump << endl;
}