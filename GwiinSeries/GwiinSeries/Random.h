#pragma once
#include<random>
using namespace std;
class Random
{public:
	Random();
	Random(int i);
	double randgen();
	int hitBall();

private:
	int randcase;
	
};

