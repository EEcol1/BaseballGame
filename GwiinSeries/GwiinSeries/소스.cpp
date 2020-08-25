#include "Input.h"
#include "CurrentPlayer.h"
#include "Scoreboard.h"
#include "Random.h"
#include "Base.h"
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
enum 초말 { 초, 말 };
enum 원정홈 { 원정, 홈 };
enum 숫자계산 { BB, SIN, DOU, TRI, HR, SO, FO, GO,DO};

int OutCount;
int InnNum;
bool InnHA;
vector<Runner> BaseSit;
int Score[2];
int NumberPitch[2];
int tasoon[2];
int& awaytasoon = tasoon[원정];
int& hometasoon = tasoon[홈];
Batter CurrentBatter;
Pitcher CurrentPitcher;
vector<int> Percent;
Base base;

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

	OutCount = 0;
	InnNum = 1;
	InnHA = 초;
	Score[초] = Score[말] = 0;
	//NumberPitch[원정] = TeamInfo.getAwayPitcher().getStat()[NP];
	//NumberPitch[홈] = TeamInfo.getHomePitcher().getStat()[NP];
	CurrentBatter = TeamInfo.getAwayBatter()[0];
	CurrentPitcher = TeamInfo.getHomePitcher();
	tasoon[원정] = tasoon[홈] = 0;
	//CurrentFielder 와 CurrentCatcher도 초기화

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
bool isGameEnd() {
	if (InnNum >= 13) return true;
	if (InnNum >= 9 && InnNum < 13) {
		if (InnHA == 초)
			return false;
		if (InnHA == 말 && (Score[말] > Score[초]))
			return true;
		if (InnHA == 말 && (Score[말] != Score[초]) && OutCount == 3)
			return true;
	}
	return false;
}
void changeInning() {

	OutCount = 0;
	if (InnHA == 말) {
		InnNum++;
		InnHA = !InnHA;
	}
	else
		InnHA = !InnHA;
	base.init();
	//CurrentPitcher,CurrentBatter, CurrentFielder, CurrentCatcher 변경.
	//추가 필요

}
void plusTasoon() {
	tasoon[InnHA]++;
	tasoon[InnHA] = tasoon[InnHA] % 9;
}
void plusOutCount() {
	OutCount++;
	//경기 종료 상황이면 종료
	if (isGameEnd()) return;
	//OutCount 꽉차면 이닝 교대
	if (OutCount == 3) changeInning();

}

void  printOutCount() {
	cout << OutCount << "아웃" << endl;
	//opengl 사용시
}
void printScoreInfo() {
	cout << TeamInfo.getAwayTeam() << Score[원정] << ":" << Score[홈] << TeamInfo.getHomeTeam() << endl;
}
void printInnInfo() {
	cout << endl;
	cout << InnNum << (InnHA == 초 ? "회초" : "회말") << endl;
}
void printCurrentInfo() {
	cout << "현재 투수: " << CurrentPitcher.getName() << endl;
	cout << "현재 타자: " << CurrentBatter.getName() << endl;
}
void printEndInfo() {
	cout << endl;
	cout << "경기종료" << endl;
	printScoreInfo();
	if (Score[원정] == Score[홈]) cout << "비김" << endl;
	else cout << (Score[원정] > Score[홈] ? TeamInfo.getAwayTeam() : TeamInfo.getHomeTeam()) << " 승리" << endl;

}
void setPercentage() {
	//다시 만들 것
	for (int i = 0; i < 8; i++) {
		Percent.push_back(0);
	}
	Percent[BB] = (int)(CurrentBatter.getStat()[BB] * CurrentPitcher.getStat()[BB] * 10000);
	int Inplay = 10000 - Percent[BB];
	for (int i = SIN; i <= SO; i++) {
		Percent[i] = Percent[i-1] + (int)(CurrentBatter.getStat()[i] * CurrentPitcher.getStat()[i] * Inplay);
	}
	int Out = 10000 - Percent[SO];
	Percent[FO] = Percent[SO]+(int)((CurrentBatter.getStat()[FO] + CurrentPitcher.getStat()[FO]) / 2.0 * Out);
	Percent[GO] = 10000;
}
/*void updateScore() {
	vector<Runner> temp;
	for (Runner Runners : BaseSit) {
		if (Runners.getRunnerPosition() < 4) {
			temp.push_back(Runners);
		}

	}
}*/
/*void moveRunner(int result) {
	if (result >= SIN && result <= HR) {
		for (Runner Runners:BaseSit) {
			Runners.plusRunnerPosition(result);
		}
	}
}*/
int main() {
	//타자 정보 (아규먼트 변경 필요)
	Batting.setPlayerInfo("batterstat.txt", 8);
	Fielding.setPlayerInfo("test.txt", 6);
	Running.setPlayerInfo("runnerstat.txt", 3);
	//투수 정보 (아규먼트 변경 필요)
	Pitching.setPlayerInfo("pitcherstat.txt", 8);
	//포수 정보 (아규먼트 변경 필요)
	Catching.setPlayerInfo("test.txt", 6);

	init();
	Random random;
	enum 숫자계산 { BB, SIN, DOU, TRI, HR, SO, FO, GO };
	//1-9회 ok 10-12회:초 공격이면 그대로 진행, 말공격이면 
	enum 초말{초,말};
	bool previousState = 말;
	auto RunnerStat = Running.getPlayerInfo();

	while (!isGameEnd()) {
		//공수교대시 이닝(초,말) 표시
		if (previousState != InnHA) {
			printInnInfo();
			previousState = InnHA;
		}



		//현재투수,현재 타자 설정
		if (InnHA == 초) {
			//현재 타자,현재투수 설정
			CurrentBatter=TeamInfo.getAwayBatter()[tasoon[원정]];
			CurrentPitcher=TeamInfo.getHomePitcher();
			
		}
		else if (InnHA == 말) {
			CurrentBatter = TeamInfo.getHomeBatter()[tasoon[홈]];
			CurrentPitcher = TeamInfo.getAwayPitcher();
			
		}
		//현재투수,현재타자 정보 출력, 확률 계산
		cout << endl;
		printOutCount();
		printCurrentInfo();
		setPercentage();

		string What;
		cin >> What;
		
		//포수 스탯
		if (base.checkStealAv()) {
			int stealAttNum = random.hitBall();
			//현재 투수 도루가능 스탯(평균 1) * 주자 도루시도 확률 스탯
			int stealAttBound = CurrentPitcher.getStat()[SAP] * base.getFirstBaseStat()[stealAttP];
			if (stealAttNum <= stealAttBound) {
				int stealNum = random.hitBall();
				//현재 포수 도루저지 스탯(평균 1)*주자 도루확률 스탯(base.getFirstBase().getStat()
				//int stealBound= 
			}
		}
		if (What == "도루") {
			//do something
		}
		else if (What == "교체") {
			//do something
		}
		




		//타격
		int number = random.hitBall();
		//볼넷
		if (number <= Percent[BB]) {
			//1루 비어있으면 그냥 추가, 1루 안 비어있으면 한 칸씩 앞으로
			//현재타자 출루
			cout << "볼넷" << endl;
			string toBB = CurrentBatter.getName();
			Runner toBBR(RunnerStat, toBB);
			base.moveRunner(BB, toBBR);
			
			plusTasoon();
		}
		else if (number <= Percent[SIN]) {
			//안타
			//1베이스씩 진루, 확률에 의해 추가진루
			cout << "안타~" << endl;
			string toSIN = CurrentBatter.getName();
			Runner toSINR(RunnerStat, toSIN);
			base.moveRunner(SIN, toSINR);
			base.additionalBase(SIN);
			
			plusTasoon();
		}
		else if (number <= Percent[DOU]) {
			//2루타
			//2베이스씩 진루, 확률에 의한 추가진루
			cout << "2루타~~" << endl;
			string toDOU = CurrentBatter.getName();
			Runner toDOUR(RunnerStat, toDOU);
			base.moveRunner(DOU, toDOUR);
			base.additionalBase(DOU);
			plusTasoon();
		}
		else if (number <= Percent[TRI]) {
			//3루타
			//싹쓸이
			cout << "3루타~~~" << endl;
			string toTRI = CurrentBatter.getName();
			Runner toTRIR(RunnerStat, toTRI);
			base.moveRunner(TRI, toTRIR);
			
			plusTasoon();
		}
		else if (number <= Percent[HR]) {
			//HR
			//싹쓸이
			cout << "홈런~~~~" << endl;
			string toHR = CurrentBatter.getName();
			Runner toHRR(RunnerStat, toHR);
			base.moveRunner(HR, toHRR);
		
			plusTasoon();
		}
		else if (number <= Percent[SO]) {
			//삼진
			cout << "삼진~~" << endl;
			plusTasoon();
			plusOutCount();
		}
		else if (number <= Percent[FO]) {
			//플라이
			cout << "플라이 아웃" << endl;
			base.additionalBase(FO);
			
			plusTasoon();
			plusOutCount();
			//일정확률로 추가진루
		}
		else if (number <= 10000) {
			
			if (base.checkDO(OutCount)) {
				cout << "병살 ㅅㄱ" << endl;
				base.additionalBase(DO);
				plusOutCount();
			}
			else
				cout << "땅볼" << endl;
				base.additionalBase(GO);
			
			plusTasoon();
			plusOutCount();
			//일정확률로 추가진루, 일정확률로 병살타.
		}
		
		cout << number << endl;
		Score[InnHA] += base.retScore();
		printScoreInfo();
		
	
	}
	printEndInfo();
	return 0;
}