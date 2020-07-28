#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

class Input
{
public:
	void setPlayerInfo(const char* filename, int n);
	map<string, vector<double>> getPlayerInfo();

private:

	map<string, vector<double>> PlayerInfo;


};

