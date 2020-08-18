#include "Pitcher.h"
#include "Random.h"
Pitcher::Pitcher() {
	//기본생성자
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
		PitcherStat[i] *= (2-Condition);
	}
	PitcherStat[SOT] *= Condition;
}
vector<double> Pitcher::getStat() const {
	return PitcherStat;
}