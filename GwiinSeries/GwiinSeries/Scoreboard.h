#pragma once
#include <iostream>
#include <vector>
#include "Batter.h"
#include "Pitcher.h"
#include "Fielder.h"
#include "Runner.h"
#include "Catcher.h"
#include "CurrentPlayer.h"
using namespace std;

class Scoreboard
{
public:
	//아웃카운트
	Scoreboard();
	Scoreboard(CurrentPlayer teaminfo);
	bool isGameEnd();
	void changeInning();

	void plusOutCount();
	void  printOutCount() const;
	//이닝

	void printInnInfo() const;
	bool getInnHA() const;
	//주자상황
	
	void moveRunner(int a); 
	void addRunner(int a);

	//점수
	void plusScore(int plusscore);
	void printScore() const;
	
	//투수 타자
	void printCurrentInfo() const;
	void setCurrentBatter(Batter cbat);
	void setCurrentPitcher(Pitcher cpit);
	//확률
	void setPercentage();
	vector<int> getPercentage() const;
	//투구수

	void setNumberPitch(Pitcher AwayPitcher,Pitcher HomePitcher);
	void updateNumberPitch();
	//타자 및 수비 및 주자에 대한 정보
	
	//
	vector<int> getBallNumber();
private:
	//아웃카운트
	int OutCount;
	//이닝
	//초 공격vs 말 공격 1이면 말공격,0이면 초 공격
	int InnNum;
	bool InnHA;
	//주자 상황 *주자 INFO도 들어가야 함.
	vector<Runner> BaseSit;
	//홈,어웨이 점수
	int Score[2];
	//투구수
	int NumberPitch[2];
	
	Batter CurrentBatter;
	Pitcher CurrentPitcher;

	vector<int> Percent;

	//Catcher CurrentCatcher;
	//Fielder CurrentFielder;

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

