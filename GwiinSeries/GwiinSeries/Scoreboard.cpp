#include "Scoreboard.h"
enum �ʸ�{��,��};
enum ����Ȩ{����,Ȩ};
enum ���ڰ��{BB,SIN,DOU,TRI,HR,SO,FO,GO};

Scoreboard::Scoreboard(){
	OutCount = 0;
	InnNum = 1;
	InnHA = ��;
	Score[��]=Score[��]=0;
	NumberPitch[��] = NumberPitch[��] = 100;
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
	InnHA = ��;
	Score[��] = Score[��] = 0;
	NumberPitch[����] = teaminfo.getAwayPitcher().getStat[NP]();
	NumberPitch[Ȩ] = teaminfo.getHomePitcher().getStat[NP]();
	CurrentBatter = teaminfo.getAwayBatter()[0];
	CurrentPitcher = teaminfo.getHomePitcher();
	//CurrentFielder �� CurrentCatcher�� �ʱ�ȭ
}
bool Scoreboard::isGameEnd(){
	if (InnNum >= 13) return true;
	if (InnNum >= 10 && InnNum < 13) {
		if (InnHA == ��)
			return false;
		if (InnHA == �� && (Score[��] > Score[��]))
			return true;
		if (InnHA == �� && (Score[��]!=Score[��])&&OutCount==3)
			return true;
	}
	return false;
}


void Scoreboard::changeInning() {
	
	OutCount = 0;
	if (InnHA == ��) {
		InnNum++;
		InnHA = !InnHA;
	}
	else
		InnHA = !InnHA;
	BaseSit.clear();
	//CurrentPitcher,CurrentBatter, CurrentFielder, CurrentCatcher ����.
	//�߰� �ʿ�

}

void Scoreboard::plusOutCount() {
	OutCount++;
	//��� ���� ��Ȳ�̸� ����
	if (Scoreboard::isGameEnd()) return;
	//OutCount ������ �̴� ����
	if (OutCount == 3) Scoreboard::changeInning();

}

void  Scoreboard::printOutCount() const {
	cout << OutCount << "�ƿ�" << endl;
	//opengl ����
}
void Scoreboard::printInnInfo() const {
	cout << InnNum << (InnHA == �� ? "ȸ��" : "ȸ��") << endl;
}
bool Scoreboard::getInnHA() const {
	return InnHA;
}
void Scoreboard::printCurrentInfo() const {
	cout << "���� ����: " << CurrentPitcher.getName() << endl;
	cout << "���� Ÿ��: " << CurrentBatter.getName() << endl;
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