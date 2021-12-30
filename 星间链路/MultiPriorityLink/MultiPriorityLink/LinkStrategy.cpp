#include"LinkStrategy.h"
#include <algorithm>
#include<queue>

vector<satelite> jnx;
vector<satelite> jwx;
vector<bool> VecIsJnx(SatNum + 1);											//卫星属性
vector<satelite> VecSat(SatNum + 1);										//存放所有的每个卫星
vector<vector<bool>> VecSatToSat(SatNum + 1, vector<bool>(SatNum + 1));		//存放当前卫星之间的可见性
vector<vector<int>> VecStaticLinks(SatNum - 5, vector<int>(8));				//存放每个卫星的永久可见星

int slot = 20;																//时隙数
vector<vector<int>> TimeSlotTable(SatNum + 1, vector<int>(slot + 10));		//时隙表
										

void GetAllInfo()
{
	ifstream infile;
	string filename1 = "E:\\Code\\git\\C--\\星间链路\\卫星可见性矩阵\\0.txt";
	string filename2 = "E:\\Code\\git\\C--\\星间链路\\境内星\\0.txt";
	string filename3 = "E:\\Code\\git\\C--\\星间链路\\静态链路\\staticlinks.txt";
	
	infile.open(filename1);
	for (int i = 1; i <= SatNum; i++)
	{
		for (int j = 1; j <= SatNum; j++)
		{
			int it;
			infile >> it;
			it == 1 ? VecSatToSat[i][j] = true : VecSatToSat[i][j] = false;
		}
	}
	infile.close();

	infile.open(filename2);
	int item;
	while (infile >> item)
	{
		VecIsJnx[item] = true;
	}
	infile.close();

	infile.open(filename3);
	for (int i = 1; i <= SatNum - 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			infile >> VecStaticLinks[i][j];
		}
	}
	infile.close();

	PrintSatSatAccess(VecSatToSat, VecIsJnx);
	PrintSatLandAccess(VecIsJnx);
}

void InitialSatInfo()
{
	for (int i = 1; i <= SatNum; i++)
	{
		VecSat[i].number = i;
		for (int j = 1; j <= SatNum; j++)
		{
			if (VecSatToSat[i][j] == 1)
			{
				if (VecIsJnx[j] == true)
				{
					VecSat[i].InNum++;
					VecSat[i].InSat.push_back(j);
				}
				else
				{
					VecSat[i].OutNum++;
					VecSat[i].OutSat.push_back(j);
				}
			}
		}
	}
}

static bool CompareIn(satelite sat1, satelite sat2)
{
	if (sat1.OutNum == sat2.OutNum)
		return sat1.InNum > sat2.InNum;
	return sat1.OutNum < sat2.OutNum;
}

static bool CompareOut(satelite sat1, satelite sat2)
{
	if (sat1.InNum == sat2.InNum)
		return sat1.OutNum > sat2.OutNum;
	return sat1.InNum < sat2.InNum;
}

void CreatLink()
{
	vector<satelite> priorSat;
	for (int i = 1; i <= SatNum; i++)
	{
		if (VecIsJnx[i] == true)
			jnx.push_back(VecSat[i]);
		else
			jwx.push_back(VecSat[i]);
	}
	sort(jwx.begin(), jwx.end(), CompareOut);

	for(auto it : jwx)
	{
		int from = it.number;
		int in = 0;
		int out = 0;
		int _in = 0;
		int _out = 0;
		int inSz = it.InSat.size();
		int outSz = it.OutSat.size();
		if (from > 24)
			continue;
		for (int i = 0; i < slot + 10; i++)
		{
			int cnt = 0;
			if (i % 3 == 0 || i % 3 == 1)
			{
				while (1)
				{
					int to = it.InSat[in++%inSz];
					if (TimeSlotTable[to][i] == 0)
					{
						TimeSlotTable[from][i] = to;
						TimeSlotTable[to][i] = from;
						break;
					}
					cnt++;
					if (cnt == inSz)
					{
						int outCnt = 0;
						while (1)
						{
							int to = it.OutSat[_out++%outSz];
							if (TimeSlotTable[to][i] == 0)
							{
								TimeSlotTable[from][i] = to;
								TimeSlotTable[to][i] = from;
								break;
							}
							outCnt++;
							if (outCnt == outSz)
								break;
						}
						break;
					}
				}
			}
			else
			{
				while (1)
				{
					int to = it.OutSat[out++%outSz];
					if (TimeSlotTable[to][i] == 0)
					{
						TimeSlotTable[from][i] = to;
						TimeSlotTable[to][i] = from;
						break;
					}
					cnt++;
					if (cnt == inSz)
					{
						int inCnt = 0;
						while (1)
						{
							int to = it.InSat[_in++%inSz];
							if (TimeSlotTable[to][i] == 0)
							{
								TimeSlotTable[from][i] = to;
								TimeSlotTable[to][i] = from;
								break;
							}
							inCnt++;
							if (inCnt == inSz)
								break;
						}
						break;
					}
				}
			}
		}
		//PrintTimeSlotTable();
	}
}

void PrintTimeSlotTable()
{
	for (int j = 1; j <= SatNum - 6; j++)
	{
		//if (VecIsJnx[j] == true)
			//continue;
		cout << j << "	";
		for (int i = 0; i < slot; i++)
		{	
			cout << TimeSlotTable[j][i] << "	";
		}
		cout << endl;
	}
	
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
}

void GetJwxLinks()
{
	for (auto it : jwx)
	{
		int from = it.number;
		if (from > 24)
			continue;
		set<int> sat;
		for (int i = 0; i < slot; i++)
			sat.insert(TimeSlotTable[from][i]);
		cout << from << " " << sat.size() << endl;
	}
}

void CalJump()
{
	int jump1 = 0;
	int jump2 = 0;
	int jump3 = 0;
	for (int i = 0; i < slot; i++)
	{
		for (auto it : jwx)
		{
			int from = it.number;
			if (from > 24)
				continue;
			//第1个时隙与境内星建链
			int to = TimeSlotTable[from][i];
			if (VecIsJnx[to] == true)
			{
				jump1++;
			}
			//第二个时隙与境内星建链
			else
			{
				int to1 = TimeSlotTable[from][i + 1];
				int to2 = TimeSlotTable[to][i + 1];
				if (VecIsJnx[to1] || VecIsJnx[to2])
				{
					jump2++;
				}
				else
				{
					jump3++;
					cout << from << " 时隙为：" << i << endl;
					cout << "存在三跳的情况，请重新规划链路" << endl;
				}
			}
		}
	}
	double jump = jump1 + jump2 + jump3;
	double avgJump = (jump1 + jump2 * 2 + jump3 * 3) / jump;
	cout << "所有的跳数情况如下：" << endl;
	cout << "一跳情况：" << jump1 << "占比：" << jump1 / jump << endl;
	cout << "二跳情况：" << jump2 << "占比：" << jump2 / jump << endl;
	cout << "三跳情况：" << jump3 << "占比：" << jump3 / jump << endl;
	cout << "平均跳数为：" << avgJump << endl;
}
