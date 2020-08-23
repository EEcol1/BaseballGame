#include "Pitcher.h"
#include "Random.h"
Pitcher::Pitcher() {
	//�⺻������
	Name = "unselected";
	Condition = 1;
	vector<double> a(8);
	PitcherStat = a;
}
Pitcher::Pitcher(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition ����
	PitcherStat = playerinfo[player];
	Random random;
	Condition = random.randgen();
}

void Pitcher::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition ����
	PitcherStat = playerinfo[player];
	Random random;
	Condition = random.randgen();
	Pitcher::setCondition();
}
void Pitcher::setCondition() {
	//��Ÿ�� �ƴϸ� ���� Ȯ����
	for (int i = 0; i <= HRT; i++) {
		PitcherStat[i] *= Condition;
	}
	PitcherStat[SOT] *= (2-Condition);
}
vector<double> Pitcher::getStat() const {
	return PitcherStat;
}