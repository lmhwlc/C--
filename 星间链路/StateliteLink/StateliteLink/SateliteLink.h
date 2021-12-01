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
����ʱ϶�������Ǽ�·�ɱ�
*/

//������
string	StkSensor[] = { "", "Sensor11","Sensor12" ,"Sensor13" ,"Sensor14" ,"Sensor15","Sensor16","Sensor17","Sensor18",
							"Sensor21","Sensor22" ,"Sensor23" ,"Sensor24" ,"Sensor25","Sensor26","Sensor27","Sensor28",
							"Sensor31","Sensor32" ,"Sensor33" ,"Sensor34" ,"Sensor35","Sensor36","Sensor37","Sensor38",
							"SensorG1","SensorG2", "SensorG3", "SensorG4", "SensorG5", "SensorG6"};

//����վ
string StkGround[] = { "","From Target KASHI","From Target kUNMING","From Target MIYUN","From Target SANYA" };

//������
string SatName[] = { " ","BEIDOU-3 M1","BEIDOU-3 M2","BEIDOU-3 M3","BEIDOU-3 M4","BEIDOU-3 M5","BEIDOU-3 M6","BEIDOU-3 M7","BEIDOU-3 M8","BEIDOU-3 M9","BEIDOU-3 M10",
						 "BEIDOU-3 M11","BEIDOU-3 M12","BEIDOU-3 M13","BEIDOU-3 M14","BEIDOU-3 M15","BEIDOU-3 M16","BEIDOU-3 M17","BEIDOU-3 M18",
						 "BEIDOU 12","BEIDOU 13","BEIDOU 15","BEIDOU 18","BEIDOU 19","BEIDOU 21",
						 "GEO1","GEO2","GEO3","IGSO1","IGSO2","IGSO3" };

//���Ƕ���
Satelite satelite[Sat_Num+6];

//�ǵؿɼ���
int StaGroundKJX[5][Sat_Num];

//�Ǽ�ɼ���
int SatSatKJX[Sat_Num][Sat_Num];

//�Ǽ����
int StaStaDistance[Sat_Num][Sat_Num][Gap+1];

//�Ǽ�·�ɱ�
int Sat_SatLink[Sat_Num][Gap];

//����·�ɱ�
int Sat_LandLink[Sat_Num][Gap];

//���ǵ�ʱ϶��
int Sat_Gap[Sat_Num][Gap] = {0};

//��ž�����
set<int> In_Set;
set<int> Geo_set;
set<int> Meo_set;

//������е�����
vector<int> Sat;

//��ѯ��־λ
int mark1 = 0;
int mark2 = 0;

//��Ź�����
vector<int> DefaultSat;

//���ÿ�����Ƕ�Ӧ�ľ�̬��·����
vector<int> StaticLink[Sat_Num];
//���ÿ�����Ƕ�Ӧ�Ķ�̬��·���ǣ�
vector<int> DynamicLink[Sat_Num];

//���ĳ��ʱ��ÿ�����ǿɼ�������
vector<int> KJSat[Sat_Num+6];
vector<int> SKJSat[Sat_Num];
vector<int> DKJSat[Sat_Num];
queue<int> QKJSat[Sat_Num];

//MEO_GEO�ɼ���Ϣ
int G_Mkjx[GSat][Sat_Num];

//���ǵĴ�����
typedef struct AwaitNum
{
	int index;
	int num;
};
AwaitNum await[Sat_Num];


float jump = 0;//������
int jump1 = 0;  //һ������
int jump2 = 0;  //��������
int jump3 = 0;  //��������
float avgjump = 0.0;//ƽ��ÿ����Ϣ���ݵ�����


//���ǳ�ʼ��
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


//��ȡʱ϶��
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
		cout << "�ļ���ʧ��" << endl;
	infile.close();
}



//
//
////ѡ��ɼ���i��ʱ϶j�о�����С������
//int SelectMinDis(int i, int j)
//{
//	int JW_MinDistance = 100000;
//	int JN_MinDistance = 100000;
//	int JN_min = 0;
//	int JW_min = 0;
//
//	//�����ǰ����û����
//	if (satelite[i].GetSateliteJL() == false)
//	{
//		//��ȡ������i������С�ľ����Ǻ;�����С�ľ�����
//		for (int k = 1; k < Sat_Num; k++)
//		{
//			if (satelite[k].GetSateliteJL() == false && SatSatKJX[i][k])
//			{
//				//������С�ľ�����
//				if (satelite[k].GetSateliteJN_JW())
//				{
//					if (JN_MinDistance > StaStaDistance[i][k][j])
//					{
//						JN_MinDistance = StaStaDistance[i][k][j];
//						JN_min = k;
//					}
//				}
//				//������С�ľ�����
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
//	//�����ǰ����i�Ǿ����ǣ����������������С�ľ����ǽ���,�����������С�ľ����ǽ���
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
////��ʼ�����ǽ���״̬
//void InitilaSatJL()
//{
//	for (int j = 1; j < Sat_Num; j++)
//		satelite[j].SetSateliteJL(false);
//}
//
//
//��ȡ�Ǽ������Ϣ
//void GetSatSatDis()
//{
//	ifstream fin("distance2.csv");
//	string line;
//	int index = 1;
//	int index1 = 0;
//	int index2 = 0;
//	while (getline(fin, line))
//	{
//		��λ��ǰ����
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

//���1~5�Ź�����
void RandomSat()
{
	for (int i = 1; i < Sat_Num; i++)
	{
		Sat.push_back(i);
	}
	random_shuffle(Sat.begin(), Sat.end());

	cout << "���ϵ�����Ϊ��" << endl;
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


//��ȡ����վ�������������ǵı��
int GetIndex(string a, string* b)
{
	for (int i = 1; i < Sat_Num+6; i++)
		if (strcmp(a.c_str(), b[i].c_str()) == 0)
			return i;
	return 0;
}


//��ȡÿ���ǵľ�̬��·����
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

//��ȡ���Ƕ�Ӧ�Ķ�̬����
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

//�ж�ĳ�������Ƿ��ǵ�ǰ���ǵľ�̬��·����
bool JudgeStaticSat(int i, int j)
{
	for (int k = 0; k < StaticLink[i].size(); k++)
	{
		if (j == StaticLink[i][k])
			return true;
	}
	return false;
}


//��ȡ���������Լ��ǵؿɼ���
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


//��ȡMEO�Ǽ�ɼ�����Ϣ
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


//��ȡMEO��GEO,IGSO֮��Ŀɼ�����Ϣ
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


//���������
//��ӡʱ϶��
void PrintGap(int p[Sat_Num][Gap])
{
	cout << "�Ǽ���·�����£�" << endl;
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


//��ӡ��ǰ�ľ�����
void PrintJNX()
{
	cout << "������Ϊ��" << endl;
	for (auto i : In_Set)
		cout << i << "	";
	cout << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//�ж�ĳ��ʱ϶����i�Ƿ���
bool SatJL(int i,int time)
{
	for (int j = 1; j < Sat_Num; j++)
	{
		if ( i == Sat_Gap[j][time])
			return true;
	}
	return false;
}


//��ʼ��ʱ϶��
void InitialGap()
{
	for (int i = 0; i < Sat_Num; i++)
		for (int j = 0; j < Gap; j++)
			Sat_Gap[i][j] = 0;
}


//��̬�����Ƿ�����
bool AllocatStaticSat(int from,int sat)
{
	for (int i = 1; i < Gap; i++)
		if (sat == Sat_Gap[from][i])
			return true;
	return false;
}


//Ѱ�����ǵĿ��ÿ���ʱ϶
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

//ɾ���Ѿ������ľ�̬��·
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

//���ҿɼ��ǵ�˳��
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
		cout << "����"<<i<<": "<<JNXSource[i][0] << "	" << JNXSource[i][1] << "	" << JNXSource[i][0] + JNXSource[i][1] << endl;;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


int SatSource[25][21];
//��ʼ��ÿ�������ǿɷ���ľ�������Դ
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
		cout << "����" << setw(5) << left <<i << ":" ;
		for (int j = 1; j < Gap; j++)
		{
			cout << setw(5) << left << SatSource[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}

//���Ҿ�������Դ���ľ�����
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

//ѭ������ÿ�������ǵĿɼ���
int ResearchKJX(int sat,int mark,bool flag)
{
	int size = KJSat[sat].size();

	//�������뾳���ǽ���
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
	//�������뾳���ǽ���
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


//������Դ����С��δ����������
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

//������Դ����С��δ���������ǣ���һʱ϶Ϊ����-������·��
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

//�������ǵ���Դ�Ƿ�ʹ��
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

//ÿ�η�����Դ��������ǵ���Դ��
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


//����̬��·���䵽������ͬʱ϶��
void AllocateStaLink()
{
	bool flag = false;
	vector<int> JW_JW;
	vector<int> temp;
	for (int i = 1; i < 9; i++)
	{
		//��һ��ʱ϶����
		if (i == 1)
		{
			for (int j = 1; j < 13; j++)
			{
				int min = ResearchMinSource(i);
				//int min = ResearchMaxJNX();
				flag = false;
				//���Ƚ��о������뾳���ǽ���
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
				//�����ھ������뾳���ǵ���·����о������뾳���ǵĽ���
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
		//ʣ�µ�ʱ϶���������Ƚ�����һʱ϶�еľ������뾳���ǵ���·
		else
		{
			int start = 0;
			while (JW_JW.size())
			{
				int min = ResearchMinSource(i, JW_JW);
				start++;
				//���Ƚ��о������뾳���ǽ���
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

//��ʣ�µľ�����-��������·���з���
for (int j = start; j < 13; j++)
{
	int min = ResearchMinSource(i);
	//int min = ResearchMaxJNX();
	//���Ƚ��о������뾳���ǽ���
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
	//�����ھ������뾳���ǵ���·����о������뾳���ǵĽ���
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

////����̬��·���䵽������ͬʱ϶��
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

//Ϊ���о������Ƿ��侳���ǻ��߾�����
void AllocateJWX()
{
	bool flag = true;
	vector<int> JW_JW;

	//��һ��ʱ϶����
	for (int j = 1; j < Sat_Num; j++)
	{
		if (satelite[j].GetSateliteJNX() == false&&satelite[j].GetSateliteJL()==false)
		{
			int mark = SatSource[j][2];
			int size = KJSat[j].size();

			//���Ƚ��о������뾳���ǽ���
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
				//û�пɽ����ľ�����
				if (mark > size * 2)
				{
					flag = false;
					mark = SatSource[j][2];
					break;
				}
			}

			//�����ھ������뾳���ǵ���·����о������뾳���ǵĽ���
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
					//����δ�����ľ�����
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

	//��ʣ��ʱ϶���ǽ��н���
	for (int i = 2; i < Gap; i++)
	{
		//���ȶ��ϸ�ʱ϶��δ�����;��⡪��������������
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
					//cout << "�޷����������" << endl;
					
					break;
				}
			}
		}

		//��ʣ�µľ����ǽ���
		for (int j = 1; j < Sat_Num; j++)
		{
			if (satelite[j].GetSateliteJNX() == false && satelite[j].GetSateliteJL() == false)
			{
				int mark = SatSource[j][2];
				int size = KJSat[j].size();

				//���Ƚ��о������뾳���ǽ���
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
					//û�пɽ����ľ�����
					if (mark > size * 2)
					{
						flag = false;
						mark = SatSource[j][2];
						break;
					}
				}

				//�����ھ������뾳���ǵ���·����о������뾳���ǵĽ���
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
						//����δ�����ľ�����
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

//�������ǿɼ��Խ����ɼ�����·��Ϊ����״̬
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


//����MEO�������뾳����֮�����·
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


//��ʼ��������20��ʱ϶�Ľ���˳��
void CreatLink()
{
	//ĳ�����ǿɼ��ľ����Ǻ;�����
	vector<int> KJ_JNX;

	//�����Ǻ;����ǽ���
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


//ѡ����GEO_IGSO�뾳��MEO֮�����·
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


//������ʱ϶�����������뾳����֮�����·
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


//ͳ��ÿ�����Ƕ�Ӧ�Ŀ���ʱ϶
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


//�ж��������Ƿ���ڿ���ʱ϶
bool JudgeAwait(int i)
{
	for (int gap = 0; gap < Gap; gap++)
	{
		if (Sat_Gap[i][gap] == 0)
			return true;
	}
	return false;
}


//��ӡ����ʱ϶
void printawait()
{
	for (int i = 1; i < Sat_Num; i++)
		cout << await[i].index << " " << await[i].num << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//�Ż���·
void UpgradeLink()
{
	//����ÿ�����ǵĿ���ʱ϶
	MarkAwaitNum();

	//�Ӵ�С����
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


	//����߹����ǽ������⡪�������Ǽ���·
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
	//��ʣ�µľ����Ƕ�Ӧ�Ŀ���ʱ϶�����뾳���ǽ���
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

//����ʱ϶��˳��
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
//����ʱ϶������·�ɱ�
bool CreatRount()
{
	//����һ��֡��ǰ18��ʱ϶��·��
	for (int i = 1; i < Gap - 2; i++)
	{
		for (int j = 1; j < Sat_Num; j++)
		{
			if (satelite[j].GetSatNormal())
			{
				int index1 = Sat_Gap[j][i];

				//��ǰ����Ϊ������
				if (satelite[j].GetSateliteJNX())
				{
					//�������뾳���ǽ���
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

				//��ǰ����Ϊ��������iʱ϶�뾳���ǽ���
				if (index1 && satelite[index1].GetSateliteJNX())
				{
					Sat_SatLink[j][i] = index1;
					if (index1 < Sat_Num)
						Sat_SatLink[index1][i] = j;

					continue;
				}
				//��ǰ����Ϊ��������i+1ʱ϶�뾳���ǽ���
				if (index2&&satelite[index2].GetSateliteJNX())
				{
					Sat_SatLink[j][i+1] = index2;
					if (index1 < Sat_Num)
						Sat_SatLink[index2][i+1] = j;

					continue;
				}
				//��ǰ����Ϊ��������i+2ʱ϶�뾳���ǽ���
				if (index3&&satelite[index3].GetSateliteJNX())
				{
					Sat_SatLink[j][i + 2] = index2;
					if (index1 < Sat_Num)
						Sat_SatLink[index2][i + 2] = j;

					continue;
				}
				//index1,index2,index3�����Ǿ����ǣ��򾭹���ת�ǽ������ݻش�
				if (!satelite[index1].GetSateliteJNX() && !satelite[index2].GetSateliteJNX() && !satelite[index3].GetSateliteJNX())
				{
					//iʱ϶���Ӿ�����(index1)��Ϊ��ת��
					if (index1)
					{
						//��i+1ʱ϶�뾳���ǽ���
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

						//��i+2ʱ϶�뾳���ǽ���
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

						//ͨ��index4�ٴ���ת����ת��index7���¸�ʱ϶��i+2��
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

					//i+1ʱ϶���Ӿ�����(index2)��Ϊ��ת��
					if (index2)
					{
						//��i+2ʱ϶�뾳���ǽ���
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

					//�������޷���10s�ڽ����ݻش�
					cout << "��ʱ϶" << i << "��ʼʱ������" << j << "�޷���10s��������ݻش�" << endl;
					break;
				}
			}

		}
	}
	return true;
}


//��������������
void CalJump()
{
	//ǰ18��ʱ϶���������
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


//��ӡ�ǵؿɼ�����Ϣ
void PrintStaGroundAcesss()
{
	cout << "�ǵؿɼ���Ϊ��" << endl;
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


//��ӡMEO�Ǽ�ɼ�����Ϣ
void PrintStaStaAccess()
{
	cout << "ÿ�����Ƕ�Ӧ�Ķ�̬��·����Ϊ��" << endl;
	for (int i = 1; i < Sat_Num; i++)
	{
		cout << "����" << i << "��Ӧ�ľ�̬��·����Ϊ��" << endl;
		for (int j = 0; j < DKJSat[i].size(); j++)
		{
			cout << setw(5) << left << DKJSat[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//��ӡGEO_IGSO��MEO֮��Ŀɼ���
void PrintG_MAcess()
{
	cout << "GEO_IGSO��MEO֮��Ŀɼ��ԣ�" << endl;
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


//��ӡ�Ǽ������Ϣ
void PrintSatSatDist()
{
	for (int k = 1; k < 3; k++)
	{
		cout << "---------------------------��" << k << "ʱ϶������Ϣ" << "---------------------------" << endl;
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
	

//��ӡ·�ɱ�
void PrintRount()
{
	//·�ɱ�
	cout << "·��������£�" << endl;
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


//��ӡÿ�����Ƕ�Ӧ�ľ�̬��·����
void PrintStaticSat()
{
	cout << "ÿ�����Ƕ�Ӧ�İ˸���̬��·����Ϊ��" << endl;
	for (int i = 1; i < Sat_Num; i++)
	{
		cout << "����" << i << "��Ӧ�ľ�̬��·����Ϊ��"<<endl;
		for (int j = 0; j < StaticLink[i].size(); j++)
			cout << StaticLink[i][j] << "	";
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}


//������е��������
void PrintJump()
{
	cout << "���е�����������£�" << endl;
	cout << "һ�������" << jump1 << "ռ�ȣ�" << jump1 / jump << endl;
	cout << "���������" << jump2 << "ռ�ȣ�" << jump2 / jump << endl;
	cout << "���������" << jump3 << "ռ�ȣ�" << jump3 / jump << endl;
	cout << "ƽ������Ϊ��" << avgjump << endl;
}