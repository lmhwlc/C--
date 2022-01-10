#include"AccessDate.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
using namespace std;

//传感器
vector<string> VecSatName{ "", "11","12" ,"13" ,"14" ,"15","16","17","18",
							"21","22" ,"23" ,"24" ,"25","26","27","28",
							"31","32" ,"33" ,"34" ,"35","36","37","38",
							"G1","G2", "G3", "G4", "G5", "G6" };

map<string, int> MapCraftIndex;
vector<vector<bool>> VecIsJnx;					//卫星属性
vector<vector<bool>> VecStateIsJnx;				//每个状态的卫星属性
vector<vector<vector<bool>>> VecSatToSat;		//星间可见性
vector<vector<vector<bool>>> VecLandToSat;		//星地可见性
vector<vector<vector<bool>>> VecStateSatSat;	//每个状态的星间可见性
vector<vector<vector<bool>>> VecStateLandSat;	//每个状态的星地可见性
vector<unordered_set<int>> VecStaticLinks;		//静态链路

int StateLength = 1;			//状态长度

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

	//按时隙划分的可见性
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

	//建立名字和索引的映射
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

		//记录持续可见卫星
		if (Duration == 8640)
			VecStaticLinks[FromSat].insert(ToSat);

		//记录非持续可见卫星
		/*
			每隔一分钟记录一次，一分钟内卫星持续可见，则当前的子帧内卫星为可见
			若一分钟内非持续可见，则当前子帧内卫星之间不可见
		*/
		int start = StartTime;
		if (start != StartTime)		//当前子帧不足一分钟
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

		//记录非持续可见卫星
		/*
			每隔一分钟记录一次，一分钟内卫星持续可见，则当前的子帧内卫星为可见
			若一分钟内非持续可见，则当前子帧内卫星之间不可见
		*/
		int start = StartTime;
		if (start != StartTime)		//当前子帧不足一分钟
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
	//星间可见性划分
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

	//星地可见性划分
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
	cout << "打印当前状态下的星间可见性情况" << endl;
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
	cout << "打印当前状态下的境内星情况" << endl;
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
	vector<int> VecMeoAccessNum(StateNum);			//MEO11在不同规模下的可见卫星数量
	map<int, int> MapSatScale;						//MEO11在不同规模下可见星的占比
	map<int, int> MapDurationScale;					//MEO11在不同规模下不同长度的比例
	int TotalSatNum = 0;

	ofstream out("AccessSatNum.txt");
	//统计可见卫星的数量
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
	//统计可见卫星数量的占比情况
	for (auto it : MapSatScale)
	{
		outfile << setw(6) << left << it.first;
		outfile << setw(6) << left << double((it.first*it.second)) / TotalSatNum << endl;
	}
	outfile.close();

	ofstream outfile1("DurationSacle.txt");
	//统计不同时长的占比情况
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
	string filename1 = "E:\\Code\\git\\C--\\星间链路\\卫星可见性矩阵\\";
	string filename2 = "E:\\Code\\git\\C--\\星间链路\\境内星\\";
	string filename3 = "E:\\Code\\git\\C--\\星间链路\\静态链路\\";
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


