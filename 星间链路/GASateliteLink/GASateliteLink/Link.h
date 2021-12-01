#pragma once
#include<iostream>
#include"SateliteInfo.h"
#include <ctime>
#include<thread>
using namespace std;

const int Gap = 21;			//һ�����ڵ�ʱ϶��
vector<int> Sat;			//������е�����
vector<int> JWX;			//������о�����
vector<int> JNX;			//������о�����
const int link_num = 10;	//��·����Լ��


void PrintGap(const vector<vector<int>> &Sat_Gap);

//��ȡ�������ԺͿɼ�����Ϣ
void GetSateliteInfo()
{
	GetAllAccess();
}

//�����Ƿ���
void ClassifySat(int snap)
{
	for (int i = 1; i < Sat_Num - 6; i++)
	{
		if (!IS_JNX[snap][i])
			JWX.push_back(i);	
	}

	for (int i = 0; i < Sat_Num; i++)
	{
		if (IS_JNX[snap][i])
			JNX.push_back(i);
	}

	for (int i = 1; i < Sat_Num; i++)
		if(!(!IS_JNX[snap][i]&&i>24))
			Sat.push_back(i);
}

//��ӡ����
void PrintItem(const vector<vector<int>> p)
{
	for (int j = 0; j < JWX.size(); j++)
	{
		int from = JWX[j];
		cout << setw(5) << left << from;
		for (int k = 1; k < Gap; k++)
		{
			cout << setw(5) << left << p[from][k];
		}
		cout << endl;
	}
	cout << endl << endl;
}

//������ʾ����ǵĿɼ�����˳��
void RandSat(vector<int> &jwx)
{
	for (int i = 0; i < jwx.size(); i++)
	{
		int num = rand() % (jwx.size() - 1);
		swap(jwx[i],jwx[num]);
	}
}

//��ֵɾ��vector���ĳ��Ԫ��
bool Remove(int tmp, vector<int> &vec)
{
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (*it == tmp)
		{
			it = vec.erase(it);
			return true;
		}
	}
	return false;
}

//�жϾ������Ƿ���ĳ�����ǽ�����
bool IsLink(int gap, int from, int to, const vector<vector<int>> &vec)
{
	for (int i = 1; i < gap; i++)
	{
		if (vec[from][i] == to)
			return true;
	}
	return false;
}

//ÿ���������ǽ�������Լ��
int IsLinkNum(const vector<vector<int>> &vec,int jwx)
{
	set<int> tmp;
	for (int i = 1; i < Gap; i++)
		if (vec[jwx][i] != 0)
			tmp.insert(vec[jwx][i]);

	return tmp.size();
}

//��ӡ���ǵ�˳��
void PrintSat(const vector<int> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << "	 ";
	cout << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}

//ÿ��ʱ϶���������ǵĽ���˳����ң���֤���ȷ�����·
void AllocateLink(vector<vector<int>> &Sat_Gap,int snap)
{
	for (int i = 1; i < Gap; i++)
	{
		vector<int> tmp1(JWX);
		vector<int> tmp2(Sat);
		RandSat(tmp1);
		RandSat(tmp2);
		bool flag = false;
		while (!tmp1.empty())
		{
			int from = tmp1[0];
			for (int k = 0; k < tmp2.size(); k++)
			{
				int to = tmp2[k];
				if (SatSatKjx[snap][from][to] == 1)
				{
					//�Ƚ���δ����������
					if (!IsLink(i, from, to, Sat_Gap) && !IsLink(i, to, from, Sat_Gap))
					{
						Sat_Gap[from][i] = to;
						Sat_Gap[to][i] = from;
						Remove(from, tmp1);
						Remove(to, tmp1);
						Remove(to, tmp2);
						Remove(from, tmp2);
						break;
					}
					//�������Ƕ����������㽨��������Լ����ʼ�뽨���������ǽ���
					if (IsLinkNum(Sat_Gap, from) && IsLinkNum(Sat_Gap, to))
					{
						Sat_Gap[from][i] = to;
						Sat_Gap[to][i] = from;
						Remove(from, tmp1);
						Remove(to, tmp1);
						Remove(to, tmp2);
						Remove(from, tmp2);
						break;
					}
				}
			}
			Remove(from, tmp1);
		}
	}
}

//������·��
void GetRoute(int from,int _gap,const vector<vector<int>> &Sat_Gap,vector<int> &tmp,int snap)
{
	vector<vector<int>> tp;
	vector<int> node;
	node.push_back(from);
	for (int i = _gap; i < Gap; i++)
	{
		if (tp.empty())
		{
			vector<int> vec1;
			vec1.push_back(from);
			int to = Sat_Gap[from][i];
			if (IS_JNX[snap][to])
			{
				vec1.push_back(to);
				for (int t = 0; t < vec1.size(); t++)
				{
					tmp.push_back(vec1[t]);
				}
				return;
			}
			vec1.push_back(0);
			tp.push_back(vec1);
			vector<int> vec2;
			vec2.push_back(from);
			vec2.push_back(to);
			tp.push_back(vec2);
			if(to!=0)
				node.push_back(to);
			if (i == 20)
			{
				for (int t = 0; t < vec1.size(); t++)
				{
					tmp.push_back(vec1[t]);
				}
				return;
			}
		}
		else
		{
			int length = node.size();
			for (int j = 0; j < length; j++)
			{
				int index = node[j];
				int to = Sat_Gap[index][i];
				if (IS_JNX[snap][to])
				{
					tp[j].push_back(to);
					for (int t = 0; t < tp[j].size(); t++)
					{
						tmp.push_back(tp[j][t]);
					}
					return;
				}
				vector<int> vec(tp[j]);
				tp[j].push_back(0);
				vec.push_back(to);
				tp.push_back(vec);
				if (to != 0)
					node.push_back(to);
			}
			if (i == 20)
			{
				for (int t = 0; t < tp[0].size(); t++)
				{
					tmp.push_back(tp[0][t]);
				}
				return;
			}
		}
	}
}

//���һ�������ڵĴ���ʱ��
//void GetAllRoute(const vector<vector<int>> &Sat_Gap,int snap, vector<vector<vector<int>>> &route)
//{
//	for (int i = 1; i < Gap; i++)
//	{
//		for (int j = 0; j < JWX.size(); j++)
//		{
//			int from = JWX[j];
//			GetRoute(from, i, Sat_Gap, route[from][i], snap);
//		}
//	}
//}

//���������뾳���ǵ���·���һ����Ϊ������
void CreatRoute(vector<vector<int>> &Sat_Gap,int snap)
{
	for (int i = 0; i < JWX.size(); i++)
	{
		int from = JWX[i];
		for (int j = 1; j < Gap; j++)
		{
			int to1 = Sat_Gap[from][j];
			if (to1 > 0)
			{
				int to2 = Sat_Gap[to1][j];
				if (to2 > 0 && !IS_JNX[snap][to1])
				{
					int index = rand() % 2;
					if (index)
						Sat_Gap[from][j] = -to1;
					else
						Sat_Gap[to1][j] = -to2;
				}
			}	
		}
	}
}

void CreatRoute(vector<vector<int>> &Sat_Gap, int snap, int _gap)
{
	for (int i = 0; i < JWX.size(); i++)
	{
		int from = JWX[i];
		int to1 = Sat_Gap[from][_gap];
		if (to1 > 0)
		{
			int to2 = Sat_Gap[to1][_gap];
			if (to2 > 0 && !IS_JNX[snap][to1])
			{
				int index = rand() % 2;
				if (index)
					Sat_Gap[from][_gap] = -to1;
				else
					Sat_Gap[to1][_gap] = -to2;
			}
		}
	}
}

void GetRoute(const vector<vector<int>> &Sat_Gap, int from, int _gap,vector<int> &tmp,int snap)
{
	tmp.push_back(from);
	for (int i = _gap; i < Gap; i++)
	{
		int to = Sat_Gap[from][i];
		if (to > 0)
		{
			if (IS_JNX[snap][to])
			{
				tmp.push_back(to);
				return;
			}
			else
			{
				tmp.push_back(to);
				from = to;
			}
		}
		else
		{
			tmp.push_back(0);
		}
	}
}

//��������Ϣ�ش�������·��
void GetAllRoute(const vector<vector<int>> &Sat_Gap,int snap,vector<vector<vector<int>>> &route)
{
	for (int i = 0; i < JWX.size(); i++)
	{
		int from = JWX[i];
		for (int j = 1; j < Gap; j++)
		{
			GetRoute(Sat_Gap, from, j, route[from][j], snap);
		}
	}
}

//���㾳�������ݻش������������ƽ������
void GetJump(int &maxJump , double &avgJump, const vector<vector<vector<int>>> &route)
{
	int max = 0;
	double sum = 0;
	for (int i = 0; i < JWX.size(); i++)
	{
		for (int j = 1; j < Gap; j++)
		{
			int from = JWX[i];
			sum += route[from][j].size() - 1;
			if (max < route[from][j].size())
			{
				max = route[from][j].size();
				maxJump = max - 1;
			}
		}
	}
	avgJump = sum / (JWX.size()*20);
}

//��ӡʱ϶��
void PrintGap(const vector<vector<int>> &Sat_Gap)
{
	for (int i = 1; i < Sat_Num - 6; i++)
	{
		cout << setw(5) << left << i;
		for (int j = 1; j < Gap; j++)
		{
			cout << setw(5) << left << Sat_Gap[i][j];
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}