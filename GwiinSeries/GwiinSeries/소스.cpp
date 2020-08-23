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
enum �ʸ� { ��, �� };
enum ����Ȩ { ����, Ȩ };
enum ���ڰ�� { BB, SIN, DOU, TRI, HR, SO, FO, GO,DO};

int OutCount;
int InnNum;
bool InnHA;
vector<Runner> BaseSit;
int Score[2];
int NumberPitch[2];
int tasoon[2];
int& awaytasoon = tasoon[����];
int& hometasoon = tasoon[Ȩ];
Batter CurrentBatter;
Pitcher CurrentPitcher;
vector<int> Percent;
Base base;

//��� ���������� ���� �ᵵ �ǳ�
/*auto BatterInfo = Batting.getPlayerInfo();
auto FielderInfo = Fielding.getPlayerInfo();
auto RunningInfo = Running.getPlayerInfo();
auto PitcherInfo = Pitching.getPlayerInfo();
auto CatchingInfo = Catching.getPlayerInfo();*/

void init() {
	string hteam, ateam;
	cout << "����(Ȩ)�� �Է��ϼ���: ";
	cin >> hteam;
	TeamInfo.setHomeTeam(hteam);
	cout << "����(����)�� �Է��ϼ���: ";
	cin >> ateam;
	TeamInfo.setAwayTeam(ateam);
	//**********���� �Է�**********
	string hpname, apname;
	auto PitcherInfo = Pitching.getPlayerInfo();
	//Ȩ ����
	cout << "Ȩ�� ��������: ";
	cin >> hpname;
	auto iter1 = PitcherInfo.find(hpname);
	while (iter1 == PitcherInfo.end()) {
		cout << "�ٽ� �Է��ϼ���: ";
		cin >> hpname;
		iter1 = PitcherInfo.find(hpname);
	}

	//HomePitcher ����, (���� ���� ����)
	//TeamInfo.setHomePitcher(hpitch);
	//TeamInfo.setCurrentPitcher(hpitch);
	Pitcher hpitcher(PitcherInfo, hpname);
	TeamInfo.setHomePitcher(hpitcher);

	//���� ����
	cout << "������ ��������: ";
	cin >> apname;
	auto iter2 = PitcherInfo.find(apname);
	while (iter2 == PitcherInfo.end()) {
		cout << "�ٽ� �Է��ϼ���: ";
		cin >> apname;
		iter2 = PitcherInfo.find(apname);
	}
	//AwayPitcher ����
	//TeamInfo.setAwayPitcher(apitch);
	Pitcher apitcher(PitcherInfo, apname);
	TeamInfo.setAwayPitcher(apitcher);

	//*********Ÿ���Է�*******
	vector<Batter> hbatVec, abatVec;
	auto BatterInfo = Batting.getPlayerInfo();
	//Ȩ
	for (int i = 0; i < 9; i++) {
		cout << "Ȩ�� " << i + 1 << "�� Ÿ��: ";
		string hbname;
		cin >> hbname;
		auto iter3 = BatterInfo.find(hbname);
		while (iter3 == BatterInfo.end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> hbname;
			iter3 = BatterInfo.find(hbname);
		}
		//����Ÿ�� ���
		//hbatVec.push_back(hbat);
		Batter hbat(BatterInfo,hbname);
		hbatVec.push_back(hbat);
	}
	//Ȩ�� Ÿ�� ����
	TeamInfo.setHomeBatter(hbatVec);

	//����
	for (int i = 0; i < 9; i++) {
		cout << "������ " << i + 1 << "�� Ÿ��: ";
		string abname;
		cin >> abname;
		auto iter4 = BatterInfo.find(abname);
		while (iter4 == BatterInfo.end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> abname;
			iter4 = BatterInfo.find(abname);
		}
		//����Ÿ�� ���
		Batter abat(BatterInfo,abname);
		abatVec.push_back(abat);
	}
	//������ Ÿ�� ���� �� (���� Ÿ�� ����)
	TeamInfo.setAwayBatter(abatVec);

	OutCount = 0;
	InnNum = 1;
	InnHA = ��;
	Score[��] = Score[��] = 0;
	//NumberPitch[����] = TeamInfo.getAwayPitcher().getStat()[NP];
	//NumberPitch[Ȩ] = TeamInfo.getHomePitcher().getStat()[NP];
	CurrentBatter = TeamInfo.getAwayBatter()[0];
	CurrentPitcher = TeamInfo.getHomePitcher();
	tasoon[����] = tasoon[Ȩ] = 0;
	//CurrentFielder �� CurrentCatcher�� �ʱ�ȭ

	//���� ����



	/*//���� ����Ʈ
	//������ ���� ����Ʈ
	cout << TeamInfo.getAwayTeam() << endl;
	cout << "��������: " << TeamInfo.getAwayPitcher().getname() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "�� Ÿ��: " << TeamInfo.getAwayBatter()[i].getname() << endl;
	}
	cout << endl;
	//Ȩ�� ���� ����Ʈ
	cout << TeamInfo.getHomeTeam() << endl;
	cout << "��������: " << TeamInfo.getHomePitcher().getname() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "�� Ÿ��: " << TeamInfo.getHomeBatter()[i].getname() << endl;
	}
	cout << endl;
	*/
}
bool isGameEnd() {
	if (InnNum >= 13) return true;
	if (InnNum >= 10 && InnNum < 13) {
		if (InnHA == ��)
			return false;
		if (InnHA == �� && (Score[��] > Score[��]))
			return true;
		if (InnHA == �� && (Score[��] != Score[��]) && OutCount == 3)
			return true;
	}
	return false;
}
void changeInning() {

	OutCount = 0;
	if (InnHA == ��) {
		InnNum++;
		InnHA = !InnHA;
	}
	else
		InnHA = !InnHA;
	base.init();
	//CurrentPitcher,CurrentBatter, CurrentFielder, CurrentCatcher ����.
	//�߰� �ʿ�

}
void plusTasoon() {
	tasoon[InnHA]++;
	tasoon[InnHA] = tasoon[InnHA] % 9;
}
void plusOutCount() {
	OutCount++;
	//��� ���� ��Ȳ�̸� ����
	if (isGameEnd()) return;
	//OutCount ������ �̴� ����
	if (OutCount == 3) changeInning();

}

void  printOutCount() {
	cout << OutCount << "�ƿ�" << endl;
	//opengl ����
}
void printScoreInfo() {
	cout << TeamInfo.getAwayTeam() << Score[����] << ":" << Score[Ȩ] << TeamInfo.getHomeTeam() << endl;
}
void printInnInfo() {
	cout << endl;
	cout << InnNum << (InnHA == �� ? "ȸ��" : "ȸ��") << endl;
}
void printCurrentInfo() {
	cout << "���� ����: " << CurrentPitcher.getName() << endl;
	cout << "���� Ÿ��: " << CurrentBatter.getName() << endl;
}
void setPercentage() {
	//�ٽ� ���� ��
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
	//Ÿ�� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Batting.setPlayerInfo("batterstat.txt", 8);
	Fielding.setPlayerInfo("test.txt", 6);
	Running.setPlayerInfo("runnerstat.txt", 3);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Pitching.setPlayerInfo("pitcherstat.txt", 8);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Catching.setPlayerInfo("test.txt", 6);

	init();
	Random random;
	enum ���ڰ�� { BB, SIN, DOU, TRI, HR, SO, FO, GO };
	//1-9ȸ ok 10-12ȸ:�� �����̸� �״�� ����, �������̸� 
	enum �ʸ�{��,��};
	bool previousState = ��;
	auto RunnerStat = Running.getPlayerInfo();

	while (!isGameEnd()) {
		//��������� �̴�(��,��) ǥ��
		if (previousState != InnHA) {
			printInnInfo();
			previousState = InnHA;
		}



		//��������,���� Ÿ�� ����
		if (InnHA == ��) {
			//���� Ÿ��,�������� ����
			CurrentBatter=TeamInfo.getAwayBatter()[tasoon[����]];
			CurrentPitcher=TeamInfo.getHomePitcher();
			
		}
		else if (InnHA == ��) {
			CurrentBatter = TeamInfo.getHomeBatter()[tasoon[Ȩ]];
			CurrentPitcher = TeamInfo.getAwayPitcher();
			
		}
		//��������,����Ÿ�� ���� ���, Ȯ�� ���
		cout << endl;
		printOutCount();
		printCurrentInfo();
		setPercentage();

		string What;
		cin >> What;
		if (What == "����") {
			//do something
		}
		else if (What == "��ü") {
			//do something
		}
		




		//Ÿ��
		int number = random.hitBall();
		//����
		if (number <= Percent[BB]) {
			//1�� ��������� �׳� �߰�, 1�� �� ��������� �� ĭ�� ������
			//����Ÿ�� ���
			cout << "����" << endl;
			string toBB = CurrentBatter.getName();
			Runner toBBR(RunnerStat, toBB);
			base.moveRunner(BB, toBBR);
			Score[InnHA] += base.retScore();
			plusTasoon();
		}
		else if (number <= Percent[SIN]) {
			//��Ÿ
			//1���̽��� ����, Ȯ���� ���� �߰�����
			cout << "��Ÿ~" << endl;
			string toSIN = CurrentBatter.getName();
			Runner toSINR(RunnerStat, toSIN);
			base.moveRunner(SIN, toSINR);
			base.additionalBase(SIN);
			Score[InnHA] += base.retScore();
			plusTasoon();
		}
		else if (number <= Percent[DOU]) {
			//2��Ÿ
			//2���̽��� ����, Ȯ���� ���� �߰�����
			cout << "2��Ÿ~~" << endl;
			string toDOU = CurrentBatter.getName();
			Runner toDOUR(RunnerStat, toDOU);
			base.moveRunner(DOU, toDOUR);
			base.additionalBase(DOU);
			Score[InnHA] += base.retScore();
			plusTasoon();
		}
		else if (number <= Percent[TRI]) {
			//3��Ÿ
			//�Ͼ���
			cout << "3��Ÿ~~~" << endl;
			string toTRI = CurrentBatter.getName();
			Runner toTRIR(RunnerStat, toTRI);
			base.moveRunner(TRI, toTRIR);
			Score[InnHA] += base.retScore();
			plusTasoon();
		}
		else if (number <= Percent[HR]) {
			//HR
			//�Ͼ���
			cout << "Ȩ��~~~~" << endl;
			string toHR = CurrentBatter.getName();
			Runner toHRR(RunnerStat, toHR);
			base.moveRunner(HR, toHRR);
			Score[InnHA] += base.retScore();
			plusTasoon();
		}
		else if (number <= Percent[SO]) {
			//����
			cout << "����~~" << endl;
			plusTasoon();
			plusOutCount();
		}
		else if (number <= Percent[FO]) {
			//�ö���
			cout << "�ö��� �ƿ�" << endl;
			base.additionalBase(FO);
			Score[InnHA] += base.retScore();
			plusTasoon();
			plusOutCount();
			//����Ȯ���� �߰�����
		}
		else if (number <= 10000) {
			
			if (base.checkDO(OutCount)) {
				cout << "���� ����" << endl;
				base.additionalBase(DO);
				plusOutCount();
			}
			else
				cout << "����" << endl;
				base.additionalBase(GO);
			Score[InnHA] += base.retScore();
			plusTasoon();;
			plusOutCount();
			//����Ȯ���� �߰�����, ����Ȯ���� ����Ÿ.
		}

		

		

		
	}



	return 0;
}