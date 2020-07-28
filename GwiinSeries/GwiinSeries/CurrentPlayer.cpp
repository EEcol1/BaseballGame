#include "CurrentPlayer.h"
string CurrentPlayer::getHomeTeam() {
	return HomeTeam;
}
string CurrentPlayer::getAwayTeam() {
	return AwayTeam;
}
void CurrentPlayer::setHomeTeam(string hteam) {
	HomeTeam = hteam;
}
void CurrentPlayer::setAwayTeam(string ateam) {
	AwayTeam = ateam;
}

string CurrentPlayer::getHomePitcher() {
	return HomePitcher;
}
string CurrentPlayer::getAwayPitcher() {
	return AwayPitcher;
}
void CurrentPlayer::setHomePitcher(string hpitch) {
	HomePitcher = hpitch;
}
void CurrentPlayer::setAwayPitcher(string apitch) {
	AwayPitcher = apitch;
}
vector<string> CurrentPlayer::getHomeBatter() {
	return HomeBatter;
}
vector<string> CurrentPlayer::getAwayBatter() {
	return AwayBatter;
}
void CurrentPlayer::setHomeBatter(vector<string> hbatvec) {
	HomeBatter = hbatvec;
}
void CurrentPlayer::setAwayBatter(vector<string> abatvec) {
	AwayBatter = abatvec;
}

string CurrentPlayer::getCurrentPitcher() {
	return CurrentPitcher;
}
string CurrentPlayer::getCurrentBatter() {
	return CurrentBatter;
}
vector<string> CurrentPlayer::getCurrentFielder() {
	return CurrentFielder;
}
void CurrentPlayer::setCurrentPitcher(string cpitch) {
	CurrentPitcher = cpitch;
}
void CurrentPlayer::setCurrentBatter(string cbat) {
	CurrentBatter = cbat;
}
void CurrentPlayer::setCurrentFielder(vector<string> cfield) {
	CurrentFielder = cfield;
}