#include "Batter.h"
#include "Random.h"
//constructor 만들어야지...
Batter::Batter() {
	Name = "unselected";
	Condition = 1;
	vector<double> a(8);
	BatterStat=a;

}
Batter::Batter(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition 랜덤
	BatterStat = playerinfo[player];
	Random random;
	Condition = random.randgen();
	Batter::setCondition();
}
void Batter::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	BatterStat = playerinfo[player];
	//컨디션 설정
	Random random;
	Condition = random.randgen();
	Batter::setCondition();
}
void Batter::setCondition() {
	//안타 확률만 달라질건지 볼넷 확률만 달라질건지
	for (int i = 0; i <=HRP; i++) {
		BatterStat[i] *= Condition;
	}
	BatterStat[SOP] *= (2 - Condition);
}
vector<double> Batter::getStat() const {
	return BatterStat;
}
