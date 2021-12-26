#include<iostream>
#include"AccessDate.h"
#include<fstream>
#include<string>
#include"LinkStrategy.h"
using namespace std;


int main()
{
	//GetSatLandInfo();
	//SaveALlInfo();

	GetAllInfo();
	InitialSatInfo();

	CreatLink();

	PrintTimeSlotTable();
	
	GetJwxLinks();
	CalJump();

	cout << "hello world !" << endl;
	cout << endl;
	cout << endl;
	getchar();
}