#include<iostream>
#include"AccessDate.h"
#include<fstream>
#include<string>
#include"LinkStrategy.h"
using namespace std;

void fun()
{
	//GetSateliteInfo();
//ofstream out("route.txt");
//if (out.is_open())
//{
//	for (int i = 0; i < 20; i++)
//	{
//		ClassifySat(i);
//		for (int i = 0; i < Sat_Num; i++)
//			Sat_Gap[i].resize(_Gap);
//		for (int i = 1; i < Sat_Num - 6; i++)
//			route[i].resize(Gap);
//	
//		int maxJump;
//		double avgJump;
//		PrintLSAccess(i, SatLandKjx[i]);
//		PrintSSAccess(i, SatSatKjx[i]);
//		PrintSat(JNX);
//		PrintSat(JWX);
//		PrintClassify(JWX, ClassifyJNX, ClassifyJWX);
//		Allocate(JWX, ClassifyJNX, ClassifyJWX);

//		//CreatLink(i, Sat_Gap);

//		PrintItem(Sat_Gap);
//		GetCorrespondInfo(Sat_Gap, i*20);
//		GetAllRoute(Sat_Gap, i, route);
//		//PrintItem(Sat_Gap);
//		GetJump(maxJump, avgJump, route);
//		cout << "周期数： " << i << "平均跳数为：	" << avgJump << " 最大跳数为：" << maxJump << endl;
//	/*	out << i << "	" << avgJump << "	" << maxJump << endl;
//		for (int j = 0,length = JWX.size(); j < length; j++)
//		{
//			int from = JWX[j];
//			out << setw(5) << left << from;
//			for (int k = 1; k < Gap; k++)
//			{
//				out << setw(5) << left << Sat_Gap[from][k];
//			}
//			out << endl;
//		}*/
//	
//		//out << endl << endl;
//		for (int i = 0; i < Sat_Num; i++)
//		{
//			vector<int>().swap(Sat_Gap[i]);
//			vector<int>().swap(ClassifyJNX[i]);
//			vector<int>().swap(ClassifyJWX[i]);
//		}
//		for (int i = 0; i < Sat_Num - 6; i++)
//			vector<vector<int>>().swap(route[i]);
//		vector<int>().swap(JWX);
//		vector<int>().swap(JNX);
//	}
//}
//else
//{
//	cout << "文件打开失败";
//}

//for (int i = 0, length = linkName.size(); i < length; i++)
//{
//	out << linkName[i] << endl;
//	for (int j = 0, size = working[i].size(); j < size; j++)
//	{
//		out << working[i][j]<<"	";
//		if ((j + 1) % 20 == 0)
//			out << endl;
//	}
//	out << endl << endl;
//}
//
//out.close();
//cout << "文件写入成功！" << endl;
//getchar();
//return 0;
}


int main()
{
	//GetSatLandInfo();
	//GetALlAns();
	vector<int> JNX;
	vector<vector<int>> VecSatSat(SatNum+1, vector<int>(SatNum + 1));
	GetSatToSat(VecSatSat, JNX);
	cout << "hello world !" << endl;
	cout << endl;
	cout << endl;
}