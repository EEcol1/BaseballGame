#pragma once
#include<vector>
#include"Runner.h"

enum ���ڰ�� { BB, SIN, DOU, TRI, HR, SO, FO, GO, DO, SB, P, B };
using namespace std;
class Base
{public:
	void init();
	void moveRunner(int what,Runner who);
	void additionalBase(int what);
	void SBOUT();
	int retScore();
	bool checkDO(int OutCount);
	bool checkStealAv();
	bool checkBuntAv();
	vector<double> getFirstBaseStat();
	//Ȯ�� �� ����
	vector<bool> getSit();

private:
	vector<Runner> firstBase;
	vector<Runner> secondBase;
	vector<Runner> thirdBase;
	vector<Runner> backHome;
};

