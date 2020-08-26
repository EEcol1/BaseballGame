#include "Catcher.h"


Catcher::Catcher() {
	Name = "unselected";
	Condition = 1;
	vector<double> a(3);
	CatcherStat = a;
}
Catcher::Catcher(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	CatcherStat = playerinfo[player];
	Condition = 1;
}
void Catcher::setCondition() {
	for (int i = 0; i < CatcherStat.size(); i++)
		CatcherStat[i] *= Condition;
}
void Catcher::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	CatcherStat = playerinfo[player];
	Condition = 1;
}
vector<double> Catcher::getStat() const {
	return CatcherStat;
}