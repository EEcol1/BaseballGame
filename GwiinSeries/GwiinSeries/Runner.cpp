#include "Runner.h"

Runner::Runner() {
	Name = "unselected";
	Condition = 1;
	vector<double> a(3);
	RunnerStat = a;

}

Runner::Runner(Batter hitter) {
	Name = hitter.getName();
	Condition = 1;

}
Runner::Runner(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	RunnerStat = playerinfo[player];
	Condition = 1;
}

void Runner::setCondition() {
	return;
}
void Runner::setStat(map<string, vector<double>> playerinfo, string player) {
	Name = player;
	RunnerStat = playerinfo[player];
	Condition = 1;
}
vector<double> Runner::getStat() const {
	return RunnerStat;
}
