#pragma once
#include<iostream>
#include"Link.h"
#include <algorithm>
#include<fstream>
using namespace std;
int curItem;
const int pop_size  = 120;		//��Ⱥ��ģ
const int maxgens = 500;		//��������
const float pro_crossver = 0.6;	//��������
const float pro_mutation = 0.8;	//ͻ�����
vector<vector<vector<int>>> Population(pop_size);		//������Ⱥ
int res1[maxgens];
double res2[maxgens];

//��Ӧ�Ƚṹ
struct Pop_fitness
{
	int index;
	int maxJump;
	double avgJump;
	double fitness;
}pop_fitness[pop_size];

//�Զ������򷽷�
bool compare(Pop_fitness a, Pop_fitness b)
{
	return a.fitness < b.fitness;
}

//��ʼ��
void InitilaPop()
{
	//��ʼ����Ⱥ
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

//���ɸ���
void CreatItem(int index,int snap)
{
	AllocateLink(Population[index], snap);
	CreatRoute(Population[index], snap);
}

//��ӡ��Ⱥ
void PrintPop(const vector<vector<vector<int>>> p)
{
	for (int i = 0; i < pop_size; i++)
	{
		cout << "����" << i << ":" << endl;
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

//���ɳ�����Ⱥ
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

// ������Ӧ�ȼ���
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
//��Ӧ�ȼ���
void CalFitness(int snap)
{
	vector<vector<vector<int>>> route(Sat_Num);		//һ�����ڵ�·�ɼ���
	CalItemFitness(route, snap, 0, pop_size);

	//PrintItem(Population[28]);
	//�����ѵĸ���
	sort(pop_fitness, pop_fitness + pop_size, compare);
	if (curItem != pop_fitness[0].index)
	{
		cout << "��Ѹ�����Ϊ��	" << curItem << " ��Ѹ�����ӦֵΪ�� " << pop_fitness[0].fitness << endl;
		cout << "ƽ������Ϊ��	" << pop_fitness[0].avgJump << " �������Ϊ��" << pop_fitness[0].maxJump << endl;
		PrintItem(Population[curItem]);
	}
	//PrintPop(Population);
	curItem = pop_fitness[0].index;
	//������Ӧֵ����
	

	//for (int i = 0; i < pop_size; i++)
	//{
	//	int it = pop_fitness[i].index;
	//	PrintItem(Population[it]);
	//}
}

//Ѱ�����Ż���
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

//Ѱ�����ӻ���
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

//����
void Crossover(int snap)
{
	double pick1;
	int index = 1;
	//ѡ�������������һ�������н������
	while (index< pop_size)
	{
		pick1 = rand() / (double(RAND_MAX));
		if (pick1 > pro_crossver)
		{
			index++;
			continue;
		}
		int item = pop_fitness[index].index;

		//ѡ�񽻲��ʱ϶
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

//�ɼ����������Ƚ�������
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

		//����Ҳ��������Ǻ����������뾳���ǽ���
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

//���»����б仯�������Ӧֵ
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
//����
void Mutation(int snap)
{
	double pick1;
	double pick2;
	int index = 1;
	//ѡ�������������һ�������б������
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

		//ѡ��ͻ���ʱ϶
		int pos = rand() % 20 + 1;
		//int pos;
		//SearchWorst(Population[item], pos,snap);
		//�����½�����ʱ϶�ÿ�
		for (int i = 1; i < Sat_Num; i++)
			Population[item][i][pos] = 0;

		//��ͻ��ĸ���
		//cout << "��ͻ��ĸ���" << endl;
		//PrintItem(Population[item]);
		//�Ը�ʱ϶���½�����������ɼ������ǽ���
		vector<int> tmp1(JWX);
		vector<int> tmp2(JNX);
		RandSat(tmp2);
		RandSat(tmp1);

		CreatLink(tmp1, tmp2, pos, item,snap);
		CreatRoute(Population[item], snap, pos);

		//����ͻ���ʱ϶�У�û���뾳���ǽ����ľ��������½���
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

		//cout << "ͻ���ĸ���" << endl;
		//PrintItem(Population[item]);

		index++;
	}
}

//��ֳ
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

//����һ�ܵĽ���״̬
void GetPeriodLink()
{
	//��ӡ�ɼ���
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
	//��ʼ��·��

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