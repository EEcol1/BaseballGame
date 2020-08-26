#pragma once
#include "Player.h"
#include "Batter.h"
enum 주루스탯 { addBaseP, 주자도루시도, 주자도루성공 };
class Runner:public Player
{public:
	Runner();
	Runner(Batter hitter);
	Runner(map<string, vector<double>> playerinfo, string player);
	virtual void setCondition();
	virtual void setStat(map<string, vector<double>> playerinfo, string player);
	virtual vector<double> getStat() const;

private:
	//int RunnerPosition;
	//double addBaseP;
	//double stealAttP;
	//double stealP;
	vector<double> RunnerStat;
};

