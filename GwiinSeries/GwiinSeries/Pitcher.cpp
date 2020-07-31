#include "Pitcher.h"

void Pitcher::setCondition() {
	//랜덤 오브젝트 만든다음에 생각
}
void Pitcher::setStat(map<string, vector<double>> playerinfo, string player) {
	name = player;
	//condition 먼저 설정
	//condition=5가지 랜덤
	//밑의 스탯에 컨디션 곱해야.
	BBT = playerinfo[player][0];
	singleT = playerinfo[player][1];
	doubleT = playerinfo[player][2];
	tripleT = playerinfo[player][3];
	HRT = playerinfo[player][4];
	SOT = playerinfo[player][5];
	FOT = playerinfo[player][6];
	GOT = playerinfo[player][7];

}
string Pitcher::getname() {
	return name;
}
double Pitcher::getBBT() {
	return BBT;
}
double Pitcher::getsingleT() {
	return singleT;
}
double Pitcher::getdoubleT() {
	return doubleT;
}
double Pitcher::gettripleT() {
	return tripleT;
}
double Pitcher::getHRT() {
	return HRT;
}
double Pitcher::getSOT() {
	return SOT;
}
double Pitcher::getFOT() {
	return FOT;
}
double Pitcher::getGOT() {
	return GOT;
}
double Pitcher::getcondition() {
	return condition;
}
