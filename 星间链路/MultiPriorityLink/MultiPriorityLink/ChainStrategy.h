//#pragma once
//#include"Info.h"
//using namespace std;
//#include <algorithm>
//#include"Info.h"
//#include<vector>
//#include<string>
//#include<map>
//const int Gap = 21;			//һ�����ڵ�ʱ϶��
//const int _Gap = 31;		//��չ������ڵ�ʱ϶��
//vector<int> Sat;			//������е�����
//vector<int> JWX;			//������о�����
//vector<int> JNX;			//������о�����
//const int link_num = 10;	//��·����Լ��
//vector<vector<int>> Sat_Gap(Sat_Num);	//ʱ϶��
//vector<vector<int>> sat_num;
//vector<vector<vector<int>>> route(Sat_Num);		//һ�����ڵ�·�ɼ���
//vector<vector<int>> working(720);				//������·��״̬
//vector<vector<int>> ClassifyJNX(Sat_Num);		//ÿ�����ǿɼ��ľ�����
//vector<vector<int>> ClassifyJWX(Sat_Num);		//ÿ�����ǿɼ��ľ�����
//vector<string> linkName;
////map<string, vector<bool>> working;
//vector<bool> pr(Sat_Num, false);
//
////��ֵɾ��vector���ĳ��Ԫ��
//bool Remove(int tmp, vector<int> &vec)
//{
//	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
//	{
//		if (*it == tmp)
//		{
//			it = vec.erase(it);
//			return true;
//		}
//	}
//	return false;
//}
//
////��ÿ�������ǵĿɼ����Ƿ������ȷ��侳���ǣ������Ǳ�������򽵵����������ȼ����޿ɽ����������뾳���ǽ���
//void ClassifyKJX(int snap,const vector<int> &jwx)
//{
//	int size = jwx.size();
//	for (int i = 0; i < size; ++i)
//	{
//		int from = jwx[i];
//		for (int j = 1; j < Sat_Num; ++j)
//		{
//			if (SatSatKjx[from][j])
//			{
//				if (IS_JNX[snap][j])
//				{
//					ClassifyJNX[from].push_back(j);
//				}
//				else
//				{
//					ClassifyJWX[from].push_back(j);
//				}
//			}
//		}
//	}
//}
//
//bool JudgeAllocate(int gap,int sat)
//{
//	for (int i = 1; i < Sat_Num; ++i)
//	{
//		if(sat == Sat_Gap[i][gap])
//			return false;
//	}
//	return true;
//}
//void Allocate(const vector<int> &jwx, const vector<vector<int>>& classifyJnx, const vector<vector<int>>& classfyJwx)
//{
//	for (int i = 0; i < jwx.size(); ++i)
//	{
//		int from = jwx[i];
//		int gap = 1;
//		while (!ClassifyJNX[from].empty())
//		{
//			for (int j = 0; j < ClassifyJNX[from].size();)
//			{
//				int to = ClassifyJNX[from][j];
//				if (JudgeAllocate(gap, to))
//				{
//					Sat_Gap[from][gap] = to;
//					Sat_Gap[to][gap] = from;
//					++gap;
//					Remove(to, ClassifyJNX[from]);
//					j = 0;
//					continue;
//				}
//				++j;
//			}
//			++gap;
//		}
//	}
//}
////��ȡ�������ԺͿɼ�����Ϣ
//void GetSateliteInfo()
//{
//	CreatKeyVal();
//
//	//��ʼ��ʱ϶��
//	for (int i = 0; i < Sat_Num; i++)
//		Sat_Gap[i].resize(_Gap);
//
//	//��ʼ��·�ɱ�
//	for (int i = 1; i < Sat_Num - 6; i++)
//		route[i].resize(Gap);
//	GetAllAccess();
//
//
//	//��ʼ����·��
//	for (int i = 1; i < Sat_Num-6; i++)
//	{
//		for (int j = 1 ; j < Sat_Num; j++)
//		{
//			string from =to_string(i);
//			string to = to_string(j);
//			string s(from);
//			s.append("-").append(to);
//			linkName.push_back(s);
//		}
//	}
//}
//
////��ӡ���ǵ�˳��
//void PrintSat(const vector<int> &vec)
//{
//	for (int i = 0; i < vec.size(); i++)
//		cout << vec[i] << "	 ";
//	cout << endl;
//	cout << "-------------------------------------------------------------------------------------" << endl;
//	cout << "-------------------------------------------------------------------------------------" << endl;
//}
//
//void PrintClassify(const vector<int> &jwx,const vector<vector<int>>& classifyJnx,const vector<vector<int>>& classfyJwx)
//{
//	for (int i = 0; i < jwx.size(); ++i)
//	{
//		int from = jwx[i];
//		cout << setw(5) << from;
//		for (int j = 0; j < classifyJnx[from].size(); ++j)
//		{
//			cout<<setw(5) << left << classifyJnx[from][j];
//		}
//		cout << "###	";
//		for (int j = 0; j < classfyJwx[from].size(); ++j)
//		{
//			cout << setw(5) << left << classfyJwx[from][j];
//		}
//		cout << endl;
//	}
//	cout << "-------------------------------------------------------------------------------------" << endl;
//	cout << "-------------------------------------------------------------------------------------" << endl;
//}
////�����Ƿ���
//void ClassifySat(int snap)
//{
//	for (int i = 1; i < Sat_Num - 6; i++)
//	{
//		if (!IS_JNX[snap][i])
//		{
//			JWX.push_back(i);
//			for (int j = 1; j < Sat_Num; ++j)
//			{
//				if (SatSatKjx[snap][i][j])
//				{
//					if (IS_JNX[snap][j])
//					{
//						ClassifyJNX[i].push_back(j);
//					}
//					else
//					{
//						ClassifyJWX[i].push_back(j);
//					}
//				}
//			}
//		}	
//	}
//
//	for (int i = 0; i < Sat_Num; i++)
//
//	{
//		if (IS_JNX[snap][i])
//			JNX.push_back(i);
//	}
//
//	for (int i = 1; i < Sat_Num; i++)
//		if (!(!IS_JNX[snap][i] && i > 24))
//			Sat.push_back(i);
//}
//
////��ӡ����
//void PrintItem(const vector<vector<int>> p)
//{
//	for (int j = 0; j < JWX.size(); j++)
//	{
//		int from = JWX[j];
//		cout << setw(5) << left << from;
//		for (int k = 1; k < Gap; k++)
//		{
//			cout << setw(5) << left << p[from][k];
//		}
//		cout << endl;
//	}
//	cout << endl << endl;
//}
//
////������ʾ����ǵĿɼ�����˳��
//void RandSat(vector<int> &jwx)
//{
//	for (int i = 0; i < jwx.size(); i++)
//	{
//		int num = rand() % (jwx.size() - 1);
//		swap(jwx[i], jwx[num]);
//	}
//}
//
//
////����ÿ�������ǵĿɼ�������
//void CalSatNum(int snap)
//{
//	int count = 0;
//	for (int i = 0; i < JWX.size(); i++)
//	{
//		vector<int> tmp;
//		int from = JWX[i];
//		tmp.push_back(from);
//		for (int i = 1; i < Sat_Num; i++)
//		{
//			int to = SatSatKjx[snap][from][i];
//			if (to== 1)
//				count++;
//		}
//		tmp.push_back(count);
//		sat_num.push_back(tmp);
//		count = 0;
//	}
//}
//
////�Զ����������
//bool compare(vector<int> a, vector<int> b)
//{
//	return a[1] < b[1];
//}
//
////���ȼ����ã�Ϊ������Ѱ�Һ��ʵľ�������Ϊ������ת��
///*
//	1.��ǰʱ϶����һ��ʱ϶δ�������뾳���ǽ����ľ����Ǵ���������ȼ�
//	2.���о����ǰ���ɼ������ǵ������������ȼ�������Խ�٣����ȼ�Խ��
//	3.�������ø����������һ���������뾳���ǽ����Ի�ȡ���õĹ۲����ݼ���PDOP,��ĳ��ʱ϶���������������ȼ��������һ��
//	4.��ǰ��������Դ���꣬��������Ϊ����ľ����ǣ�����о������뾳���ǽ���
//	5.ÿ�ζ�������ʾ�����
//*/
//
//
////δ�뾳���ǽ�������δ�����ľ��������Ƚ���
//void CreatLink(vector<int> &vec1, vector<int> &vec2, vector<vector<int>> &Sat_Gap, int snap,int pos,vector<int> &vec)
//{
//	bool flag = false;
//	while (!vec1.empty())
//	{
//		flag = false;
//		int from = vec1[0];
//		for (int k = 0; k < vec2.size(); k++)
//		{
//			int to = vec2[k];
//			if (SatSatKjx[snap][from][to] == 1)
//			{
//				Sat_Gap[from][pos] = to;
//				Sat_Gap[to][pos] = from;
//				Remove(from, vec1);
//				Remove(to, vec2);
//				Remove(from, vec);
//				flag = true;
//				break;
//			}
//		}
//		if (flag == false)
//		{
//			for (int i = 0; i < vec.size(); i++)
//			{
//				int to = vec[i];
//				if (SatLandKjx[snap][from][to] == 1)
//				{
//
//					Sat_Gap[from][pos] = to;
//					Sat_Gap[to][pos] = from;
//					Remove(from, vec1);
//					Remove(to, vec);
//					break;
//				}
//			}
//			Remove(from, vec1);
//			Remove(from, vec);
//		}
//	}
//}
//
////��������������С��Դ�ľ����ǽ���
//void AllocateLink(vector<vector<int>> &Sat_Gap, int snap, vector<int> &vec1, vector<int> &vec2,vector<int> &priorSat,int i)
//{
//	bool flag = false;
//	while (!vec1.empty())
//	{
//		flag = false;
//		int from = vec1[0];
//		for (int k = 0; k < vec2.size(); k++)
//		{
//			int to = vec2[k];
//			if (SatSatKjx[snap][from][to] == 1)
//			{
//				Sat_Gap[from][i] = to;
//				Sat_Gap[to][i] = from;
//				Remove(from, vec1);
//				Remove(to, vec2);
//				flag = true;
//				break;
//			}
//		}
//
//		//�����ǰ�������Ҳ������佨���ľ����ǣ������뾳���ǽ���
//		if (flag == false)
//		{
//			priorSat.push_back(from);
//			for (int k = 1, length = vec1.size(); k < length; k++)
//			{
//				int to = vec1[k];
//				if (SatSatKjx[snap][from][to] == 1)
//				{
//					Sat_Gap[from][i] = to;
//					Sat_Gap[to][i] = from;
//					Remove(from, vec1);
//					Remove(to, vec1);
//					priorSat.push_back(to);
//					int index = rand() % 2;
//					if (index)
//						Sat_Gap[from][i] = -to;
//					else
//						Sat_Gap[to][i] = -from;
//					break;
//				}
//			}
//			Remove(from, vec1);
//		}
//	}
//}
//
////�������Ǵ���˳��,Ȼ�����η������ǣ�ѭ��һ������
//void CreatLink(int snap,vector<vector<int>> &Sat_Gap)
//{
//	CalSatNum(snap);
//	vector<int> priorSat;
//	sort(sat_num.begin(), sat_num.end(), compare);
//	vector<int> vec;
//	for (int i = 0, num = JWX.size(); i < num; i++)
//		vec.push_back(sat_num[i][0]);
//
//	vector<vector<int>>().swap(sat_num);
//
//	for (int i = 1; i < _Gap; i++)
//	{
//		vector<int> vec1(vec);
//		vector<int> vec2(JNX);
//		RandSat(vec2);
//		if (priorSat.empty()) 
//		{
//			AllocateLink(Sat_Gap, snap, vec1, vec2, priorSat, i);
//		}
//		else
//		{
//			CreatLink(priorSat, vec2, Sat_Gap, snap, i,vec1);
//			AllocateLink(Sat_Gap, snap, vec1, vec2, priorSat, i);
//		}
//	}
//}
//
////������·��
//void GetRoute(const vector<vector<int>> &Sat_Gap, int from, int _gap, vector<int> &tmp, int snap)
//{
//	tmp.push_back(from);
//	for (int i = _gap; i < _Gap; i++)
//	{
//		int to = Sat_Gap[from][i];
//		if (to > 0)
//		{
//			if (IS_JNX[snap][to])
//			{
//				tmp.push_back(to);
//				return;
//			}
//			else
//			{
//				tmp.push_back(to);
//				from = to;
//			}
//		}
//		else
//		{
//			tmp.push_back(0);
//		}
//	}
//}
//
////��������Ϣ�ش�������·��
//void GetAllRoute(const vector<vector<int>> &Sat_Gap, int snap, vector<vector<vector<int>>> &route)
//{
//	for (int i = 0; i < JWX.size(); i++)
//	{
//		int from = JWX[i];
//		for (int j = 1; j < Gap; j++)
//		{
//			GetRoute(Sat_Gap, from, j, route[from][j], snap);
//		}
//	}
//}
//
////���㾳�������ݻش������������ƽ������
//void GetJump(int &maxJump, double &avgJump, const vector<vector<vector<int>>> &route)
//{
//	int max = 0;
//	double sum = 0;
//	for (int i = 0; i < JWX.size(); i++)
//	{
//		int from = JWX[i];
//		for (int j = 1; j < Gap; j++)
//		{
//			sum += (route[from][j].size() - 1);
//			if (max < route[from][j].size())
//			{
//				max = route[from][j].size();
//				maxJump = max - 1;
//			}
//		}
//	}
//	avgJump = sum / (JWX.size() * 20);
//}
//
////����һ����������·�Ƿ�ͨ��
//void GetCorrespondInfo(const vector<vector<int>> &vec, int pos)
//{
//	for (int i = 0; i < JWX.size(); i++)
//	{
//		int from = JWX[i];
//		for (int j = 1; j < Gap; j++)
//		{
//			int to = vec[from][j];
//			if (to > 0)
//			{
//				int index = (from - 1)*(Sat_Num - 1) + to-1;
//				working[index].push_back(pos + j - 1);
//			}
//			if (to < 0)
//			{
//				int index = (-to - 1)*(Sat_Num - 1) + from-1;
//				working[index].push_back(pos + j - 1);
//			}
//		}
//	}
//}
