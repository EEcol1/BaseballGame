#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std;
class Player
{public:
	string getName() const;
	virtual void setCondition()=0;
	virtual void setStat(map<string, vector<double>> playerinfo, string player)=0;
	virtual vector<double> getStat() const=0;


protected:
	string Name;
	double Condition;
	
};

