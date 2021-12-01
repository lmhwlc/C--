#pragma once
#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include<iomanip>
#include<string>
#include<sstream>
using namespace std;

const int period = 8640;	//周期数
const int Sat_Num = 31;		//卫星的数量
const int Land_Num = 3;		//地面站的数量
bool IS_JNX[period][Sat_Num] = {false}; //卫星的属性

//传感器
string	StkSensor[] = { "", "Sensor11","Sensor12" ,"Sensor13" ,"Sensor14" ,"Sensor15","Sensor16","Sensor17","Sensor18",
							"Sensor21","Sensor22" ,"Sensor23" ,"Sensor24" ,"Sensor25","Sensor26","Sensor27","Sensor28",
							"Sensor31","Sensor32" ,"Sensor33" ,"Sensor34" ,"Sensor35","Sensor36","Sensor37","Sensor38",
							"SensorG1","SensorG2", "SensorG3", "SensorG4", "SensorG5", "SensorG6" };

//地面站
string StkGround[] = { "","From Target KASHI","From Target kUNMING","From Target MIYUN","From Target SANYA" };

//卫星名
string SatName[] = { " ","BEIDOU-3 M1","BEIDOU-3 M2","BEIDOU-3 M3","BEIDOU-3 M4","BEIDOU-3 M5","BEIDOU-3 M6","BEIDOU-3 M7","BEIDOU-3 M8","BEIDOU-3 M9","BEIDOU-3 M10",
						 "BEIDOU-3 M11","BEIDOU-3 M12","BEIDOU-3 M13","BEIDOU-3 M14","BEIDOU-3 M15","BEIDOU-3 M16","BEIDOU-3 M17","BEIDOU-3 M18",
						 "BEIDOU 12","BEIDOU 13","BEIDOU 15","BEIDOU 18","BEIDOU 19","BEIDOU 21",
						 "GEO1","GEO2","GEO3","IGSO1","IGSO2","IGSO3" };


int SatSatKjx[period][Sat_Num][Sat_Num];
int SatLandKjx[period][Land_Num][Sat_Num];

//获取地面站、传感器、卫星的编号
int GetIndex(string a, string* b)
{
	for (int i = 1; i < Sat_Num + 6; i++)
		if (strcmp(a.c_str(), b[i].c_str()) == 0)
			return i;
	return 0;
}

int GetIndex(int pos)
{
	if (pos < 10)
		return pos;
	else if (pos < 20)
	{
		return pos - 10;
	}
	else if (pos < 30)
	{
		return pos - 12;
	}
	else if (pos < 40)
	{
		return pos - 14;
	}
	else if (pos < 50)
	{
		return pos - 40;
	}
	else
		return pos - 26;
}

//空格替换逗号
void Replace(string &s)
{
	int n = s.size();
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == ',')
		{
			s[i] = ' ';
		}
	}
}

//获取可见性
void GetAccess(string file,bool flag)
{
	ifstream fin(file);
	string line;
	while (getline(fin,line))
	{
		Replace(line);
		vector<string> res;
		string result;
		stringstream input(line);
		while (input>>result)
		{
			res.push_back(result);
		}
		float start = atof(res[0].c_str());
		float stop = atof(res[1].c_str());
		int from = atoi(res[3].c_str());
		int to = atoi(res[4].c_str());
		from = GetIndex(from);
		to = GetIndex(to);
		int _start = start;
		if (start == _start)
		{
			while ((_start+1.5)<stop)
			{
				if (flag)
				{
					SatLandKjx[_start][from][to] = 1;
					IS_JNX[_start][to] = true;
					_start++;
				}
				else
				{
					SatSatKjx[_start][from][to] = 1;
					_start++;
				}
			}
		}
		else
		{
			_start++;
			while ((_start + 1.5) < stop)
			{
				if (flag)
				{
					SatLandKjx[_start][from][to] = 1;
					IS_JNX[_start][to] = true;
					_start++;
				}
				else
				{
					SatSatKjx[_start][from][to] = 1;
					_start++;
				}
			}
		}
	}
	fin.close();
}

void GetAllAccess()
{
	string meo_meo = "SLS visibility.csv";
	string meo_geo = "MEO_GEO.csv";
	string land_meo = "LAND_MEO.csv";
	string land_geo = "Land_GEO.csv";

	GetAccess(meo_meo, false);
	GetAccess(meo_geo, false);
	GetAccess(land_meo, true);
	GetAccess(land_geo, true);
}

////获取卫星属性以及星地可见性
//void GetSatGroundAcess()
//{
//	ifstream fin("SLL visibility.csv");
//	string line;
//	while (getline(fin, line))
//	{
//		int index1 = 0;
//		int index2 = 0;
//		int npos = line.find("60");
//		if (npos != -1)
//		{
//			int npos1 = line.find("To");
//			if (npos1 == -1)
//				break;
//			string ground = line.substr(8, npos1 - 11);
//			string meo = line.substr(npos1 + 10, 8);
//			index1 = GetIndex(ground, StkGround);
//			index2 = GetIndex(meo, StkSensor);
//			if (index1&&index2&&satelite[index1].GetSatNormal() && satelite[index2].GetSatNormal())
//			{
//				satelite[index2].SetSateliteJN_JW(true);
//				StaGroundKJX[index1][index2] = 1;
//				In_Set.insert(index2);
//			}
//		}
//	}
//	fin.close();
//}
//
//
////获取MEO星间可见性信息
//void GetSatSatAccess()
//{
//	ifstream fin("SLS visibility.csv");
//	string line;
//	while (getline(fin, line))
//	{
//		int index1 = 0;
//		int index2 = 0;
//		int npos = line.find("60");
//		if (npos != -1)
//		{
//			int npos1 = line.find("To");
//			int npos2 = line.find("Sensor");
//			if (npos1 == -1)
//				break;
//			string sensor = line.substr(npos2 + 7, 8);
//			string meo = line.substr(npos1 + 10, 8);
//			index1 = GetIndex(sensor, StkSensor);
//			index2 = GetIndex(meo, StkSensor);
//			if (index1&&index2&&satelite[index1].GetSatNormal() && satelite[index2].GetSatNormal())
//			{
//				KJSat[index1].push_back(index2);
//				SatSatKJX[index1][index2] = 1;
//			}
//		}
//	}
//	fin.close();
//}
//
//
////获取MEO与GEO,IGSO之间的可见性信息
//void GetGMAcess()
//{
//	ifstream fin("G_Mkjx.csv");
//	string line;
//	while (getline(fin, line))
//	{
//		int index1 = 0;
//		int index2 = 0;
//		int npos = line.find("60");
//		if (npos != -1)
//		{
//			int npos1 = line.find("To");
//			int npos2 = line.find("Sensor");
//			if (npos1 == -1)
//				break;
//			string meo = line.substr(npos2 + 7, 8);
//			string sensor = line.substr(npos1 + 10, 8);
//			index1 = GetIndex(sensor, StkSensor);
//			index2 = GetIndex(meo, StkSensor);
//			if (index1&&index2&&satelite[index1].GetSatNormal() && satelite[index2].GetSatNormal())
//			{
//				SatSatKJX[index1][index2] = 1;
//				SatSatKJX[index2][index1] = 1;
//				KJSat[index2].push_back(index1);
//			}
//		}
//	}
//	fin.close();
//}



