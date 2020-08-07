#include "Scoreboard.h"
enum 초말{초,말};
enum 원정홈{원정,홈};
enum 숫자계산{BB,SIN,DOU,TRI,HR,SO,FO,GO};

Scoreboard::Scoreboard(){
	OutCount = 0;
	InnNum = 1;
	InnHA = 초;
	Score[초]=Score[말]=0;
	NumberPitch[초] = NumberPitch[말] = 100;
	BaseSit.clear();

	Batter b;
	CurrentBatter=b;
	Pitcher p;
	CurrentPitcher = p;
	//Catcher c;
	//CurrentCatcher = c;
	//Fielder f;
	//CurrentFielder = f;
}

Scoreboard::Scoreboard(CurrentPlayer teaminfo) {
	OutCount = 0;
	InnNum = 1;
	InnHA = 초;
	Score[초] = Score[말] = 0;
	NumberPitch[원정] = teaminfo.getAwayPitcher().getStat[NP]();
	NumberPitch[홈] = teaminfo.getHomePitcher().getStat[NP]();
	CurrentBatter = teaminfo.getAwayBatter()[0];
	CurrentPitcher = teaminfo.getHomePitcher();
	//CurrentFielder 와 CurrentCatcher도 초기화
}
bool Scoreboard::isGameEnd(){
	if (InnNum >= 13) return true;
	if (InnNum >= 10 && InnNum < 13) {
		if (InnHA == 초)
			return false;
		if (InnHA == 말 && (Score[말] > Score[초]))
			return true;
		if (InnHA == 말 && (Score[말]!=Score[초])&&OutCount==3)
			return true;
	}
	return false;
}


void Scoreboard::changeInning() {
	
	OutCount = 0;
	if (InnHA == 말) {
		InnNum++;
		InnHA = !InnHA;
	}
	else
		InnHA = !InnHA;
	BaseSit.clear();
	//CurrentPitcher,CurrentBatter, CurrentFielder, CurrentCatcher 변경.
	//추가 필요

}

void Scoreboard::plusOutCount() {
	OutCount++;
	//경기 종료 상황이면 종료
	if (Scoreboard::isGameEnd()) return;
	//OutCount 꽉차면 이닝 교대
	if (OutCount == 3) Scoreboard::changeInning();

}

void  Scoreboard::printOutCount() const {
	cout << OutCount << "아웃" << endl;
	//opengl 사용시
}
void Scoreboard::printInnInfo() const {
	cout << InnNum << (InnHA == 초 ? "회초" : "회말") << endl;
}
bool Scoreboard::getInnHA() const {
	return InnHA;
}
void Scoreboard::printCurrentInfo() const {
	cout << "현재 투수: " << CurrentPitcher.getName() << endl;
	cout << "현재 타자: " << CurrentBatter.getName() << endl;
}

void Scoreboard::setCurrentBatter(Batter cbat) {
	CurrentBatter = cbat;
}
void Scoreboard::setCurrentPitcher(Pitcher cpit) {
	CurrentPitcher = cpit;
}
void Scoreboard::setPercentage() {
	for (int i = 0; i < 8; i++) {
		Percent.push_back(0);
	}
	int Inplay=10000;
	for (int i = BB; i <= SO; i++) {
		Percent[i] = (int)CurrentBatter.getStat()[i] * CurrentPitcher.getStat()[i] * 10000;
		Inplay = Inplay - Percent[i];
	}
	Percent[FO] = CurrentBatter.getStat()[FO] * CurrentPitcher.getStat()[FO] * Inplay;
	Percent[GO] = Inplay - Percent[FO];

	for (int i = 1; i < 8; i++) {
		Percent[i] = Percent[i - 1] + Percent[i];
	}

}

vector<int> Scoreboard::getPercentage() const {
	return Percent;
}