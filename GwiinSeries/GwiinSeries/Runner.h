#pragma once
#include "Player.h"
#include "Batter.h"
enum renum{addBaseP,stealAttP,stealP};
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

