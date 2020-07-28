#pragma once
#include <vector>
#include <string>
using namespace std;
class CurrentPlayer
{
public:
	string getHomeTeam();
	string getAwayTeam();
	void setHomeTeam(string hteam);
	void setAwayTeam(string ateam);
	string getHomePitcher();
	string getAwayPitcher();
	void setHomePitcher(string hpitch);
	void setAwayPitcher(string apitch);
	vector<string> getHomeBatter();
	vector<string> getAwayBatter();
	void setHomeBatter(vector<string> hbatvec);
	void setAwayBatter(vector<string> abatvec);
	string getCurrentPitcher();
	string getCurrentBatter();
	vector<string> getCurrentFielder();
	void setCurrentPitcher(string cpitch);
	void setCurrentBatter(string cbat);
	void setCurrentFielder(vector<string> cfield);
private:
	string HomeTeam;
	string AwayTeam;
	string HomePitcher;
	string AwayPitcher;
	vector<string> HomeBatter;
	vector<string> AwayBatter;
	string CurrentPitcher;
	string CurrentBatter;
	vector<string> CurrentFielder;
	//정보는 어디다 저장할겨???

};

