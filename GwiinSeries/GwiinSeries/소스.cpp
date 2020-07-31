#include "Input.h"
#include "CurrentPlayer.h"
#include "Scoreboard.h"
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
	Pitcher hpitcher;
	hpitcher.setStat(PitcherInfo, hpname);
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
	Pitcher apitcher;
	apitcher.setStat(PitcherInfo, apname);
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
		Batter hbat;
		hbat.setStat(BatterInfo, hbname);
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
		Batter abat;
		abat.setStat(BatterInfo, abname);
		abatVec.push_back(abat);
	}
	//������ Ÿ�� ���� �� (���� Ÿ�� ����)
	TeamInfo.setAwayBatter(abatVec);

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


int main() {
	//�������� ����
	vector<Input> SumBatterInfo;

	//Ÿ�� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Batting.setPlayerInfo("test.txt", 8);
	Fielding.setPlayerInfo("test.txt", 8);
	Running.setPlayerInfo("test.txt", 8);
	SumBatterInfo.push_back(Batting);
	SumBatterInfo.push_back(Fielding);
	SumBatterInfo.push_back(Running);
	enum BFR { Ÿ��, ����, �ַ� };

	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Pitching.setPlayerInfo("test.txt", 8);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Catching.setPlayerInfo("test.txt", 8);

	init();
	Scoreboard GB;
	//1-9ȸ ok 10-12ȸ:�� �����̸� �״�� ����, �������̸� 
	while (GB.getInnNum() >= 1 && GB.getInnNum() < 13) {
		enum �ʸ� { ��, �� };
		if (GB.getInnNum() >= 10) {
			if (GB.getInnHA() == �� && GB.getHomeScore() > GB.getAwayScore()) {
				cout << "������" << endl;
				break;
			}
			//OutCount 3�� �ٽ� ����
			if (GB.getInnHA() == �� && GB.getHomeScore() != GB.getAwayScore() && GB.getOutCount() == 3) {
				break;
			}
		}

	}



	return 0;
}