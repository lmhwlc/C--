//#pragma once
//#include"Info.h"
//using namespace std;
//#include <algorithm>
//#include"Info.h"
//#include<vector>
//#include<string>
//#include<map>
//const int Gap = 21;			//一个周期的时隙数
//const int _Gap = 31;		//拓展半个周期的时隙数
//vector<int> Sat;			//存放所有的卫星
//vector<int> JWX;			//存放所有境外星
//vector<int> JNX;			//存放所有境内星
//const int link_num = 10;	//链路数量约束
//vector<vector<int>> Sat_Gap(Sat_Num);	//时隙表
//vector<vector<int>> sat_num;
//vector<vector<vector<int>>> route(Sat_Num);		//一个周期的路由集合
//vector<vector<int>> working(720);				//所有链路的状态
//vector<vector<int>> ClassifyJNX(Sat_Num);		//每个卫星可见的境内星
//vector<vector<int>> ClassifyJWX(Sat_Num);		//每个卫星可见的境外星
//vector<string> linkName;
////map<string, vector<bool>> working;
//vector<bool> pr(Sat_Num, false);
//
////按值删除vector里的某个元素
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
////将每个境外星的可见卫星分类优先分配境内星，境内星被分配过则降低其分配的优先级，无可建链卫星则与境外星建链
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
////获取卫星属性和可见性信息
//void GetSateliteInfo()
//{
//	CreatKeyVal();
//
//	//初始化时隙表
//	for (int i = 0; i < Sat_Num; i++)
//		Sat_Gap[i].resize(_Gap);
//
//	//初始化路由表
//	for (int i = 1; i < Sat_Num - 6; i++)
//		route[i].resize(Gap);
//	GetAllAccess();
//
//
//	//初始化链路名
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
////打印卫星的顺序
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
////将卫星分类
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
////打印个体
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
////随机访问境内星的可见卫星顺序
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
////计算每个境外星的可见卫星数
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
////自定义排序规则
//bool compare(vector<int> a, vector<int> b)
//{
//	return a[1] < b[1];
//}
//
////优先级设置（为境外星寻找合适的境内星作为数据中转）
///*
//	1.当前时隙的上一个时隙未建链和与境外星建链的境外星处于最高优先级
//	2.所有境外星按其可见境内星的数量设置优先级，数量越少，优先级越高
//	3.尽可能让更多的卫星在一个周期内与境外星建链以获取更好的观测数据减少PDOP,在某个时隙建链过的卫星优先级降至最低一级
//	4.当前境内星资源用完，但还存在为分配的境外星，则进行境外星与境外星建链
//	5.每次都随机访问境外星
//*/
//
//
////未与境内星建链或者未建链的境外星优先建链
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
////境外星优先与最小资源的境内星建链
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
//		//如果当前境外星找不到与其建链的境内星，则它与境外星建链
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
////将境内星打乱顺序,然后依次分配卫星，循环一个周期
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
////求解最短路径
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
////求境外星信息回传的所有路径
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
////计算境外星数据回传的最大跳数和平均跳数
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
////计算一个周期内链路是否通信
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
