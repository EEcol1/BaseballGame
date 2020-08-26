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

Pitcher CurrentPlayer::getHomePitcher() {
	return HomePitcher;
}
Pitcher CurrentPlayer::getAwayPitcher() {
	return AwayPitcher;
}
void CurrentPlayer::setHomePitcher(Pitcher hpitch) {
	HomePitcher = hpitch;
}
void CurrentPlayer::setAwayPitcher(Pitcher apitch) {
	AwayPitcher = apitch;
}
vector<Batter> CurrentPlayer::getHomeBatter() {
	return HomeBatter;
}
vector<Batter> CurrentPlayer::getAwayBatter() {
	return AwayBatter;
}
void CurrentPlayer::setHomeBatter(vector<Batter> hbatvec) {
	HomeBatter = hbatvec;
}
void CurrentPlayer::setAwayBatter(vector<Batter> abatvec) {
	AwayBatter = abatvec;
}
void CurrentPlayer::changeHomeBatter(Batter cbat, int num) {
	HomeBatter[num] = cbat;
}
void CurrentPlayer::changeAwayBatter(Batter cbat, int num) {
	AwayBatter[num] = cbat;
}
Catcher CurrentPlayer::getHomeCatcher() {
	return HomeCatcher;
}
Catcher CurrentPlayer::getAwayCatcher() {
	return AwayCatcher;
}
void CurrentPlayer::setHomeCatcher(Catcher hcat) {
	HomeCatcher = hcat;
}
void CurrentPlayer::setAwayCatcher(Catcher acat) {
	AwayCatcher = acat;
}
/*
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
}*/