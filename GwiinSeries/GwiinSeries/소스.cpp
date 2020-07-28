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
	cout << "����(Ȩ)�� �Է��ϼ���: ";
	cin >> hteam;
	PlayBall.setHomeTeam(hteam);
	cout << "����(����)�� �Է��ϼ���: ";
	cin >> ateam;
	PlayBall.setAwayTeam(ateam);
	//**********���� �Է�**********
	string hpitch, apitch;
	//Ȩ ����
	cout << "Ȩ�� ��������: ";
	cin >> hpitch;
	auto iter1 = Pitching.getPlayerInfo().find(hpitch);
	while (iter1 == Pitching.getPlayerInfo().end()) {
		cout << "�ٽ� �Է��ϼ���: ";
		cin >> hpitch;
		iter1 = Pitching.getPlayerInfo().find(hpitch);
	}
	//HomePitcher ����, ���� ���� ����
	PlayBall.setHomePitcher(hpitch);
	PlayBall.setCurrentPitcher(hpitch);
	//���� ����
	cout << "������ ��������: ";
	cin >> apitch;
	auto iter2 = Pitching.getPlayerInfo().find(apitch);
	while (iter2 == Pitching.getPlayerInfo().end()) {
		cout << "�ٽ� �Է��ϼ���: ";
		cin >> apitch;
		iter2 = Pitching.getPlayerInfo().find(apitch);
	}
	//AwayPitcher ����
	PlayBall.setAwayPitcher(apitch);

	//*********Ÿ���Է�*******
	vector<string> hbatVec, abatVec;
	//Ȩ
	for (int i = 0; i < 9; i++) {
		cout << "Ȩ�� " << i + 1 << "�� Ÿ��: ";
		string hbat;
		cin >> hbat;
		auto iter3 = Batting.getPlayerInfo().find(hbat);
		while (iter3 == Batting.getPlayerInfo().end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> hbat;
			iter3 = Batting.getPlayerInfo().find(hbat);
		}
		//����Ÿ�� ���
		hbatVec.push_back(hbat);
	}
	//Ȩ�� Ÿ�� ����
	PlayBall.setHomeBatter(hbatVec);

	//����
	for (int i = 0; i < 9; i++) {
		cout << "������ " << i + 1 << "�� Ÿ��: ";
		string abat;
		cin >> abat;
		auto iter4 = Batting.getPlayerInfo().find(abat);
		while (iter4 == Batting.getPlayerInfo().end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> abat;
			iter4 = Batting.getPlayerInfo().find(abat);
		}
		//����Ÿ�� ���
		abatVec.push_back(abat);
	}
	//������ Ÿ�� ���� �� ���� Ÿ�� ����
	PlayBall.setAwayBatter(abatVec);
	PlayBall.setCurrentBatter(abatVec[0]);

	//���� ����



	//���� ����Ʈ
	//������ ���� ����Ʈ
	cout << PlayBall.getAwayTeam() << endl;
	cout << "��������: " << PlayBall.getAwayPitcher() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "�� Ÿ��: " << PlayBall.getAwayBatter()[i] << endl;
	}
	cout << endl;
	//Ȩ�� ���� ����Ʈ
	cout << PlayBall.getHomeTeam() << endl;
	cout << "��������: " << PlayBall.getHomePitcher() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "�� Ÿ��: " << PlayBall.getHomeBatter()[i] << endl;
	}
	cout << endl;

}


int main() {
	//�������� ����
	vector<Input> SumBatterInfo;

	//Ÿ�� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Batting.setPlayerInfo("test.txt", 6);
	Fielding.setPlayerInfo("test.txt", 6);
	Running.setPlayerInfo("test.txt", 6);
	SumBatterInfo.push_back(Batting);
	SumBatterInfo.push_back(Fielding);
	SumBatterInfo.push_back(Running);
	enum BFR { Ÿ��, ����, �ַ� };

	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Pitching.setPlayerInfo("test.txt", 6);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Catching.setPlayerInfo("test.txt", 6);

	init();





	return 0;
}