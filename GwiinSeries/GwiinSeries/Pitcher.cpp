#include "Pitcher.h"
#include "Random.h"
Pitcher::Pitcher() {
	//�⺻������
}
Pitcher::Pitcher(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition ����
	PitcherStat = playerinfo[player];
	Random random;
	Condition = random.randgen();
}

void Pitcher::setCondition() {
	//���� ������Ʈ ��������� ����
}
void Pitcher::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition ����
	PitcherStat = playerinfo[player];
}
void Pitcher::setCondition() {
	//��Ÿ�� �ƴϸ� ���� Ȯ����
	for (int i = 0; i <= HRT; i++) {
		PitcherStat[i] *= (2-Condition);
	}
	PitcherStat[SOT] *= (2 - Condition);
}
vector<double> Pitcher::getStat() const {
	return PitcherStat;
}
/*int Pitcher::getNP() const{
	return NP;
}*/