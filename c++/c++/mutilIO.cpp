#include"mutiIO.h"

void mutilIO()
{
	vector<string> name;
	vector<vector<int>> value;
	string str;
	getline(cin, str);
	while (str.size())
	{
		istringstream is(str);
		vector<string> ar;
		while (is >> str)
		{
			ar.push_back(str);
		}
		name.push_back(ar[0]);
		value.push_back(vector<int>{stoi(ar[1]), stoi(ar[2])});
		getline(cin, str);
	}
	for (int i = 0; i < name.size(); i++)
		cout << name[i] << " " << value[i][0] << " " << value[i][1] << endl;
}


void GetFile()
{
	ifstream infile;
	
	//����1������eof�ж��Ƿ��ļ�ĩβ
	int item1;
	infile.open("demo.txt");
	cout << "����һ�Ľ�����£�" << endl;
	vector<int> res1;
	while (!infile.eof())
	{
		infile >> item1;
		res1.push_back(item1);
	}
	infile.close();
	for (auto it : res1)
		cout << it << " ";
	cout << endl << endl;


	//����2������infile�������е������Ƿ�Ϊ����
	cout << "����һ�Ľ�����£�" << endl;
	infile.open("demo.txt");
	int item2;
	vector<int> res2;
	while (infile >> item2)
	{
		res2.push_back(item2);
	}
	infile.close();

	for (auto it : res2)
		cout << it << " ";
	cout << endl << endl;
}


