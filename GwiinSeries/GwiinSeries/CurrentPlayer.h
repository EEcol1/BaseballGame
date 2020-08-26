#pragma once
#include <vector>
#include <string>
#include "Batter.h"
#include "Pitcher.h"
#include "Catcher.h"


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
	void changeHomeBatter(Batter cbat, int num);
	void changeAwayBatter(Batter cbat, int num);
	Catcher getHomeCatcher();
	Catcher getAwayCatcher();
	void setHomeCatcher(Catcher hcat);
	void setAwayCatcher(Catcher acat);
private:
	string HomeTeam;
	string AwayTeam;
	Pitcher HomePitcher;
	Pitcher AwayPitcher;
	vector<Batter> HomeBatter;
	vector<Batter> AwayBatter;
	Catcher HomeCatcher;
	Catcher AwayCatcher;

	//Pitcher CurrentPitcher;
	//Batter CurrentBatter;
	//vector<Fielder> CurrentFielder;
	//정보는 어디다 저장할겨???

};

