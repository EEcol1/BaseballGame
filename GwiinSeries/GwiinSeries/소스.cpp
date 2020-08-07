#include "Input.h"
#include "CurrentPlayer.h"
#include "Scoreboard.h"
#include "Random.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
Input Batting;
Input Fielding;
Input Running;
Input Pitching;
Input Catching;
CurrentPlayer TeamInfo;
//얘네 전역변수로 놓고 써도 되나
/*auto BatterInfo = Batting.getPlayerInfo();
auto FielderInfo = Fielding.getPlayerInfo();
auto RunningInfo = Running.getPlayerInfo();
auto PitcherInfo = Pitching.getPlayerInfo();
auto CatchingInfo = Catching.getPlayerInfo();*/

void init() {
	string hteam, ateam;
	cout << "팀명(홈)을 입력하세요: ";
	cin >> hteam;
	TeamInfo.setHomeTeam(hteam);
	cout << "팀명(원정)을 입력하세요: ";
	cin >> ateam;
	TeamInfo.setAwayTeam(ateam);
	//**********투수 입력**********
	string hpname, apname;
	auto PitcherInfo = Pitching.getPlayerInfo();
	//홈 선발
	cout << "홈팀 선발투수: ";
	cin >> hpname;
	auto iter1 = PitcherInfo.find(hpname);
	while (iter1 == PitcherInfo.end()) {
		cout << "다시 입력하세요: ";
		cin >> hpname;
		iter1 = PitcherInfo.find(hpname);
	}

	//HomePitcher 설정, (현재 투수 설정)
	//TeamInfo.setHomePitcher(hpitch);
	//TeamInfo.setCurrentPitcher(hpitch);
	Pitcher hpitcher(PitcherInfo, hpname);
	TeamInfo.setHomePitcher(hpitcher);

	//원정 선발
	cout << "원정팀 선발투수: ";
	cin >> apname;
	auto iter2 = PitcherInfo.find(apname);
	while (iter2 == PitcherInfo.end()) {
		cout << "다시 입력하세요: ";
		cin >> apname;
		iter2 = PitcherInfo.find(apname);
	}
	//AwayPitcher 설정
	//TeamInfo.setAwayPitcher(apitch);
	Pitcher apitcher(PitcherInfo, apname);
	TeamInfo.setAwayPitcher(apitcher);

	//*********타자입력*******
	vector<Batter> hbatVec, abatVec;
	auto BatterInfo = Batting.getPlayerInfo();
	//홈
	for (int i = 0; i < 9; i++) {
		cout << "홈팀 " << i + 1 << "번 타자: ";
		string hbname;
		cin >> hbname;
		auto iter3 = BatterInfo.find(hbname);
		while (iter3 == BatterInfo.end()) {
			cout << "다시 입력하세요: ";
			cin >> hbname;
			iter3 = BatterInfo.find(hbname);
		}
		//현재타자 목록
		//hbatVec.push_back(hbat);
		Batter hbat(BatterInfo,hbname);
		hbatVec.push_back(hbat);
	}
	//홈팀 타순 설정
	TeamInfo.setHomeBatter(hbatVec);

	//원정
	for (int i = 0; i < 9; i++) {
		cout << "원정팀 " << i + 1 << "번 타자: ";
		string abname;
		cin >> abname;
		auto iter4 = BatterInfo.find(abname);
		while (iter4 == BatterInfo.end()) {
			cout << "다시 입력하세요: ";
			cin >> abname;
			iter4 = BatterInfo.find(abname);
		}
		//현재타자 목록
		Batter abat(BatterInfo,abname);
		abatVec.push_back(abat);
	}
	//원정팀 타순 설정 및 (현재 타자 설정)
	TeamInfo.setAwayBatter(abatVec);

	//정보 저장



	/*//정보 프린트
	//원정팀 정보 프린트
	cout << TeamInfo.getAwayTeam() << endl;
	cout << "선발투수: " << TeamInfo.getAwayPitcher().getname() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "번 타자: " << TeamInfo.getAwayBatter()[i].getname() << endl;
	}
	cout << endl;
	//홈팀 정보 프린트
	cout << TeamInfo.getHomeTeam() << endl;
	cout << "선발투수: " << TeamInfo.getHomePitcher().getname() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "번 타자: " << TeamInfo.getHomeBatter()[i].getname() << endl;
	}
	cout << endl;
	*/
}


int main() {
	//선수정보 저장
	vector<Input> SumBatterInfo;

	//타자 정보 (아규먼트 변경 필요)
	Batting.setPlayerInfo("test.txt", 8);
	Fielding.setPlayerInfo("test.txt", 8);
	Running.setPlayerInfo("test.txt", 8);
	SumBatterInfo.push_back(Batting);
	SumBatterInfo.push_back(Fielding);
	SumBatterInfo.push_back(Running);
	enum BFR { 타격, 수비, 주루 };

	//투수 정보 (아규먼트 변경 필요)
	Pitching.setPlayerInfo("test.txt", 8);
	//포수 정보 (아규먼트 변경 필요)
	Catching.setPlayerInfo("test.txt", 8);

	init();
	Scoreboard Game;
	Random random;
	enum 숫자계산 { BB, SIN, DOU, TRI, HR, SO, FO, GO };
	//1-9회 ok 10-12회:초 공격이면 그대로 진행, 말공격이면 
	enum 초말{초,말};
	bool previousState = 말;
	int hometasoon = 0;
	int awaytasoon = 0;
	while (!Game.isGameEnd()) {
		//공수교대시 이닝(초,말) 표시
		if (previousState != Game.getInnHA())
			Game.printInnInfo();
		//초 공격 시
		if (Game.getInnHA() == 초) {
			//현재 타자,현재투수 설정
			Game.setCurrentBatter(TeamInfo.getAwayBatter()[awaytasoon]);
			Game.setCurrentPitcher(TeamInfo.getHomePitcher());
			//현재 타자,투수 출력
			Game.printCurrentInfo();
			Game.setPercentage();
		}
		int number = random.hitBall();
		//볼넷
		if (number < Game.getPercentage()[BB]) {
			//1루 비어있으면 그냥 추가, 1루 안 비어있으면 한 칸씩 앞으로


		}
		if (number <= Game.getPercentage()[SIN]) {
			//안타
			//1베이스씩 진루, 확률에 의해 추가진루
		}
		if (number <= Game.getPercentage()[DOU]) {
			//2루타
			//2베이스씩 진루, 확률에 의한 추가진루
		}
		if (number <= Game.getPercentage()[TRI]) {
			//3루타
			//싹쓸이
		}
		if (number <= Game.getPercentage()[HR]) {
			//HR
			//싹쓸이
		}
		if (number <= Game.getPercentage()[SO]) {
			//삼진
			cout << "삼진~~" << endl;
			Game.plusOutCount();
		}
		if (number <= Game.getPercentage()[FO]) {
			//플라이
			cout << "플라이 아웃" << endl;
			Game.plusOutCount();
			//일정확률로 추가진루
		}
		if (number <= 10000) {
			cout << "땅볼" << endl;
			Game.plusOutCount();
			//일정확률로 추가진루, 일정확률로 병살타.
		}

		

		

		bool previousState = Game.getInnHA();
	}



	return 0;
}