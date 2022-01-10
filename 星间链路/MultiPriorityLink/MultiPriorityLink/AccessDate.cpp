#include"AccessDate.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
using namespace std;

//������
vector<string> VecSatName{ "", "11","12" ,"13" ,"14" ,"15","16","17","18",
							"21","22" ,"23" ,"24" ,"25","26","27","28",
							"31","32" ,"33" ,"34" ,"35","36","37","38",
							"G1","G2", "G3", "G4", "G5", "G6" };

map<string, int> MapCraftIndex;
vector<vector<bool>> VecIsJnx;					//��������
vector<vector<bool>> VecStateIsJnx;				//ÿ��״̬����������
vector<vector<vector<bool>>> VecSatToSat;		//�Ǽ�ɼ���
vector<vector<vector<bool>>> VecLandToSat;		//�ǵؿɼ���
vector<vector<vector<bool>>> VecStateSatSat;	//ÿ��״̬���Ǽ�ɼ���
vector<vector<vector<bool>>> VecStateLandSat;	//ÿ��״̬���ǵؿɼ���
vector<unordered_set<int>> VecStaticLinks;		//��̬��·

int StateLength = 1;			//״̬����

void GetStateAccess(int length)
{
	vector<vector<vector<bool>>>().swap(VecStateSatSat);
	vector<vector<bool>>().swap(VecStateIsJnx);
	int StateNum = PeriodNum / length;
	VecStateIsJnx.resize(StateNum);
	VecStateSatSat.resize(StateNum);
	VecStateLandSat.resize(StateNum);
	for (int i = 0; i < StateNum; i++)
	{
		VecStateIsJnx[i].resize(SatNum + 1);
		VecStateSatSat[i].resize(SatNum + 1);
		VecStateLandSat[i].resize(SatNum + 1);

		for (int j = 1; j <= SatNum; j++)
		{
			VecStateSatSat[i][j].resize(SatNum + 1);
			VecStateLandSat[i][j].resize(LandNum + 1);
		}
	}
}


void InitialData()
{
	VecStaticLinks.resize(SatNum + 1);

	//��ʱ϶���ֵĿɼ���
	VecIsJnx.resize(PeriodNum);
	VecSatToSat.resize(PeriodNum);
	VecLandToSat.resize(PeriodNum);

	for (int i = 0; i < PeriodNum; i++)
	{
		VecSatToSat[i].resize(SatNum + 1);
		VecLandToSat[i].resize(SatNum + 1);
		VecIsJnx[i].resize(SatNum + 1);

		for (int j = 1; j <= SatNum; j++)
		{
			VecSatToSat[i][j].resize(SatNum + 1);
			VecLandToSat[i][j].resize(LandNum + 1);
		}
	}

	//�������ֺ�������ӳ��
	for (int i = 1; i <= 30; ++i)
		MapCraftIndex[VecSatName[i]] = i;

	MapCraftIndex["1"] = 1;
	MapCraftIndex["2"] = 2;
	MapCraftIndex["3"] = 3;
	MapCraftIndex["4"] = 4;
}


void ReplaceSpace(string& str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ',')
			str[i] = ' ';
	}
}


void GetLine(string& line, double& StartTime, double& EndTime, int& Duration, int& From, int& To)
{
	vector<string> VecAccessResult;
	string item;
	stringstream input(line);
	while (input >> item)
	{
		VecAccessResult.push_back(item);
	}

	StartTime = stod(VecAccessResult[0]);
	EndTime = stod(VecAccessResult[1]);
	Duration = stoi(VecAccessResult[2]);
	From = MapCraftIndex[VecAccessResult[3]];
	To = MapCraftIndex[VecAccessResult[4]];
}


void GetSatSatAccess(string& FileName)
{
	ifstream fin(FileName);
	string line;
	double StartTime;
	double EndTime;
	int Duration;
	int	FromSat;
	int ToSat;
	while (getline(fin, line))
	{
		ReplaceSpace(line);
		GetLine(line, StartTime, EndTime, Duration, FromSat, ToSat);

		//��¼�����ɼ�����
		if (Duration == 8640)
			VecStaticLinks[FromSat].insert(ToSat);

		//��¼�ǳ����ɼ�����
		/*
			ÿ��һ���Ӽ�¼һ�Σ�һ���������ǳ����ɼ�����ǰ����֡������Ϊ�ɼ�
			��һ�����ڷǳ����ɼ�����ǰ��֡������֮�䲻�ɼ�
		*/
		int start = StartTime;
		if (start != StartTime)		//��ǰ��֡����һ����
			start++;
		while ((start + 1.5) < EndTime)
		{
			VecSatToSat[start][FromSat][ToSat] = true;
			VecSatToSat[start][ToSat][FromSat] = true;
			start++;
		}
	}
}


void GetSatLandAccess(string& FileName)
{
	ifstream fin(FileName);
	string line;
	double StartTime;
	double EndTime;
	int Duration;
	int	FromLand;
	int ToSat;
	while (getline(fin, line))
	{
		ReplaceSpace(line);
		GetLine(line, StartTime, EndTime, Duration, FromLand, ToSat);

		//��¼�ǳ����ɼ�����
		/*
			ÿ��һ���Ӽ�¼һ�Σ�һ���������ǳ����ɼ�����ǰ����֡������Ϊ�ɼ�
			��һ�����ڷǳ����ɼ�����ǰ��֡������֮�䲻�ɼ�
		*/
		int start = StartTime;
		if (start != StartTime)		//��ǰ��֡����һ����
			start++;
		while ((start + 1.5) < EndTime)
		{
			VecLandToSat[start][FromLand][ToSat];
			VecIsJnx[start][ToSat] = true;
			start++;
		}
	}
}


void DivideState(int StateNum)
{
	int StateLength = PeriodNum / StateNum;
	//�Ǽ�ɼ��Ի���
	for (int i = 1; i <= SatNum; i++)
	{
		for (int j = 1; j <= SatNum; j++)
		{
			for (int k = 0; k < StateNum; k++)
			{
				for (int t = 0; t < StateLength; t++)
				{
					if (VecSatToSat[k * StateLength + t][i][j] == false)
					{
						VecStateSatSat[k][i][j] = false;
						break;
					}
					VecStateSatSat[k][i][j] = true;
				}
			}
		}
	}

	//�ǵؿɼ��Ի���
	for (int i = 1; i <= SatNum; i++)
	{
		for (int j = 0; j < StateNum; j++)
		{
			int k = 0;
			for (; k < StateLength; k++)
			{
				if (VecIsJnx[j * StateLength + k][i] == false && VecStateIsJnx[j][i] == false)
					break;
			}
			if(k == StateLength)
				VecStateIsJnx[j][i] = true;
		}
	}
}


void PrintSatSatAccess(vector<vector<bool>>& VecSatSat, vector<bool>& VecJnx)
{
	cout << "��ӡ��ǰ״̬�µ��Ǽ�ɼ������" << endl;
	for (int i = 1; i <= SatNum; i++)
	{
		cout << setw(6) << left << i;
		for (int j = 1; j <= SatNum; j++)
		{
			if (VecSatSat[i][j] == true)
			{
				cout << setw(6) << left << j;
			}
		}
		cout << endl;
	}
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
}


void PrintSatLandAccess(vector<bool>& VecJnx)
{
	cout << "��ӡ��ǰ״̬�µľ��������" << endl;
	for (int i = 1; i < VecJnx.size(); i++)
	{
		if (VecJnx[i] == true)
			cout << setw(6) << left << i;
	}
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
}


void GetSatLandInfo()
{
	string meo_meo = "MM.csv";
	string meo_geo = "GM.csv";
	string land_meo = "LM.csv";
	string land_geo = "L_G.csv";

	InitialData();

	GetSatSatAccess(meo_meo);
	GetSatSatAccess(meo_geo);
	GetSatLandAccess(land_meo);
	GetSatLandAccess(land_geo);

	PrintSatLandAccess(VecIsJnx[0]);
	PrintSatSatAccess(VecSatToSat[0], VecIsJnx[0]);

}


bool JudgeAccess(vector<vector<bool>>& v1, vector<vector<bool>>& v2)
{
	for (int i = 1; i <= SatNum - 6; i++)
	{
		for (int j = 1; j <= SatNum; j++)
		{
			if (v1[i][j] != v2[i][j])
				return false;
		}
	}
	return true;
}


int GetAccessPoint(vector<vector<vector<bool>>>& vec, int CurPoint, int StateNum)
{
	for (int i = CurPoint + 1; i < StateNum; i++)
	{
		if (JudgeAccess(vec[CurPoint], vec[i]) == false)
			return i;
	}
	return StateNum;
}


void GetAnsMeo(vector<vector<vector<bool>>>& vec, int StateNum)
{
	vector<int> VecMeoAccessNum(StateNum);			//MEO11�ڲ�ͬ��ģ�µĿɼ���������
	map<int, int> MapSatScale;						//MEO11�ڲ�ͬ��ģ�¿ɼ��ǵ�ռ��
	map<int, int> MapDurationScale;					//MEO11�ڲ�ͬ��ģ�²�ͬ���ȵı���
	int TotalSatNum = 0;

	ofstream out("AccessSatNum.txt");
	//ͳ�ƿɼ����ǵ�����
	for (int i = 0; i < StateNum; i++)
	{
		out << setw(6) << left << i;
		int cnt = 0;
		for (int j = 1; j <= SatNum; j++)
		{
			if (VecSatToSat[i][1][j] == true)
				cnt++;
		}
		VecMeoAccessNum[i] = cnt;
		MapSatScale[cnt]++;
		TotalSatNum += cnt;
		out << setw(6) << left << cnt << endl;
	}
	out.close();

	ofstream outfile("SatNumSacle.txt");
	//ͳ�ƿɼ�����������ռ�����
	for (auto it : MapSatScale)
	{
		outfile << setw(6) << left << it.first;
		outfile << setw(6) << left << double((it.first*it.second)) / TotalSatNum << endl;
	}
	outfile.close();

	ofstream outfile1("DurationSacle.txt");
	//ͳ�Ʋ�ͬʱ����ռ�����
	int CurPoint = 0;
	int TotalStates = 0;
	while (CurPoint < StateNum - 1)
	{
		int NextPoint = GetAccessPoint(vec, CurPoint, StateNum);
		if (NextPoint == StateNum)
			MapDurationScale[StateNum - CurPoint]++;
		else
		{
			MapDurationScale[NextPoint - CurPoint]++;
			CurPoint = NextPoint;
		}
		TotalStates++;
	}

	for (auto it : MapDurationScale)
	{
		outfile1 << setw(6) << left << it.first;
		outfile1 << setw(6) << left << double(it.second) / TotalStates << endl;
	}
	outfile1.close();
}


void SaveALlInfo()
{
	int StateNum = PeriodNum / StateLength;
	GetStateAccess(StateLength);
	DivideState(StateNum);
	string filename1 = "E:\\Code\\git\\C--\\�Ǽ���·\\���ǿɼ��Ծ���\\";
	string filename2 = "E:\\Code\\git\\C--\\�Ǽ���·\\������\\";
	string filename3 = "E:\\Code\\git\\C--\\�Ǽ���·\\��̬��·\\";
	ofstream file;

	for (int i = 0; i < StateNum; i++)
	{
		file.open(filename1 + to_string(i) + ".txt");

		for (int j = 1; j <= SatNum; j++)
		{
			for (int k = 1; k <= SatNum; k++)
			{
				file << setw(6) << left << VecStateSatSat[i][j][k];
			}
			file << endl;
		}
		file.close();
	}
	
	for (int i = 0; i < StateNum; i++)
	{
		file.open(filename2 + to_string(i) + ".txt");
		for (int j = 1; j <= SatNum; j++)
		{
			if (VecStateIsJnx[i][j] == true)
				file << setw(6) << left << j;
		}
		file.close();
	}
	
	file.open(filename3 + "staticlinks.txt");
	for (int i = 1; i <= SatNum - 6; i++)
	{
		for (auto it : VecStaticLinks[i])
			file << setw(6) << left << it;
		file << endl;
	}
	file.close();

	//GetAnsMeo(VecStateSatSat, StateNum);
}


