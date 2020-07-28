#include "Input.h"
#include "CurrentPlayer.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
Input Batting;
Input Fielding;
Input Running;
Input Pitching;
Input Catching;
CurrentPlayer PlayBall;
void init() {
	string hteam, ateam;
	cout << "팀명(홈)을 입력하세요: ";
	cin >> hteam;
	PlayBall.setHomeTeam(hteam);
	cout << "팀명(원정)을 입력하세요: ";
	cin >> ateam;
	PlayBall.setAwayTeam(ateam);
	//**********투수 입력**********
	string hpitch, apitch;
	//홈 선발
	cout << "홈팀 선발투수: ";
	cin >> hpitch;
	auto iter1 = Pitching.getPlayerInfo().find(hpitch);
	while (iter1 == Pitching.getPlayerInfo().end()) {
		cout << "다시 입력하세요: ";
		cin >> hpitch;
		iter1 = Pitching.getPlayerInfo().find(hpitch);
	}
	//HomePitcher 설정, 현재 투수 설정
	PlayBall.setHomePitcher(hpitch);
	PlayBall.setCurrentPitcher(hpitch);
	//원정 선발
	cout << "원정팀 선발투수: ";
	cin >> apitch;
	auto iter2 = Pitching.getPlayerInfo().find(apitch);
	while (iter2 == Pitching.getPlayerInfo().end()) {
		cout << "다시 입력하세요: ";
		cin >> apitch;
		iter2 = Pitching.getPlayerInfo().find(apitch);
	}
	//AwayPitcher 설정
	PlayBall.setAwayPitcher(apitch);

	//*********타자입력*******
	vector<string> hbatVec, abatVec;
	//홈
	for (int i = 0; i < 9; i++) {
		cout << "홈팀 " << i + 1 << "번 타자: ";
		string hbat;
		cin >> hbat;
		auto iter3 = Batting.getPlayerInfo().find(hbat);
		while (iter3 == Batting.getPlayerInfo().end()) {
			cout << "다시 입력하세요: ";
			cin >> hbat;
			iter3 = Batting.getPlayerInfo().find(hbat);
		}
		//현재타자 목록
		hbatVec.push_back(hbat);
	}
	//홈팀 타순 설정
	PlayBall.setHomeBatter(hbatVec);

	//원정
	for (int i = 0; i < 9; i++) {
		cout << "원정팀 " << i + 1 << "번 타자: ";
		string abat;
		cin >> abat;
		auto iter4 = Batting.getPlayerInfo().find(abat);
		while (iter4 == Batting.getPlayerInfo().end()) {
			cout << "다시 입력하세요: ";
			cin >> abat;
			iter4 = Batting.getPlayerInfo().find(abat);
		}
		//현재타자 목록
		abatVec.push_back(abat);
	}
	//원정팀 타순 설정 및 현재 타자 설정
	PlayBall.setAwayBatter(abatVec);
	PlayBall.setCurrentBatter(abatVec[0]);

	//정보 저장



	//정보 프린트
	//원정팀 정보 프린트
	cout << PlayBall.getAwayTeam() << endl;
	cout << "선발투수: " << PlayBall.getAwayPitcher() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "번 타자: " << PlayBall.getAwayBatter()[i] << endl;
	}
	cout << endl;
	//홈팀 정보 프린트
	cout << PlayBall.getHomeTeam() << endl;
	cout << "선발투수: " << PlayBall.getHomePitcher() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "번 타자: " << PlayBall.getHomeBatter()[i] << endl;
	}
	cout << endl;

}


int main() {
	//선수정보 저장
	vector<Input> SumBatterInfo;

	//타자 정보 (아규먼트 변경 필요)
	Batting.setPlayerInfo("test.txt", 6);
	Fielding.setPlayerInfo("test.txt", 6);
	Running.setPlayerInfo("test.txt", 6);
	SumBatterInfo.push_back(Batting);
	SumBatterInfo.push_back(Fielding);
	SumBatterInfo.push_back(Running);
	enum BFR { 타격, 수비, 주루 };

	//투수 정보 (아규먼트 변경 필요)
	Pitching.setPlayerInfo("test.txt", 6);
	//포수 정보 (아규먼트 변경 필요)
	Catching.setPlayerInfo("test.txt", 6);

	init();





	return 0;
}