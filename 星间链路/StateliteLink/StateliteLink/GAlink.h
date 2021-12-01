#pragma once
#ifndef GALINK_H
#define GALINK_H
#include <iostream>

using namespace std;

/*
	方法：基于遗传算法优化星间链路建链表

	目的：减少境外星回传跳数


	个体：链路表
	种群：若干链路表的集合
	表现型：链路表的通信时延（境外星回传到境内星的跳数）
	基因型：链路表每个时隙的建链情况
	适应度函数：每张链路表的通信时延的倒数
	个体选择：淘汰存在三跳的链路表，选择尽可能一跳多的链路表（通信时延短的同时还要避免三跳的情况，减少两跳的次数）
	基因交叉：随机两个个体的某个或者某些时隙进行交换
	基因突变：对某个时隙的建链情况进行改变，优先改变境外星之间的链路，其次改变境外星之间的链路，最后改境内星与境外星的链路

*/

const int maxgen = 100;				//最大进化次数
const int populationSize = 16;		//种群规模
const double possibilityCross = 0.6;	//交叉概率
const double possibilityMutation = 0.1;//变异概率


const int gap = 21;		//时隙数（染色体长度）
const int satNum = 25;	//卫星数（基因长度）


int chromosome[populationSize][satNum][gap];	//链路表集合（种群）
float fitness[populationSize];					//链路表的通信时延（个体适应度的集合）
int maxFitnessIndex = 0;						//通信时延最小的链路表（最佳的个体）
float maxFitness = 0;							//适应度最高的个体
int BestLink[Sat_Num][Gap];


//计算适应度
float CaculateFitnes()
{
	return jump3+avgjump;
}

//生成建链表
float CreatLinkTable()
{
	//链路分配
	InitialGap();
	InitialJNXSource();
	SortLink();
	AllocateJWX();
	CreatLink();
	UpgradeLink();

	//生成路由
	CreatRount();
	CalJump();
	return  1/ CaculateFitnes();
}

//初始化种群
void InitialPopulation()
{
	for (int i = 0; i < populationSize; i++)
	{
		fitness[i] = CreatLinkTable();

		jump = jump1 = jump2 = jump3 = 0;

		for (int j = 1; j < Sat_Num; j++)
		{
			for (int k = 1; k < Gap; k++)
			{
				chromosome[i][j][k] = Sat_Gap[j][k];
			}
		}
	}
}

//选择
void Selection()
{
	int selectChromosome[populationSize][satNum][gap] = {0};
	float sumFitness = 0;
	float fitnessPro[populationSize];
	double pick = 0;

	for (int i = 0; i < populationSize; i++)
	{
		if (fitness[i] > maxFitness)
		{
			maxFitness = fitness[i];
			maxFitnessIndex = i;
		}
		sumFitness += fitness[i];
	}

	for (int i = 1; i < Sat_Num; i++)
		for (int j = 1; j < gap; j++)
			BestLink[i][j] = chromosome[maxFitnessIndex][i][j];
	cout << "适应度最佳的个体为" << maxFitnessIndex << "号个体" << endl;
	cout << "通信时延为" << maxFitness << endl;

	for (int j = 0; j < populationSize; j++)
	{
		fitnessPro[j] = fitness[j] / sumFitness;
	}

	//轮盘选择
	for (int k = 0; k < populationSize; k++)
	{
		pick = ((double)rand()) / RAND_MAX;
		for (int i = 0; i < populationSize; i++)
		{
			pick = pick - fitnessPro[i];
			if (pick <= 0)
			{
				for (int j = 1; j < satNum; j++)
				{
					for (int t = 1; t < gap; t++)
					{
						selectChromosome[k][j][t] = chromosome[i][j][t];
					}
				}
				break;
			}
		}
	}

	for (int i = 0; i < populationSize; i++)
		for (int j = 1; j < satNum; j++)
			for (int k = 1; k < gap; k++)
				chromosome[i][j][k] = selectChromosome[i][j][k];

}

//交叉
void Crossover()
{
	double pick1;
	double pick2;
	int index = 0;
	int pos;
	while (index < populationSize - 1)
	{
		pick1 = ((double)rand()) / RAND_MAX;
		if (pick1 > possibilityCross)
		{
			index += 2;
			continue;
		}

		pick2 = ((double)rand()) / (RAND_MAX + 1.0);
		pos = (int)(pick2*gap);

		//交换父代pos位置的基因(互换pos时隙的链路状态)
		for (int i = 0; i < satNum; i++)
		{
			int temp = chromosome[index][i][pos];
			chromosome[index][i][pos] = chromosome[index + 1][i][pos];
			chromosome[index + 1][i][pos] = temp;
		}
		index += 2;
	}
}

//变异
void Mutation()
{
	double pick1, pick2;
	int pos;
	for (int i = 0; i < populationSize; i++)
	{
		pick1 = ((double)rand()) / RAND_MAX;
		if (pick1 > possibilityMutation)
		{
			continue;
		}
		pick2 = ((double)rand()) / (RAND_MAX + 1.0);
		pos = (int)(pick2*gap);

		//对pos时隙的链路转态进行改变

		//将该时隙的的链路置为空
		for (int j = 1; j < satNum; j++)
		{
			chromosome[i][j][pos] = 0;
						
		}
		//对所有的境外星分配境内星与其建链
		for (int j = 1; j < satNum; j++)
		{
			if (satelite[j].GetSateliteJNX() == false)
			{
				for (int k = 1; k < Sat_Num; k++)
				{
					if (SatSatKJX[j][k] && satelite[k].GetSateliteJNX()&& !SatJL(k, pos))
					{
						chromosome[i][j][pos] = k;
						chromosome[i][k][pos] = j;
					}
				}
			}
		}
	}
}

//适应度更新
void UpdataFitness()
{
	for (int i = 0; i < populationSize; i++)
	{
		for (int j = 1; j < Sat_Num; j++)
			for (int k = 1; k < Gap; k++)
			{
				Sat_Gap[j][k] = chromosome[i][j][k];
			}
		CreatRount();
		CalJump();
		fitness[i] = 1 / CaculateFitnes();
		jump = jump1 = jump2 = jump3 = 0;
	}	
}

//繁殖
void Reproduce()
{
	for (int i = 0; i < 60; i++)
	{
		Selection();
		Crossover();
		Mutation();
		UpdataFitness();
	}
}

#endif // !GALINK>H