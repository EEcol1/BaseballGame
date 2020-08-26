#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Player.h"
using namespace std;
enum 투수스탯 { BBT, singleT, doubleT, tripleT, HRT, SOT, FOT, GOT, NP, 투수도루시도 };
class Pitcher :public Player
{
public:
	Pitcher();
	Pitcher(map<string, vector<double>> playerinfo, string player);
	virtual void setCondition();
	virtual void setStat(map<string, vector<double>> playerinfo, string player);
	virtual vector<double> getStat() const;
	void needChange();

//	int getNP() const;
private:
	vector<double> PitcherStat;

};

