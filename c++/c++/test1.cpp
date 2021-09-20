#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<sstream>
/*
	如何输入多行数据，形如：
	a 12 13
	b 14 15
	c 16 17

	...
	输入的行数未知
*/

void fun()
{
	vector<string> ar;
	vector<string> name;
	vector<vector<int>> value;
	string str;
	getline(cin, str);
	while (str.size())
	{
		istringstream is(str);
		while (is>>str)
		{
			ar.push_back(str);
		}
		name.push_back(ar[0]);
		value.push_back(vector<int>{stoi(ar[1]), stoi(ar[2])});
		getline(cin, str);
	}
	for (int i = 0; i < name.size(); i++)
		cout << name[i] << " " << value[i][0] << " " << value[i][1] << endl;
	cout << endl;
}


