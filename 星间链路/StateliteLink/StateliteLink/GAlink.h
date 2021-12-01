#pragma once
#ifndef GALINK_H
#define GALINK_H
#include <iostream>

using namespace std;

/*
	�����������Ŵ��㷨�Ż��Ǽ���·������

	Ŀ�ģ����پ����ǻش�����


	���壺��·��
	��Ⱥ��������·��ļ���
	�����ͣ���·���ͨ��ʱ�ӣ������ǻش��������ǵ�������
	�����ͣ���·��ÿ��ʱ϶�Ľ������
	��Ӧ�Ⱥ�����ÿ����·���ͨ��ʱ�ӵĵ���
	����ѡ����̭������������·��ѡ�񾡿���һ�������·��ͨ��ʱ�Ӷ̵�ͬʱ��Ҫ������������������������Ĵ�����
	���򽻲棺������������ĳ������ĳЩʱ϶���н���
	����ͻ�䣺��ĳ��ʱ϶�Ľ���������иı䣬���ȸı侳����֮�����·����θı侳����֮�����·�����ľ������뾳���ǵ���·

*/

const int maxgen = 100;				//����������
const int populationSize = 16;		//��Ⱥ��ģ
const double possibilityCross = 0.6;	//�������
const double possibilityMutation = 0.1;//�������


const int gap = 21;		//ʱ϶����Ⱦɫ�峤�ȣ�
const int satNum = 25;	//�����������򳤶ȣ�


int chromosome[populationSize][satNum][gap];	//��·���ϣ���Ⱥ��
float fitness[populationSize];					//��·���ͨ��ʱ�ӣ�������Ӧ�ȵļ��ϣ�
int maxFitnessIndex = 0;						//ͨ��ʱ����С����·����ѵĸ��壩
float maxFitness = 0;							//��Ӧ����ߵĸ���
int BestLink[Sat_Num][Gap];


//������Ӧ��
float CaculateFitnes()
{
	return jump3+avgjump;
}

//���ɽ�����
float CreatLinkTable()
{
	//��·����
	InitialGap();
	InitialJNXSource();
	SortLink();
	AllocateJWX();
	CreatLink();
	UpgradeLink();

	//����·��
	CreatRount();
	CalJump();
	return  1/ CaculateFitnes();
}

//��ʼ����Ⱥ
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

//ѡ��
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
	cout << "��Ӧ����ѵĸ���Ϊ" << maxFitnessIndex << "�Ÿ���" << endl;
	cout << "ͨ��ʱ��Ϊ" << maxFitness << endl;

	for (int j = 0; j < populationSize; j++)
	{
		fitnessPro[j] = fitness[j] / sumFitness;
	}

	//����ѡ��
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

//����
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

		//��������posλ�õĻ���(����posʱ϶����·״̬)
		for (int i = 0; i < satNum; i++)
		{
			int temp = chromosome[index][i][pos];
			chromosome[index][i][pos] = chromosome[index + 1][i][pos];
			chromosome[index + 1][i][pos] = temp;
		}
		index += 2;
	}
}

//����
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

		//��posʱ϶����·ת̬���иı�

		//����ʱ϶�ĵ���·��Ϊ��
		for (int j = 1; j < satNum; j++)
		{
			chromosome[i][j][pos] = 0;
						
		}
		//�����еľ����Ƿ��侳�������佨��
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

//��Ӧ�ȸ���
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

//��ֳ
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