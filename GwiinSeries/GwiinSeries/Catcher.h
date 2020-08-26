#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Player.h"
enum 포수스탯 {포수도루시도,포수도루허용,포수폭투허용};
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

