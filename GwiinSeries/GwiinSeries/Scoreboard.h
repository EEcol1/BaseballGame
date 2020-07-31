#pragma once
class Scoreboard
{
public:
	//아웃카운트
	void plusOutCount();
	int getOutCount() const;
	//이닝
	void plusInnNum();
	int getInnNum() const;
	void setInnHA(bool homeaway);
	bool getInnHA() const;
	//주자상황
	void setBaseSit(bool base1, bool base2, bool base3);
	bool getBase1() const;
	bool getBase2() const;
	bool getBase3() const;
	//점수
	void setHomeScore(int homescore);
	void plusHomeScore(int plusscore);
	int getHomeScore() const;
	void setAwayScore(int awayscore);
	void plusAwayScore(int plusscore);
	int getAwayScore() const;
	//투구수
	void setCurrentPitcherNP(int NP);
	void plusCurrentPitcherNP(int NP);
	int getCurrentPitcherNP() const;

	void setHomePitcherNP(int NP);
	int getHomePitcherNP() const;
	void setAwayPitcherNP(int NP);
	int getAwayPitcherNP() const;
	//타자 및 수비 및 주자에 대한 정보

private:
	//아웃카운트
	int OutCount;
	//이닝
	//초 공격vs 말 공격 1이면 말 공격,0이면 초 공격
	int InnNum;
	bool InnHA;
	//주자 상황 *주자 INFO도 들어가야 함.
	bool BaseSit[3];
	//홈,어웨이 점수
	int HomeScore;
	int AwayScore;
	//투구수
	int HomePitcherNP;
	int AwayPitcherNP;
	int CurrentPitcherNP;
	//현재 투수 및 현재 타자에 대한 정보
	/*
	자료형 미결정
	CurrentBatter
	CurrentBatterInfo[n]: 타율,장타율 등 기록이 담겨야해.
	CurrentPitcher
	CurrentPitcherInfo[n]: 여러가지 기록들이 담겨야해
	CurrentFielder[n]
	CurrentFielderInfo[n][n]
	+주자 INFO 아마도 CurrentRunner[3]
	*/
};

