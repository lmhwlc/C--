#include<iostream>
#include"AccessDate.h"
#include<fstream>
#include<string>
#include"LinkStrategy.h"
using namespace std;


int main()
{
	GetSatLandInfo();
	SaveALlInfo();

	//GetAllInfo(1371);
	//InitialSatInfo();

	//CreatLink();
	//while (!JudgeJump())
	//{
	//	CreatLink();
	//	PrintTimeSlotTable();
	//}

	//PrintTimeSlotTable();

	//GetJwxLinks();
	//CalJump();

	GetAllSlot(8639);
	cout << "hello world !" << endl;
	cout << endl;
	cout << endl;
	getchar();
}