#pragma once
#include<iostream>
#include<set>
#include<vector>
#include<string>
#include<map>
#include<unordered_set>
using namespace std;

const int PeriodNum = 8640;			//�ع����ڵ�ʱ϶��Ŀ
const int SatNum = 30;				//�����е�������Ŀ
const int LandNum = 4;				//����վ������

//��ȡ״̬���Ӿ���
void GetStateAccess(int);

//���ݳ�ʼ��
void InitialData();


//�ո��滻����
void ReplaceSpace(string& str);


//����һ���ɼ��Լ�¼
void GetLine(string& line, double& StartTime, double& EndTime, int& Duration, int& From, int& To);


//��ȡ�Ǽ�ɼ�����Ϣ
void GetSatSatAccess(string& FileName);


//��ȡ�ǵؿɼ�����Ϣ
void GetSatLandAccess(string& FileName);


//��״̬������������
void DivideState(int);


//��ӡ�Ǽ�ɼ���
void PrintSatSatAccess(vector<vector<bool>>& VecSatSat, vector<bool>& VecJnx);


//��ӡ�ǵؿɼ���
void PrintSatLandAccess(vector<bool>& VecJnx);


//��ȡ�������ԺͿɼ�����Ϣ
void GetSatLandInfo();


//���ڿ��Ӿ����Ƿ�仯
bool JudgeAccess(vector<vector<bool>>& v1, vector<vector<bool>>& v2);


//Ѱ����һ�����Ӿ���仯��ʱ��ڵ�
int GetAccessPoint(vector<vector<vector<bool>>>& vec, int CurPoint, int StateNum);


//��MEO11�ڲ�ͬʱ����״̬�£��ɼ��Ե�������ռ��
void GetAnsMeo(vector<vector<vector<bool>>>& vec, int StateNum);


//���治ͬʱ϶�����µĿɼ�����Ϣ
void SaveALlInfo();

