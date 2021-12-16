#pragma once
#include"AccessDate.h"
#include<fstream>
#include<iostream>
using namespace std;

//统计每个卫星的可见卫星数量（境内星，境外星）
void GetAccessSatNum(vector<vector<bool>>& VecSatToSat, vector<bool>& VecIsJnx)
{
	int cnt1 = 0, cnt2 = 0;
	vector<vector<int>> AccessSatNum(SatNum + 1);
	for (int i = 1; i <= SatNum - 6; i++)
	{
		if (VecIsJnx[i] == true)
		{
			for (int j = 1; j <= SatNum; j++)
			{
				if (VecSatToSat[i][j] == true)
				{
					VecIsJnx[j] == false ? cnt1++ : cnt2++;
				}
			}
		}
		else
		{
			for (int j = 1; j <= SatNum; j++)
			{
				if (VecSatToSat[i][j] == true)
				{
					VecIsJnx[j] == true ? cnt1++ : cnt2++;
				}
			}
		}
		AccessSatNum[i].push_back(cnt1);
		AccessSatNum[i].push_back(cnt2);
		cnt1 = 0;
		cnt2 = 0;
	}
}

//获取可见性矩阵
void GetSatToSat(vector<vector<int>>& VecSatToSat, vector<int>& JNX)
{
	ifstream infile;
	string filename = "E:\\Code\\git\\C--\\星间链路\\卫星可见性矩阵\\0.txt";
	string filename1 = "E:\\Code\\git\\C--\\星间链路\\境内星\\0.txt";
	infile.open(filename);
	for (int i = 1; i <= SatNum; i++)
	{
		for (int j = 1; j <= SatNum; j++)
		{
			infile >> VecSatToSat[i][j];
		}
	}
	infile.close();
	infile.open(filename1);
	int item;
	while (infile >> item)
	{
		JNX.push_back(item);
	}
}