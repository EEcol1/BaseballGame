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
}
void Batter::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	//condition ���� ����
	BatterStat = playerinfo[player];
	Condition = 1;
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
/*double Batter::getBBP() {
	return BBP;
}
double Batter::getsingleP() {
	return singleP;
}
double Batter::getdoubleP() {
	return doubleP;
}
double Batter::gettripleP() {
	return tripleP;
}
double Batter::getHRP() {
	return HRP;
}
double Batter::getSOP() {
	return SOP;
}
double Batter::getFOP() {
	return FOP;
}
double Batter::getGOP() {
	return GOP;
}
double Batter::getCondition() {
	return condition;
}*/
