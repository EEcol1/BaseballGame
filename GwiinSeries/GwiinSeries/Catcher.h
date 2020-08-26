#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Player.h"
enum �������� {��������õ�,�����������,�����������};
class Catcher:public Player
{public:
	Catcher();
	Catcher(map<string, vector<double>> playerinfo, string player);
	virtual void setCondition();
	virtual void setStat(map<string, vector<double>> playerinfo, string player);
	virtual vector<double> getStat() const;
private:
	vector<double> CatcherStat;
};

