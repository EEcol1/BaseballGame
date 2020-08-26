#include "Random.h"

enum 숫자계산 { BB, SIN, DOU, TRI, HR, SO, FO, GO, DO, SB, P, B };
Random::Random() {
	randcase = 3;
}
Random::Random(int i) {
	randcase = i;
}
double Random::randgen(){
	double condarray[5] = { 0.8,0.9,1.0,1.1,1.2 };
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 5);
	randcase = dis(gen);
	/*for (int i = 1; i <= 5; i++) {
		if (randcase == i)
			return condarray[i - 1];
	}
	return 1.0;*/
	return condarray[randcase - 1];
}
int Random::randNP(int a) {
	int NParray[23] = { 1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,4,5,5,6,6,9 };
	int NPBB[23] = { 4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,7,7,7,10 };
	int NPSO[23] = { 3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6 };

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 23);
	randcase = dis(gen);
	if (a == BB) return NPBB[randcase - 1];
	else if (a == SO) return NPSO[randcase - 1];
	else return NParray[randcase - 1];
}
int Random::hitBall() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 10000);
	return dis(gen);

}