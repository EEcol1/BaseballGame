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
	NumberPitch[����] = TeamInfo.getAwayPitcher().getStat()[NP];
	NumberPitch[Ȩ] = TeamInfo.getHomePitcher().getStat()[NP];
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
void printInnInfo() {
	cout << InnNum << (InnHA == �� ? "ȸ��" : "ȸ��") << endl;
}
void printCurrentInfo() {
	cout << "���� ����: " << CurrentPitcher.getName() << endl;
	cout << "���� Ÿ��: " << CurrentBatter.getName() << endl;
}
void setPercentage() {
	Percent.clear();
	for (int i = 0; i < 8; i++) {
		Percent.push_back(0);
	}
	int Inplay = 10000;
	for (int i = BB; i <= SO; i++) {
		Percent[i] = (int)(CurrentBatter.getStat()[i] * CurrentPitcher.getStat()[i] * 10000);
		Inplay = Inplay - Percent[i];
	}
	Percent[FO] = (int)(CurrentBatter.getStat()[FO] * CurrentPitcher.getStat()[FO] * Inplay);
	Percent[GO] = Inplay - Percent[FO];

	for (int i = 1; i < 8; i++) {
		Percent[i] = Percent[i - 1] + Percent[i];
	}
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
	Batting.setPlayerInfo("test.txt", 8);
	Fielding.setPlayerInfo("test.txt", 8);
	Running.setPlayerInfo("test.txt", 8);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Pitching.setPlayerInfo("test.txt", 8);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Catching.setPlayerInfo("test.txt", 8);

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
		printCurrentInfo();
		setPercentage();

		//Ÿ��
		int number = random.hitBall();
		//����
		if (number < Percent[BB]) {
			//1�� ��������� �׳� �߰�, 1�� �� ��������� �� ĭ�� ������
			//����Ÿ�� ���
			string toBB = CurrentBatter.getName();
			Runner toBBR(RunnerStat, toBB);
			base.moveRunner(BB, toBBR);
			Score[InnHA] += base.retScore();
			tasoon[InnHA]++;
		}
		if (number <= Percent[SIN]) {
			//��Ÿ
			//1���̽��� ����, Ȯ���� ���� �߰�����
			string toSIN = CurrentBatter.getName();
			Runner toSINR(RunnerStat, toSIN);
			base.moveRunner(SIN, toSINR);
			base.additionalBase(SIN);
			Score[InnHA] += base.retScore();
			tasoon[InnHA]++;
		}
		if (number <= Percent[DOU]) {
			//2��Ÿ
			//2���̽��� ����, Ȯ���� ���� �߰�����
			string toDOU = CurrentBatter.getName();
			Runner toDOUR(RunnerStat, toDOU);
			base.moveRunner(DOU, toDOUR);
			base.additionalBase(DOU);
			Score[InnHA] += base.retScore();
			tasoon[InnHA]++;
		}
		if (number <= Percent[TRI]) {
			//3��Ÿ
			//�Ͼ���
			string toTRI = CurrentBatter.getName();
			Runner toTRIR(RunnerStat, toTRI);
			base.moveRunner(TRI, toTRIR);
			Score[InnHA] += base.retScore();
			tasoon[InnHA]++;
		}
		if (number <= Percent[HR]) {
			//HR
			//�Ͼ���
			string toHR = CurrentBatter.getName();
			Runner toHRR(RunnerStat, toHR);
			base.moveRunner(HR, toHRR);
			Score[InnHA] += base.retScore();
			tasoon[InnHA]++;
		}
		if (number <= Percent[SO]) {
			//����
			cout << "����~~" << endl;
			tasoon[InnHA]++;
			plusOutCount();
		}
		if (number <= Percent[FO]) {
			//�ö���
			cout << "�ö��� �ƿ�" << endl;
			base.additionalBase(FO);
			Score[InnHA] += base.retScore();
			tasoon[InnHA]++;
			plusOutCount();
			//����Ȯ���� �߰�����
		}
		if (number <= 10000) {
			cout << "����" << endl;
			if (base.checkDO(OutCount)) {
				base.additionalBase(DO);
				plusOutCount();
			}
			else
				base.additionalBase(GO);
			Score[InnHA] += base.retScore();
			tasoon[InnHA]++;
			plusOutCount();
			//����Ȯ���� �߰�����, ����Ȯ���� ����Ÿ.
		}

		

		

		
	}



	return 0;
}