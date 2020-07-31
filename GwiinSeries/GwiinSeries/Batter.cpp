#include "Batter.h"
void Batter::setCondition() {
	//랜덤 오브젝트 만든다음에 생각
}
void Batter::setStat(map<string, vector<double>> playerinfo, string player) {
	name = player;
	//condition 먼저 설정
	//condition=5가지 랜덤
	//밑의 스탯에 컨디션 곱해야.
	BBP = playerinfo[player][0];
	singleP = playerinfo[player][1];
	doubleP = playerinfo[player][2];
	tripleP = playerinfo[player][3];
	HRP = playerinfo[player][4];
	SOP = playerinfo[player][5];
	FOP = playerinfo[player][6];
	GOP = playerinfo[player][7];

}
string Batter::getname() {
	return name;
}
double Batter::getBBP() {
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
double Batter::getcondition() {
	return condition;
}
