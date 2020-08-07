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
	Scoreboard Game;
	Random random;
	enum ���ڰ�� { BB, SIN, DOU, TRI, HR, SO, FO, GO };
	//1-9ȸ ok 10-12ȸ:�� �����̸� �״�� ����, �������̸� 
	enum �ʸ�{��,��};
	bool previousState = ��;
	int hometasoon = 0;
	int awaytasoon = 0;
	while (!Game.isGameEnd()) {
		//��������� �̴�(��,��) ǥ��
		if (previousState != Game.getInnHA())
			Game.printInnInfo();
		//�� ���� ��
		if (Game.getInnHA() == ��) {
			//���� Ÿ��,�������� ����
			Game.setCurrentBatter(TeamInfo.getAwayBatter()[awaytasoon]);
			Game.setCurrentPitcher(TeamInfo.getHomePitcher());
			//���� Ÿ��,���� ���
			Game.printCurrentInfo();
			Game.setPercentage();
		}
		int number = random.hitBall();
		//����
		if (number < Game.getPercentage()[BB]) {
			//1�� ��������� �׳� �߰�, 1�� �� ��������� �� ĭ�� ������


		}
		if (number <= Game.getPercentage()[SIN]) {
			//��Ÿ
			//1���̽��� ����, Ȯ���� ���� �߰�����
		}
		if (number <= Game.getPercentage()[DOU]) {
			//2��Ÿ
			//2���̽��� ����, Ȯ���� ���� �߰�����
		}
		if (number <= Game.getPercentage()[TRI]) {
			//3��Ÿ
			//�Ͼ���
		}
		if (number <= Game.getPercentage()[HR]) {
			//HR
			//�Ͼ���
		}
		if (number <= Game.getPercentage()[SO]) {
			//����
			cout << "����~~" << endl;
			Game.plusOutCount();
		}
		if (number <= Game.getPercentage()[FO]) {
			//�ö���
			cout << "�ö��� �ƿ�" << endl;
			Game.plusOutCount();
			//����Ȯ���� �߰�����
		}
		if (number <= 10000) {
			cout << "����" << endl;
			Game.plusOutCount();
			//����Ȯ���� �߰�����, ����Ȯ���� ����Ÿ.
		}

		

		

		bool previousState = Game.getInnHA();
	}



	return 0;
}