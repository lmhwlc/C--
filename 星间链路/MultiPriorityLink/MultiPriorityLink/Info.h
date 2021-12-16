//#pragma once
//#include<iostream>
//#include<fstream>
//#include<set>
//#include<vector>
//#include<iomanip>
//#include<string>
//#include<sstream>
//#include<map>
//#include<unordered_set>
//using namespace std;
//
//const int period = 8640;	//周期数
//const int Sat_Num = 31;		//卫星的数量
//const int Land_Num = 3;		//地面站的数量
//bool IS_JNX[period][Sat_Num] = { false }; //卫星的属性
//const int day = 1440;		//一天的周期数
//map<string, int> craftIndex;
//vector<unordered_set<int>> staticlink(Sat_Num);
//
////传感器
//string	StkSensor[] = { "", "11","12" ,"13" ,"14" ,"15","16","17","18",
//							"21","22" ,"23" ,"24" ,"25","26","27","28",
//							"31","32" ,"33" ,"34" ,"35","36","37","38",
//							"G1","G2", "G3", "G4", "G5", "G6" };
//
////卫星名
//string SatName[] = { " ","BEIDOU-3 M1","BEIDOU-3 M2","BEIDOU-3 M3","BEIDOU-3 M4","BEIDOU-3 M5","BEIDOU-3 M6","BEIDOU-3 M7","BEIDOU-3 M8","BEIDOU-3 M9","BEIDOU-3 M10",
//						 "BEIDOU-3 M11","BEIDOU-3 M12","BEIDOU-3 M13","BEIDOU-3 M14","BEIDOU-3 M15","BEIDOU-3 M16","BEIDOU-3 M17","BEIDOU-3 M18",
//						 "BEIDOU 12","BEIDOU 13","BEIDOU 15","BEIDOU 18","BEIDOU 19","BEIDOU 21",
//						 "GEO1","GEO2","GEO3","IGSO1","IGSO2","IGSO3" };
//
//int SatSatKjx[period][Sat_Num][Sat_Num];		//星间可见性
//int SatLandKjx[period][Land_Num][Sat_Num];		//星地可见性
//
//
////建链映射关系
//void CreatKeyVal()
//{
//	//卫星和编号
//	for (int i = 1; i <= 30; ++i)
//		craftIndex[StkSensor[i]] = i;
//
//	craftIndex["1"] = 1;
//	craftIndex["2"] = 2;
//}
//
////空格替换逗号
//void Replace(string &s)
//{
//	int n = s.size();
//	for (int i = 0; i < n; ++i)
//	{
//		if (s[i] == ',')
//		{
//			s[i] = ' ';
//		}
//	}
//}
//
////获取可见性
//void GetAccess(string file, bool flag)
//{
//	ifstream fin(file);
//	string line;
//	while (getline(fin, line))
//	{
//		Replace(line);
//		vector<string> res;
//		string result;
//		stringstream input(line);
//		while (input >> result)
//		{
//			res.push_back(result);
//		}
//		double start = stod(res[0]);
//		double stop = stod(res[1]);
//		int forever = stoi(res[2]);
//		int from = craftIndex[res[3]];
//		int to = craftIndex[res[4]];
//		if (forever == 8640)
//			staticlink[from].insert(to);
//		int _start = start;
//		if (start == _start)
//		{
//			while ((_start + 1.5) < stop)
//			{
//				if (flag)
//				{
//					SatLandKjx[_start][from][to] = 1;
//					IS_JNX[_start][to] = true;
//					_start++;
//				}
//				else
//				{
//					SatSatKjx[_start][from][to] = 1;
//					SatSatKjx[_start][to][from] = 1;
//					_start++;
//				}
//			}
//		}
//		else
//		{
//			_start++;
//			while ((_start + 1.5) < stop)
//			{
//				if (flag)
//				{
//					SatLandKjx[_start][from][to] = 1;
//					IS_JNX[_start][to] = true;
//					_start++;
//				}
//				else
//				{
//					SatSatKjx[_start][from][to] = 1;
//					SatSatKjx[_start][to][from] = 1;
//					_start++;
//				}
//			}
//		}
//	}
//	fin.close();
//}
//
//
////按状态划分周期
//void DivideState(const int length)
//{
//	int states = period / length;
//	vector<vector<vector<int>>> SatSatAccess(states, vector<vector<int>>(Sat_Num, vector<int>(Sat_Num, 0)));
//
//	for (int k = 1; k < Sat_Num; k++)
//	{
//		for (int t = 1; t < Sat_Num - 6; t++)
//		{
//			for (int i = 0; i < states; i++)
//			{
//				for (int j = 0; j < length; j++)
//				{
//					if (SatSatKjx[length*i + j][k][t] == 0)
//					{
//						SatSatAccess[i][k][t] = 0;
//						break;
//					}
//					SatSatAccess[i][k][t] = 1;
//				}
//			}
//		}
//	}
//
//	for (int i = 1; i < Sat_Num - 6; i++)
//	{
//		for (int j = 1; j < Sat_Num; j++)
//		{
//			cout << setw(6) << left << SatSatAccess[0][i][j];
//		}
//		cout << endl;
//	}
//}
//
//
////获取所有的可见性
//void GetAllAccess()
//{
//	string meo_meo = "MM.csv";
//	string meo_geo = "GM.csv";
//	string land_meo = "LM.csv";
//	string land_geo = "LG.csv";
//
//	GetAccess(meo_meo, false);
//	GetAccess(meo_geo, false);
//	GetAccess(land_meo, true);
//	GetAccess(land_geo, true);
//
//	DivideState(5);
//	cout << "test " << endl;
//}
//
////星间可见性
//void PrintSSAccess(int snap ,int p[][Sat_Num])
//{
//	for (int i = 1; i < Sat_Num-6; i++)
//	{
//		if (!IS_JNX[snap][i])
//		{
//			cout << setw(5) << left << i;
//			for (int j = 1; j < Sat_Num; j++)
//			{
//				if (p[i][j])
//					cout << setw(5) << left << j;
//			}
//			cout << endl;
//		}	
//	}
//	cout << "-------------------------------" << endl;
//	cout << "-------------------------------" << endl;
//}
//
////星地可见性
//void PrintLSAccess(int snap, int p[][Sat_Num])
//{
//	for (int i = 1; i < Land_Num; i++)
//	{
//		cout << setw(5) << left << i;
//		for (int j = 1; j < Sat_Num; j++)
//		{
//			if (p[i][j])
//				cout << setw(5) << left << j;
//		}
//		cout << endl;
//	}
//	cout << "-------------------------------" << endl;
//	cout << "-------------------------------" << endl;
//}
//
