#include "Random.h"
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
	for (int i = 1; i <= 5; i++) {
		if (randcase == i)
			return condarray[i - 1];
	}
	return 1.0;
}
int Random::hitBall() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 10000);
	return dis(gen);

}