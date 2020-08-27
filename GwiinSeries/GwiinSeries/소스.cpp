#include "Input.h"
#include "CurrentPlayer.h"
#include "Random.h"
#include "Base.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <GL/glut.h>
using namespace std;
Input Batting;
Input Running;
Input Pitching;
Input Catching;
CurrentPlayer TeamInfo;
enum �ʸ� { ��, �� };
enum ����Ȩ { ����, Ȩ };
int OutCount;
int InnNum;
bool InnHA;
int Score[2];
//827 �߰�
vector<int> ScoreVec[2];
int Hit[2];
int Ball[2];
int Error[2];
int NumberPitch[2];
int tasoon[2];
int& awaytasoon = tasoon[����];
int& hometasoon = tasoon[Ȩ];
Batter CurrentBatter;
Pitcher CurrentPitcher;
Catcher CurrentCatcher;
vector<int> Percent;
Base base;
vector<string> result[2][9];
vector<string> startBatterHome;
vector<string> startBatterAway;
Random random;
map<string, vector<double>> RunnerStat;
vector<string> RBIVec;

void init() {
	string hteam, ateam;
	cout << "����(Ȩ)�� �Է��ϼ���: ";
	cin >> hteam;
	TeamInfo.setHomeTeam(hteam);
	cout << "����(����)�� �Է��ϼ���: ";
	cin >> ateam;
	TeamInfo.setAwayTeam(ateam);
	//**********���� �Է�**********
	string hpname, apname;
	auto PitcherInfo = Pitching.getPlayerInfo();
	//Ȩ ����
	cout << "Ȩ�� ��������: ";
	cin >> hpname;
	auto iter1 = PitcherInfo.find(hpname);
	while (iter1 == PitcherInfo.end()) {
		cout << "�ٽ� �Է��ϼ���: ";
		cin >> hpname;
		iter1 = PitcherInfo.find(hpname);
	}

	//HomePitcher ����, (���� ���� ����)
	//TeamInfo.setHomePitcher(hpitch);
	//TeamInfo.setCurrentPitcher(hpitch);
	Pitcher hpitcher(PitcherInfo, hpname);
	TeamInfo.setHomePitcher(hpitcher);

	//���� ����
	cout << "������ ��������: ";
	cin >> apname;
	auto iter2 = PitcherInfo.find(apname);
	while (iter2 == PitcherInfo.end()) {
		cout << "�ٽ� �Է��ϼ���: ";
		cin >> apname;
		iter2 = PitcherInfo.find(apname);
	}
	//AwayPitcher ����
	//TeamInfo.setAwayPitcher(apitch);
	Pitcher apitcher(PitcherInfo, apname);
	TeamInfo.setAwayPitcher(apitcher);

	//*********Ÿ���Է�*******
	vector<Batter> hbatVec, abatVec;
	auto BatterInfo = Batting.getPlayerInfo();
	auto CatcherInfo = Catching.getPlayerInfo();
	//Ȩ
	for (int i = 0; i < 9; i++) {
		cout << "Ȩ�� " << i + 1 << "�� Ÿ��: ";
		string hbname;
		cin >> hbname;
		auto iter3 = BatterInfo.find(hbname);
		while (iter3 == BatterInfo.end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> hbname;
			iter3 = BatterInfo.find(hbname);
		}
		//����Ÿ�� ���
		//hbatVec.push_back(hbat);
		Batter hbat(BatterInfo,hbname);
		hbatVec.push_back(hbat);
		startBatterHome.push_back(hbname);
		auto itercatch1 = CatcherInfo.find(hbname);
		if (itercatch1 != CatcherInfo.end()) {
			Catcher hcat(CatcherInfo, hbname);
			TeamInfo.setHomeCatcher(hcat);
		}

	}
	//Ȩ�� Ÿ�� ����
	TeamInfo.setHomeBatter(hbatVec);
	
	//����
	for (int i = 0; i < 9; i++) {
		cout << "������ " << i + 1 << "�� Ÿ��: ";
		string abname;
		cin >> abname;
		auto iter4 = BatterInfo.find(abname);
		while (iter4 == BatterInfo.end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> abname;
			iter4 = BatterInfo.find(abname);
		}
		//����Ÿ�� ���
		Batter abat(BatterInfo,abname);
		abatVec.push_back(abat);
		startBatterAway.push_back(abname);
		auto itercatch2 = CatcherInfo.find(abname);
		if (itercatch2 != CatcherInfo.end()) {
			Catcher acat(CatcherInfo, abname);
			TeamInfo.setAwayCatcher(acat);
		}
	}
	//������ Ÿ�� ���� �� (���� Ÿ�� ����)
	TeamInfo.setAwayBatter(abatVec);

	OutCount = 0;
	InnNum = 1;
	InnHA = ��;
	Score[��] = Score[��] = 0;
	//827�߰�
	ScoreVec[��].push_back(0);
	NumberPitch[����] = TeamInfo.getAwayPitcher().getStat()[NP];
	NumberPitch[Ȩ] = TeamInfo.getHomePitcher().getStat()[NP];
	CurrentBatter = TeamInfo.getAwayBatter()[0];
	CurrentPitcher = TeamInfo.getHomePitcher();
	CurrentCatcher = TeamInfo.getHomeCatcher();
	tasoon[����] = tasoon[Ȩ] = 0;
	//CurrentFielder �� CurrentCatcher�� �ʱ�ȭ

	//���� ����



	/*//���� ����Ʈ
	//������ ���� ����Ʈ
	cout << TeamInfo.getAwayTeam() << endl;
	cout << "��������: " << TeamInfo.getAwayPitcher().getname() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "�� Ÿ��: " << TeamInfo.getAwayBatter()[i].getname() << endl;
	}
	cout << endl;
	//Ȩ�� ���� ����Ʈ
	cout << TeamInfo.getHomeTeam() << endl;
	cout << "��������: " << TeamInfo.getHomePitcher().getname() << endl;
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << "�� Ÿ��: " << TeamInfo.getHomeBatter()[i].getname() << endl;
	}
	cout << endl;
	*/
}
bool isGameEnd() {
	if (InnNum >= 13) return true;
	if (InnNum >= 9 && InnNum < 13) {
		if (InnHA == ��)
			return false;
		if (InnHA == �� && (Score[��] > Score[��]))
			return true;
		if (InnHA == �� && (Score[��] != Score[��]) && OutCount == 3)
			return true;
	}
	return false;
}
void changeInning() {

	OutCount = 0;
	if (InnHA == ��) {
		InnNum++;
		InnHA = !InnHA;
	}
	else
		InnHA = !InnHA;
	base.init();

	//827 �߰�
	ScoreVec[InnHA].push_back(0);
}
void plusTasoon() {
	tasoon[InnHA]++;
	tasoon[InnHA] = tasoon[InnHA] % 9;
}
void plusOutCount() {
	OutCount++;
	//��� ���� ��Ȳ�̸� ����
	if (isGameEnd()) return;
	//OutCount ������ �̴� ����
	if (OutCount == 3) changeInning();

}
void setCurrentInfo() {
	if (InnHA == ��) {
		//���� Ÿ��,�������� ����
		CurrentBatter = TeamInfo.getAwayBatter()[tasoon[����]];
		CurrentPitcher = TeamInfo.getHomePitcher();
		CurrentCatcher = TeamInfo.getHomeCatcher();

	}
	else if (InnHA == ��) {
		CurrentBatter = TeamInfo.getHomeBatter()[tasoon[Ȩ]];
		CurrentPitcher = TeamInfo.getAwayPitcher();
		CurrentCatcher = TeamInfo.getAwayCatcher();

	}
}

void  printOutCount() {
	cout << endl;
	cout << "�ƿ�: ";
	if (OutCount == 0) {
		cout << "�ۡ�" << endl;
	}
	else if (OutCount == 1) {
		cout << "�ܡ�" << endl;
	}
	else if (OutCount == 2) {
		cout << "�ܡ�" << endl;
	}
	//opengl ����
}
void printScoreInfo() {
	cout << TeamInfo.getAwayTeam() << Score[����] << ":" << Score[Ȩ] << TeamInfo.getHomeTeam() << endl;
}
//827 �߰�
/*void printScoreVecInfo() {
	int AWAYSCORE=0;
	int HOMESCORE = 0;
	for (int i = 0; i < ScoreVec[0].size(); i++) {
		AWAYSCORE += ScoreVec[0][i];
	}
	for (int i = 0; i < ScoreVec[1].size(); i++) {
		HOMESCORE += ScoreVec[1][i];;
	}
	cout << TeamInfo.getAwayTeam() << AWAYSCORE << ":" << HOMESCORE << TeamInfo.getHomeTeam() << endl;
}*/
void printInnInfo() {
	cout << endl;
	cout << InnNum << (InnHA == �� ? "ȸ��" : "ȸ��") << endl;
}
void printCurrentInfo() {
	cout << "���� ����: " << CurrentPitcher.getName() << endl;
	cout << "���� Ÿ��: " << CurrentBatter.getName() << endl;
}
//827 �߰�
void printEndInfo() {
	cout << endl;
	cout << "�������" << endl;
	printScoreInfo();
	
	if (Score[����] ==Score[Ȩ]) cout << "���º�" << endl;
	else cout << (Score[����] > Score[Ȩ] ? TeamInfo.getAwayTeam() : TeamInfo.getHomeTeam()) << " �¸�" << endl;

}
void printRunnerInfo() {
	vector<bool> RunnerInfoVec = base.getSit();
	//2��
	if (RunnerInfoVec[1] == true) {
		cout << "    ��" << endl;
	}
	else {
		cout << "    ��" << endl;
	}
	if (RunnerInfoVec[0] == true && RunnerInfoVec[2] == true) {
		cout << "  ��  ��" << endl;
	}
	else if (RunnerInfoVec[0] == true && RunnerInfoVec[2] == false) {
		cout << "  ��  ��" << endl;
	}
	else if (RunnerInfoVec[0] == false && RunnerInfoVec[2] == true) {
		cout << "  ��  ��" << endl;
	}
	else if (RunnerInfoVec[0] == false && RunnerInfoVec[2] == false) {
		cout << "  ��  ��" << endl;
	}
}
void setPercentage() {
	//�ٽ� ���� ��
	for (int i = 0; i < 8; i++) {
		Percent.push_back(0);
	}
	Percent[BB] = (int)(CurrentBatter.getStat()[BB] * CurrentPitcher.getStat()[BB] * 10000);
	int Inplay = 10000 - Percent[BB];
	for (int i = SIN; i <= SO; i++) {
		Percent[i] = Percent[i-1] + (int)(CurrentBatter.getStat()[i] * CurrentPitcher.getStat()[i] * Inplay);
	}
	int Out = 10000 - Percent[SO];
	Percent[FO] = Percent[SO]+(int)((CurrentBatter.getStat()[FO] + CurrentPitcher.getStat()[FO]) / 2.0 * Out);
	Percent[GO] = 10000;
}
void setandPrintCurrent() {
	setCurrentInfo();
	printOutCount();
	printRunnerInfo();
	printCurrentInfo();
	
	if (NumberPitch[!InnHA] <= -20) {
		cout << "�Ѱ������� �ʰ��� ���� ��� ���� ����" << endl;
	}
	else if (NumberPitch[!InnHA] <= 0) {
		cout << "�Ѱ������� ����" << endl;
		CurrentPitcher.needChange();
	}
	
	setPercentage();
}
void setGameRecord() {
	ofstream fs_a("away.txt");
	ofstream fs_h("home.txt");
	ofstream fs_r("����.txt");
	ofstream fs_rbi("Ÿ��.txt");
	ofstream fs_game("�����.txt");
	for (int i = 0; i < 9; i++) {
		fs_a << startBatterAway[i] << " ";
		for (int j = 0; j < result[����][i].size(); j++) {
			fs_a << result[����][i][j] << " ";
		}
		fs_a << endl;
	}
	fs_a.close();
	for (int i = 0; i < 9; i++) {
		fs_h << startBatterHome[i] << " ";
		for (int j = 0; j < result[Ȩ][i].size(); j++) {
			fs_h << result[Ȩ][i][j] << " ";
		}
		fs_h << endl;
	}
	fs_h.close();
	vector<string> RunVec = base.getRunVec();
	for (int i = 0; i < RunVec.size(); i++) {
		fs_r << RunVec[i] << endl;
	}
	fs_r.close();
	for (int i = 0; i < RBIVec.size(); i++) {
		fs_rbi << RBIVec[i] << endl;
	}
	fs_rbi.close();
	//ù°��
	fs_game << "     ";
	for (int i = 0; i < ScoreVec[����].size(); i++) {
		fs_game << i + 1 << " ";
	}
	fs_game << "R H E B" << endl;
	//��° ��
	fs_game << TeamInfo.getAwayTeam() << " ";
	for (int i = 0; i < ScoreVec[����].size(); i++) {
		fs_game << ScoreVec[����][i] << " ";
	}
	
	fs_game << Score[����] << " " << Hit[����] << " " << Error[����] << " " << Ball[����] << endl;
	//��°��
	fs_game << TeamInfo.getHomeTeam() << " ";
	for (int i = 0; i < ScoreVec[Ȩ].size(); i++) {
		fs_game << ScoreVec[Ȩ][i] << " ";
	}
	if (ScoreVec[����].size() == ScoreVec[Ȩ].size() + 1) {
		fs_game << "  ";
	}
	
	fs_game << Score[Ȩ] << " " << Hit[Ȩ] << " " << Error[Ȩ] << " " << Ball[Ȩ] << endl;
	fs_game.close();
}
void addressInput(string What) {
	if (What == "��Ʈ" && base.checkBuntAv()) {
		//do something
		int bunt = random.hitBall();
		int buntBound = 5830;
		if (bunt <= buntBound) {
			cout << "��Ʈ ����" << endl;
			base.additionalBase(B);
			NumberPitch[!InnHA] -= 1;
			plusTasoon();
			plusOutCount();
			setandPrintCurrent();
			string stop;
			cin >> stop;
			addressInput(stop);
		}
		else if (bunt > buntBound&& bunt <= buntBound + 1000) {
			cout << "��Ʈ ���� �ƿ�" << endl;
			plusTasoon();
			plusOutCount();
			setandPrintCurrent();
			string stop;
			cin >> stop;
			addressInput(stop);
		}
		else {
			cout << "��Ʈ ����->���� ��ȯ" << endl;
			string stop;
			cin >> stop;
			while (stop == "��Ʈ") {
				string stop;
				cin >> stop;
			}
			addressInput(stop);
		}
	}
	else if (What == "������ü") {
		//do something
		auto PitcherInfo = Pitching.getPlayerInfo();
		string cpname;
		cout << "���� �̸� �Է��ϼ���: ";
		cin >> cpname;
		auto iterP = PitcherInfo.find(cpname);
		while (iterP == PitcherInfo.end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> cpname;
			iterP = PitcherInfo.find(cpname);
		}
		Pitcher cPitcher(PitcherInfo, cpname);
		if (InnHA == ��) {
			TeamInfo.setHomePitcher(cPitcher);
			NumberPitch[Ȩ] = TeamInfo.getHomePitcher().getStat()[NP];
		}
		else {
			TeamInfo.setAwayPitcher(cPitcher);
			NumberPitch[����] = TeamInfo.getAwayPitcher().getStat()[NP];
		}
		setandPrintCurrent();
		string stop;
		cin >> stop;
		addressInput(stop);
	}
	else if (What == "Ÿ�ڱ�ü") {
		auto BatterInfo = Batting.getPlayerInfo();
		string cbname;
		cout << "Ÿ�� �̸� �Է��ϼ���: ";
		cin >> cbname;
		auto iterB = BatterInfo.find(cbname);
		while (iterB == BatterInfo.end()) {
			cout << "�ٽ� �Է��ϼ���: ";
			cin >> cbname;
			iterB = BatterInfo.find(cbname);
		}
		Batter cBatter(BatterInfo, cbname);
		if (InnHA == ��)
			TeamInfo.changeAwayBatter(cBatter, tasoon[����]);
		else
			TeamInfo.changeHomeBatter(cBatter, tasoon[Ȩ]);
		setandPrintCurrent();
		string stop;
		cin >> stop;
		addressInput(stop);
	}
	else if (What == "���ǻ籸" || What == "����4��") {
		cout << "�ڵ�����4��" << endl;
		string toBB = CurrentBatter.getName();
		Runner toBBR(RunnerStat, toBB);
		base.moveRunner(BB, toBBR);
		result[InnHA][tasoon[InnHA]].push_back("����4��");
		Ball[InnHA]++;
		plusTasoon();
		setandPrintCurrent();
		string stop;
		cin >> stop;
		addressInput(stop);
	}
	else if (What == "������") {
		cout << (int)(CurrentPitcher.getStat()[NP] - NumberPitch[!InnHA]) << endl;
		string stop;
		cin >> stop;
		addressInput(stop);
	}
}
/*void drawBase(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(50, 0, 0);
	glVertex3f(0, 50, 0);
	glVertex3f(-50, 0, 0);
	glVertex3f(0, -50, 0);
	glEnd();
	glPopMatrix();
}
void drawOut(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBegin(GL_TRIANGLE_FAN);
	for (int j = 0; j < 50; j++) {
		glColor3f(1, 0, 0);
		glVertex2f(50 * cos(2 * j * PI / 50), 50 * sin(2 * j * PI / 50));	
	}
	glEnd();
	glPopMatrix();
}
void renderScene() {
	/*glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawBase();
	drawCircle(100, 100);
	glFlush();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	glOrtho(0, WIDTH, 0, HEIGHT, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//����
	vector<bool> drawBaseVec = base.getSit();

	if (drawBaseVec[0] == true) {
		drawBase(180, 0);
	}
	if(drawBaseVec[1]==true){
		drawBase(120, 180);
	}
	if (drawBaseVec[2] == true) {
		drawBase(60, 0);
	}
	//�ƿ�ī��Ʈ
	if (OutCount == 1) {
		drawOut(20, 20);
	}
	if (OutCount == 2) {
		drawOut(40, 20);
	}
	glutSwapBuffers();
}
/*void updateScore() {
	vector<Runner> temp;
	for (Runner Runners : BaseSit) {
		if (Runners.getRunnerPosition() < 4) {
			temp.push_back(Runners);
		}

	}
}*/
/*void moveRunner(int result) {
	if (result >= SIN && result <= HR) {
		for (Runner Runners:BaseSit) {
			Runners.plusRunnerPosition(result);
		}
	}
}*/
int main() {
	//Ÿ�� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	
	Batting.setPlayerInfo("batterstat.txt", 8);
	Running.setPlayerInfo("runnerstat.txt", 3);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Pitching.setPlayerInfo("pitcherstat.txt", 10);
	//���� ���� (�ƱԸ�Ʈ ���� �ʿ�)
	Catching.setPlayerInfo("catcherstat.txt", 3);

	init();
	RunnerStat = Running.getPlayerInfo();
	bool previousState = ��;
	

	while (!isGameEnd()) {
		//��������� �̴�(��,��) ǥ��
		
	
		if (previousState != InnHA) {
			printInnInfo();
			previousState = InnHA;
		}



		//��������,���� Ÿ�� ����
		setandPrintCurrent();
		
		string What;
		cin >> What;
		addressInput(What);
		/*if (What == "��Ʈ"&&base.checkBuntAv()) {
			//do something
			int bunt = random.hitBall();
			int buntBound = 5830;
			if (bunt <= buntBound) {
				cout << "��Ʈ ����" << endl;
				base.additionalBase(B);
				NumberPitch[!InnHA] -= 1;
				plusTasoon();
				plusOutCount();
				setandPrintCurrent();
				string stop;
				cin >> stop;
			}
			else if (bunt > buntBound&& bunt <= buntBound + 1000) {
				cout << "��Ʈ ���� �ƿ�" << endl;
				plusTasoon();
				plusOutCount(); 
				setandPrintCurrent();
				string stop;
				cin >> stop;
			}
			else {
				cout << "��Ʈ ����->���� ��ȯ" << endl;
				string stop;
				cin >> stop;
			}
		}
		else if (What == "������ü") {
			//do something
			auto PitcherInfo = Pitching.getPlayerInfo();
			string cpname;
			cout << "���� �̸� �Է��ϼ���: ";
			cin >> cpname;
			auto iterP = PitcherInfo.find(cpname);
			while (iterP == PitcherInfo.end()) {
				cout << "�ٽ� �Է��ϼ���: ";
				cin >> cpname;
				iterP = PitcherInfo.find(cpname);
			}
			Pitcher cPitcher(PitcherInfo, cpname);
			if (InnHA == ��) {
				TeamInfo.setHomePitcher(cPitcher);
				NumberPitch[Ȩ] = TeamInfo.getHomePitcher().getStat()[NP];
			}
			else {
				TeamInfo.setAwayPitcher(cPitcher);
				NumberPitch[����] = TeamInfo.getAwayPitcher().getStat()[NP];
			}
			setandPrintCurrent();
			string stop;
			cin >> stop;
		}
		else if (What == "Ÿ�ڱ�ü") {
			auto BatterInfo = Batting.getPlayerInfo();
			string cbname;
			cout << "Ÿ�� �̸� �Է��ϼ���: ";
			cin >> cbname;
			auto iterB = BatterInfo.find(cbname);
			while (iterB == BatterInfo.end()) {
				cout << "�ٽ� �Է��ϼ���: ";
				cin >> cbname;
				iterB = BatterInfo.find(cbname);
			}
			Batter cBatter(BatterInfo, cbname);
			if (InnHA == ��)
				TeamInfo.changeAwayBatter(cBatter, tasoon[����]);
			else
				TeamInfo.changeHomeBatter(cBatter, tasoon[Ȩ]);
			setandPrintCurrent();
			string stop;
			cin >> stop;
		}
		else if (What == "���ǻ籸"||What=="����4��") {
			cout << "�ڵ�����4��" << endl;
			string toBB = CurrentBatter.getName();
			Runner toBBR(RunnerStat, toBB);
			base.moveRunner(BB, toBBR);
			result[InnHA][tasoon[InnHA]].push_back("����4��");
			plusTasoon();
			setandPrintCurrent();
			string stop;
			cin >> stop;
		}*/
		//����
		int pass = random.hitBall();
		int passBound = (int)(CurrentCatcher.getStat()[�����������] * CurrentPitcher.getStat()[BB]*125);
		if (pass <= passBound&&!(base.getSit()[0]==0&&base.getSit()[1]==0&&base.getSit()[2]==0)) {
			//�߰�����
			cout << "����" << endl;
			base.additionalBase(P);
			ScoreVec[InnHA].back() += base.retScore();
			setandPrintCurrent();
			string stop;
			cin >> stop;
			addressInput(stop);
		}
		//�ڵ�����
		if (base.checkStealAv()) {
			int stealAttNum = random.hitBall();
			//���� ���� ���簡�� ����(��� 1) * ���� ����õ� Ȯ�� ����
			int stealAttBound = (int)(CurrentPitcher.getStat()[��������õ�] *CurrentCatcher.getStat()[��������õ�] *base.getFirstBaseStat()[���ڵ���õ�]*100);
			if (stealAttNum <= stealAttBound) {
				int stealNum = random.hitBall();
				int stealBound = (int)(CurrentCatcher.getStat()[�����������] * base.getFirstBaseStat()[���ڵ��缺��]*100);
				if (stealNum <= stealBound) {
					cout << "���� ����" << endl;
					base.additionalBase(SB);
					//printRunnerInfo();
					//printScoreInfo();
					
				}
				else {
					cout << "���� ����" << endl;
					base.SBOUT();
					plusOutCount();
					
				}
				setandPrintCurrent();
				string stop;
				cin >> stop;
				addressInput(stop);
			}
		}
		




		//Ÿ��
		int number = random.hitBall();
		//����
		string batterName = CurrentBatter.getName();
		Runner beRunner(RunnerStat, batterName);
		if (number <= Percent[BB]) {
			//1�� ��������� �׳� �߰�, 1�� �� ��������� �� ĭ�� ������
			//����Ÿ�� ���
			cout << "����" << endl;
			base.moveRunner(BB, beRunner);
			NumberPitch[!InnHA] -= random.randNP(BB);
			result[InnHA][tasoon[InnHA]].push_back("����");
			Ball[InnHA]++;
			plusTasoon();
		}
		else if (number <= Percent[SIN]) {
			//��Ÿ
			//1���̽��� ����, Ȯ���� ���� �߰�����
			cout << "��Ÿ~" << endl;
			base.moveRunner(SIN, beRunner);
			base.additionalBase(SIN);
			NumberPitch[!InnHA] -= random.randNP(SIN);
			result[InnHA][tasoon[InnHA]].push_back("��Ÿ");
			Hit[InnHA]++;
			plusTasoon();
		}
		else if (number <= Percent[DOU]) {
			//2��Ÿ
			//2���̽��� ����, Ȯ���� ���� �߰�����
			cout << "2��Ÿ~~" << endl;
			base.moveRunner(DOU, beRunner);
			base.additionalBase(DOU);
			NumberPitch[!InnHA] -= random.randNP(DOU);
			result[InnHA][tasoon[InnHA]].push_back("2��Ÿ");
			Hit[InnHA]++;
			plusTasoon();
		}
		else if (number <= Percent[TRI]) {
			//3��Ÿ
			//�Ͼ���
			cout << "3��Ÿ~~~" << endl;
			base.moveRunner(TRI, beRunner);
			NumberPitch[!InnHA] -= random.randNP(TRI);
			result[InnHA][tasoon[InnHA]].push_back("3��Ÿ");
			Hit[InnHA]++;
			plusTasoon();
		}
		else if (number <= Percent[HR]) {
			//HR
			//�Ͼ���
			cout << "Ȩ��~~~~" << endl;
			base.moveRunner(HR, beRunner);
			NumberPitch[!InnHA] -= random.randNP(HR);
			result[InnHA][tasoon[InnHA]].push_back("Ȩ��");
			Hit[InnHA]++;
			plusTasoon();
		}
		else if (number <= Percent[SO]) {
			//����
			cout << "����~~" << endl;
			NumberPitch[!InnHA] -= random.randNP(SO);
			result[InnHA][tasoon[InnHA]].push_back("����");
			plusTasoon();
			plusOutCount();
		}
		else if (number <= Percent[FO]) {
			//�ö���
			cout << "�ö��� �ƿ�" << endl;
			base.additionalBase(FO);
			NumberPitch[!InnHA] -= random.randNP(FO);
			result[InnHA][tasoon[InnHA]].push_back("���");
			plusTasoon();
			plusOutCount();
			//����Ȯ���� �߰�����
		}
		else if (number <= 9832) {
			
			if (base.checkDO(OutCount)) {
				cout << "���� ����" << endl;
				base.additionalBase(DO);
				result[InnHA][tasoon[InnHA]].push_back("����Ÿ");
				plusOutCount();
			}
			else {
				cout << "����" << endl;
				base.additionalBase(GO);
				result[InnHA][tasoon[InnHA]].push_back("����");
			}
			NumberPitch[!InnHA] -= random.randNP(GO);
			plusTasoon();
			plusOutCount();
			//����Ȯ���� �߰�����, ����Ȯ���� ����Ÿ.
		}
		else if (number <= 10000) {
			cout << "��å��� ������" << endl;
			base.moveRunner(SIN, beRunner); 
			NumberPitch[!InnHA] -= random.randNP(SIN);
			result[InnHA][tasoon[InnHA]].push_back("��å");
			Error[!InnHA]++;
			plusTasoon();
		}
		
		//cout << number << endl;
		int plusScore = base.retScore();
		Score[InnHA] += plusScore;
		//827 �߰�
		ScoreVec[InnHA].back() += plusScore;
	//Ÿ�� ���
		for (int i = 0; i < plusScore; i++) {
			RBIVec.push_back(batterName);
		}
		printScoreInfo();
		
	
	}
	printEndInfo();
	setGameRecord();
	return 0;
}
/*void main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(650, 300);
	glutInitWindowSize(800, 600);
	glutCreateWindow("���νø��� 2020");
	// register callbacks
	glutDisplayFunc(renderScene);
	//glutIdleFunc(GamePlay);

	// enter GLUT event processing cycle
	glutMainLoop();

}*/