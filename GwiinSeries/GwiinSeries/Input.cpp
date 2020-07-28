#include "Input.h"
#include<iostream>
#include<fstream>

void Input::setPlayerInfo(const char* filename, int n) {
	ifstream input(filename);
	const int lineSize = 128;
	char line[lineSize];
	char* token = NULL;
	char* next_token = NULL;

	while (input.getline(line, lineSize)) {
		//printf("%s\n", line);
		token = strtok_s(line, "/", &next_token);
		char* name = token;
		string str(name);
		vector<double> number;
		for (int i = 0; i < n; i++) {
			token = strtok_s(NULL, "/", &next_token);
			number.push_back(atof(token));
		}
		PlayerInfo.insert(make_pair(str, number));

	}

}
map<string, vector<double>> Input::getPlayerInfo() {
	return PlayerInfo;
}
