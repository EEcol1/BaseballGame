#pragma once
#include<vector>
#include"Runner.h"
using namespace std;
class Base
{public:
	void init();
	void moveRunner(int what,Runner who);
	void additionalBase(int what);
	int retScore();
	bool checkDO(int OutCount);
private:
	vector<Runner> firstBase;
	vector<Runner> secondBase;
	vector<Runner> thirdBase;
	vector<Runner> backHome;
};

