#pragma once
#include <vector>
#include <string>
#include "Batter.h"
#include "Pitcher.h"
#include "Fielder.h"

using namespace std;
class CurrentPlayer
{
public:
	string getHomeTeam();
	string getAwayTeam();
	void setHomeTeam(string hteam);
	void setAwayTeam(string ateam);
	Pitcher getHomePitcher();
	Pitcher getAwayPitcher();
	void setHomePitcher(Pitcher hpitch);
	void setAwayPitcher(Pitcher apitch);
	vector<Batter> getHomeBatter();
	vector<Batter> getAwayBatter();
	void setHomeBatter(vector<Batter> hbatvec);
	void setAwayBatter(vector<Batter> abatvec);
	//사용 여부 고민중
	/*Pitcher getCurrentPitcher();
	Batter getCurrentBatter();
	vector<Fielder> getCurrentFielder();
	void setCurrentPitcher(string cpitch);
	void setCurrentBatter(string cbat);
	void setCurrentFielder(vector<string> cfield);*/
private:
	string HomeTeam;
	string AwayTeam;
	Pitcher HomePitcher;
	Pitcher AwayPitcher;
	vector<Batter> HomeBatter;
	vector<Batter> AwayBatter;

	//Pitcher CurrentPitcher;
	//Batter CurrentBatter;
	//vector<Fielder> CurrentFielder;
	//정보는 어디다 저장할겨???

};

