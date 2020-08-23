#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Player.h"
using namespace std;
enum Å¸ÀÚ½ºÅÈ { BBP, singleP, doubleP, tripleP, HRP, SOP, FOP, GOP };
class Batter: public Player 
{
public:
	Batter();
	Batter(map<string, vector<double>> playerinfo, string player);
	virtual void setCondition();
	virtual void setStat(map<string, vector<double>> playerinfo, string player);
	virtual vector<double> getStat() const;
	
	
	
private:
	vector<double> BatterStat;
};

