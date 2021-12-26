#include "RouteStrategy.h"
#include"AccessDate.h"
#include"LinkStrategy.h"
#include<iostream>
#include<vector>
using namespace std;

extern vector<vector<bool>> TimeSlotTable;
extern int slot;
extern vector<satelite> jwx;
extern vector<bool> VecIsJnx;

vector<vector<int>> RouterTable(SatNum + 1, vector<int>(slot));
