#include "Batter.h"
#include "Random.h"
//constructor ��������...
Batter::Batter() {
	Name = "unselected";
	Condition = 1;
	vector<double> a(8);
	BatterStat=a;

}
Batter::Batter(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//Condition ����
	BatterStat = playerinfo[player];
	Random random;
	Condition = random.randgen();
	Batter::setCondition();
}
void Batter::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	BatterStat = playerinfo[player];
	//����� ����
	Random random;
	Condition = random.randgen();
	Batter::setCondition();
}
void Batter::setCondition() {
	//��Ÿ Ȯ���� �޶������� ���� Ȯ���� �޶�������
	for (int i = 0; i <=HRP; i++) {
		BatterStat[i] *= Condition;
	}
	BatterStat[SOP] *= (2 - Condition);
}
vector<double> Batter::getStat() const {
	return BatterStat;
}
