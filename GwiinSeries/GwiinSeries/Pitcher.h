#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
class Pitcher
{
public:
	void setCondition();
	void setStat(map<string, vector<double>> playerinfo, string player);
	string getname();
	double getBBT();
	double getsingleT();
	double getdoubleT();
	double gettripleT();
	double getHRT();
	double getSOT();
	double getFOT();
	double getGOT();
	double getcondition();
private:
	string name;
	double BBT;
	double singleT;
	double doubleT;
	double tripleT;
	double HRT;
	double SOT;
	double FOT;
	double GOT;
	double condition;
};

