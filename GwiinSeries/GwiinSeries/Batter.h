#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
class Batter
{
public:
	void setCondition();
	void setStat(map<string, vector<double>> playerinfo, string player);
	string getname();
	double getBBP();
	double getsingleP();
	double getdoubleP();
	double gettripleP();
	double getHRP();
	double getSOP();
	double getFOP();
	double getGOP();
	double getcondition();
private:
	string name;
	double BBP;
	double singleP;
	double doubleP;
	double tripleP;
	double HRP;
	double SOP;
	double FOP;
	double GOP;
	double condition;
};

