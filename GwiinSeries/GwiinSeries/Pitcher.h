#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Player.h"
using namespace std;
enum Åõ¼ö½ºÅÈ { BBT, singleT, doubleT, tripleT, HRT, SOT, FOT, GOT, NP, SAP, SSP};
class Pitcher :public Player
{
public:
	Pitcher();
	Pitcher(map<string, vector<double>> playerinfo, string player);
	virtual void setCondition();
	virtual void setStat(map<string, vector<double>> playerinfo, string player);
	virtual vector<double> getStat() const;

//	int getNP() const;
private:
	vector<double> PitcherStat;

};

