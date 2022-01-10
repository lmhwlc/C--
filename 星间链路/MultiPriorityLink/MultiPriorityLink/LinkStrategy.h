#pragma once
#include"AccessDate.h"
#include<fstream>
#include<iostream>
using namespace std;

struct satelite
{
	int number;				//���Ǳ��
	int InNum;				//�ɼ�����������
	int OutNum;				//�ɼ�����������
	set<int> LinkSats;		//���ǵ���·���
	vector<int> InSat;		//�ɼ�������
	vector<int> OutSat;		//�ɼ�������
};


//��ȡ���е�������Ϣ
void GetAllInfo(int num);

//ͳ��ÿ�����ǵĿɼ����������������ǣ������ǣ�
void InitialSatInfo();

/*
	�������ǽ�����˳�򰴿ɼ�������������С�������򣬾�����������ͬ���򰴿ɼ������ǵ������Ӵ�С����
	�������Ǳ������˳����ɼ������ǵ�������С��������,������������ͬ�򰴿ɼ������������Ӵ�С����
*/
void CreatLink();

//�ж�ʱ϶���е�����Լ��
bool JudgeJump();

//��ӡʱ϶��
void PrintTimeSlotTable();

//ͳ��ÿ�������ǵ���·����
void GetJwxLinks();

//ͳ��ʱ�����
void CalJump();

//��ȡһ�����ڵ�ʱ϶��
void GetAllSlot(int stateNum);