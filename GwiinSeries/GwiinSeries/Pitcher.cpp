#include "Pitcher.h"
#include "Random.h"
Pitcher::Pitcher() {
	//기본생성자
	Name = "unselected";
	Condition = 1;
	vector<double> a(8);
	PitcherStat = a;
}
Pitcher::Pitcher(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition 랜덤
	PitcherStat = playerinfo[player];
	Random random;
	Condition = random.randgen();
}

void Pitcher::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition 랜덤
	PitcherStat = playerinfo[player];
	Random random;
	Condition = random.randgen();
	Pitcher::setCondition();
}
void Pitcher::setCondition() {
	//안타만 아니면 볼넷 확률도
	for (int i = 0; i <= HRT; i++) {
		PitcherStat[i] *= Condition;
	}
	PitcherStat[SOT] *= (2-Condition);
}
vector<double> Pitcher::getStat() const {
	return PitcherStat;
}