#pragma once
#include<string>
#include<random>
using namespace std;
class Random
{public:
	Random();
	Random(int i);
	double randgen();
	int randNP(int a);
	int hitBall();

private:
	int randcase;
	
};

