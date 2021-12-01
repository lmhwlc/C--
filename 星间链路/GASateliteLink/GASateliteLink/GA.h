#pragma once
#include<iostream>
#include"Link.h"
#include <algorithm>
#include<fstream>
using namespace std;
int curItem;
const int pop_size  = 120;		//种群规模
const int maxgens = 500;		//迭代次数
const float pro_crossver = 0.6;	//交换概率
const float pro_mutation = 0.8;	//突变概率
vector<vector<vector<int>>> Population(pop_size);		//初代种群
int res1[maxgens];
double res2[maxgens];

//适应度结构
struct Pop_fitness
{
	int index;
	int maxJump;
	double avgJump;
	double fitness;
}pop_fitness[pop_size];

//自定义排序方法
bool compare(Pop_fitness a, Pop_fitness b)
{
	return a.fitness < b.fitness;
}

//初始化
void InitilaPop()
{
	//初始化种群
	for (int i = 0; i < pop_size; i++)
	{
		Population[i].resize(Sat_Num);
	}
	for (int i = 0; i < pop_size; i++)
	{
		for (int j = 0; j < Sat_Num; j++)
		{
			Population[i][j].resize(Gap);
		}
	}
}

//生成个体
void CreatItem(int index,int snap)
{
	AllocateLink(Population[index], snap);
	CreatRoute(Population[index], snap);
}

//打印种群
void PrintPop(const vector<vector<vector<int>>> p)
{
	for (int i = 0; i < pop_size; i++)
	{
		cout << "个体" << i << ":" << endl;
		for (int j = 0; j < JWX.size(); j++)
		{
			int from = JWX[j];
			cout << setw(5) << left << from;
			for (int k = 1; k < Gap; k++)
			{
				cout << setw(5) << left << p[i][from][k];
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}

//生成初代种群
void CreatPop(int snap)
{
	InitilaPop();
  	srand(time(NULL));
	for (int i = 0; i < pop_size; i++)
	{
		thread obj(CreatItem, i, snap);
		obj.join();
	}
}

// 个体适应度计算
void CalItemFitness(vector<vector<vector<int>>> route,int snap,int start,int stop)
{
	for (int i = start; i < stop; i++)
	{
		for (int i = 1; i < Sat_Num - 6; i++)
			route[i].resize(Gap);

		GetAllRoute(Population[i], snap, route);
		GetJump(pop_fitness[i].maxJump, pop_fitness[i].avgJump, route);
		pop_fitness[i].fitness = pop_fitness[i].avgJump * 0.4 + pop_fitness[i].maxJump * 0.6;
		pop_fitness[i].index = i;

		for (int i = 1; i < Sat_Num - 6; i++)
			vector<vector<int>>().swap(route[i]);
	}
	
}
//适应度计算
void CalFitness(int snap)
{
	vector<vector<vector<int>>> route(Sat_Num);		//一个周期的路由集合
	CalItemFitness(route, snap, 0, pop_size);

	//PrintItem(Population[28]);
	//输出最佳的个体
	sort(pop_fitness, pop_fitness + pop_size, compare);
	if (curItem != pop_fitness[0].index)
	{
		cout << "最佳个体编号为：	" << curItem << " 最佳个体适应值为： " << pop_fitness[0].fitness << endl;
		cout << "平均跳数为：	" << pop_fitness[0].avgJump << " 最大跳数为：" << pop_fitness[0].maxJump << endl;
		PrintItem(Population[curItem]);
	}
	//PrintPop(Population);
	curItem = pop_fitness[0].index;
	//计算适应值概率
	

	//for (int i = 0; i < pop_size; i++)
	//{
	//	int it = pop_fitness[i].index;
	//	PrintItem(Population[it]);
	//}
}

//寻找最优基因
void SearchBest(const vector<vector<int>> &vec, vector<int> &pos,int snap)
{
	int link_num = 0;
	for (int i = 1; i < Gap; i++)
	{
		int tmp = 0;
		for (int j = 0; j < JWX.size(); j++)
		{
			int from = JWX[j];
			if (IS_JNX[snap][vec[from][i]])
				tmp++;
			
		}
		if (tmp > link_num)
		{
			vector<int>().swap(pos);
			link_num = tmp;
			pos.push_back(i);
		}
		if(tmp==link_num)
			pos.push_back(i);
	}
}

//寻找最劣基因
void SearchWorst(const vector<vector<int>> &vec,int &pos,int snap)
{
	int link_num = 30;
	for (int i = 1; i < Gap; i++)
	{
		int tmp1 = 0;
		int tmp2 = 0;
		for (int j = 0; j < JWX.size(); j++)
		{
			int from = JWX[j];
			if (IS_JNX[snap][vec[from][i]])
				tmp1++;
		}
		if (tmp1 < link_num)
		{
			link_num = tmp1;
			pos = i;
		}
	}
}


//int IS_crossover(vector<vector<int>> vec1,vector<vector<int>> vec2,vector<int> best,int worst )
//{
//	for (int j = 0; j < best.size(); j++)
//	{
//		bool flag = true;
//		int _best = best[j];
//		for (int i = 0; i < JWX.size(); i++)
//		{
//			int from = JWX[i];
//			swap(vec1[from][_best], vec2[from][worst]);
//			if (IsLinkNum(vec2, from) >= link_num)
//				continue;
//			else
//			{
//				flag = false;
//			}
//		}
//		if (flag)
//			return _best;
//	}
//	return -1;
//}

//交叉
void Crossover(int snap)
{
	double pick1;
	int index = 1;
	//选择生存能力差的一半个体进行交叉操作
	while (index< pop_size)
	{
		pick1 = rand() / (double(RAND_MAX));
		if (pick1 > pro_crossver)
		{
			index++;
			continue;
		}
		int item = pop_fitness[index].index;

		//选择交叉的时隙
		int pos1 = rand() % 20 + 1;
		int pos2 = rand() % 20 + 1;
		if (pos1 == pos2)
		{
			if (pos1 < Gap - 1)
				pos1++;
			else
				pos1--;
		}
	
		//PrintItem(Population[item]);
		for (int i = 1; i < Sat_Num; i++)
		{
			swap(Population[item][i][pos1], Population[item][i][pos2]);
		}
		//PrintItem(Population[item]);
		index++;
	}
}

//可见境内星优先建链策略
void CreatLink(vector<int> &vec1, vector<int> &vec2, int pos,int item,int snap)
{
	bool flag = false;
	while (!vec1.empty())
	{
		int from = vec1[0];
		flag = false;
		for (int k = 0; k < vec2.size(); k++)
		{
			int to = vec2[k];
			if (SatSatKjx[snap][from][to] == 1)
			{
				Population[item][from][pos] = to;
				Population[item][to][pos] = from;
				int linkNum = IsLinkNum(Population[item], from);
				if (linkNum >= link_num)
				{
					Remove(from, vec1);
					Remove(to, vec2);
					flag = true;
					break;
				}
				else
				{
					Population[item][from][pos] = 0;
					Population[item][to][pos] = 0;
				}
			}
		}

		//如果找不到境内星和它建链则与境外星建链
		if (flag == false)
		{
			for (int k = 1; k < vec1.size(); k++)
			{
				int to = vec1[k];
				if (SatSatKjx[snap][from][to] == 1)
				{
					Population[item][from][pos] = to;
					Population[item][to][pos] = from;
					int linkNum1 = IsLinkNum(Population[item], from);
					int linkNum2 = IsLinkNum(Population[item], to);
					if ((linkNum1 >= link_num) && (linkNum2 >= link_num))
					{
						Remove(from, vec1);
						Remove(to, vec1);
						break;
					}
					else
					{
						Population[item][from][pos] = 0;
						Population[item][to][pos] = 0;
					}
				}
			}
			Remove(from, vec1);
		}
	}
}

//更新基因有变化个体的适应值
void UpdataFitness(int item,int snap)
{
	vector<vector<vector<int>>> route(Sat_Num);
	for (int i = 1; i < Sat_Num - 6; i++)
		route[i].resize(Gap);
	int _maxJump;
	double _avgJump;
	GetAllRoute(Population[item], snap, route);
	GetJump(_maxJump, _avgJump, route);
	pop_fitness[item].fitness = _maxJump * 0.4 + _avgJump * 0.6;
}
//变异
void Mutation(int snap)
{
	double pick1;
	double pick2;
	int index = 1;
	//选择生存能力差的一半个体进行变异操作
	while (index < pop_size)
	{
		pick1 = rand() / (double)RAND_MAX;
		if (pick1 > pro_mutation)
		{
			index++;
			continue;
		}

		int item = pop_fitness[index].index;
		//PrintItem(Population[item]);

		//选择突变的时隙
		int pos = rand() % 20 + 1;
		//int pos;
		//SearchWorst(Population[item], pos,snap);
		//将重新建链的时隙置空
		for (int i = 1; i < Sat_Num; i++)
			Population[item][i][pos] = 0;

		//待突变的个体
		//cout << "待突变的个体" << endl;
		//PrintItem(Population[item]);
		//对该时隙重新建链，优先与可见境内星建链
		vector<int> tmp1(JWX);
		vector<int> tmp2(JNX);
		RandSat(tmp2);
		RandSat(tmp1);

		CreatLink(tmp1, tmp2, pos, item,snap);
		CreatRoute(Population[item], snap, pos);

		//将待突变的时隙中，没有与境内星建链的境外星重新建链
		/*vector<int> p;
		for (int i = 0; i < JWX.size(); i++)
		{
			int from = JWX[i];
			int to = Population[item][from][pos];
			if (!satelite[to].GetSateliteJNX())
				p.push_back(to);
			else
				Remove(to, tmp2);
		}

		CreatLink(p, tmp2, pos, item);*/

		//cout << "突变后的个体" << endl;
		//PrintItem(Population[item]);

		index++;
	}
}

//繁殖
void Reproduce(int snap)
{
	ofstream out("res.txt");
	if (out.is_open())
	{
		for (int i = 0; i < maxgens; i++)
		{
			//if(i%10==0)
			CalFitness(snap);
			Crossover(snap);
			Mutation(snap);
			//res2[i] = pop_fitness[0].fitness;
			out << pop_fitness[0].maxJump << "	" << pop_fitness[0].avgJump << endl;
		}
	}
	out.close();
}

//计算一周的建链状态
void GetPeriodLink()
{
	//打印可见性
	//int t = 500;
	//for (int i = 0; i < JWX.size(); i++)
	//{
	//	int from = JWX[i];
	//	for (int k = 1; k < Sat_Num; k++)
	//	{
	//		if(SatSatKjx[t][from][k])
	//			cout << setw(5) << left << k;
	//	}
	//	cout << endl;
	//}

	//cout << endl << endl;
	//for (int i = 1; i < Land_Num; i++)
	//{
	//	for (int k = 1; k < Sat_Num; k++)
	//	{
	//		cout << setw(5) << left << SatLandKjx[t][i][k];
	//	}
	//	cout << endl;
	//}
	//cout << endl << endl;
	//初始化路径

	for (int i = 500; i < period; i++)
	{
		i = 500;
		ClassifySat(i);
		PrintSat(JWX);
		PrintSat(JNX);
		int t = 700;
		for (int i = 0; i < JWX.size(); i++)
		{
			int from = JWX[i];
			cout << setw(5) << left << from;
			for (int k = 1; k < Sat_Num; k++)
			{
				if (SatSatKjx[t][from][k])
					cout << setw(5) << left << k;
			}
			cout << endl;
		}
		CreatPop(i);
		//PrintPop(Population);
		Reproduce(i);
		vector<int>().swap(JWX);
		vector<int>().swap(JNX);
	}
}