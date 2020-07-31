#pragma once
class Scoreboard
{
public:
	//�ƿ�ī��Ʈ
	void plusOutCount();
	int getOutCount() const;
	//�̴�
	void plusInnNum();
	int getInnNum() const;
	void setInnHA(bool homeaway);
	bool getInnHA() const;
	//���ڻ�Ȳ
	void setBaseSit(bool base1, bool base2, bool base3);
	bool getBase1() const;
	bool getBase2() const;
	bool getBase3() const;
	//����
	void setHomeScore(int homescore);
	void plusHomeScore(int plusscore);
	int getHomeScore() const;
	void setAwayScore(int awayscore);
	void plusAwayScore(int plusscore);
	int getAwayScore() const;
	//������
	void setCurrentPitcherNP(int NP);
	void plusCurrentPitcherNP(int NP);
	int getCurrentPitcherNP() const;

	void setHomePitcherNP(int NP);
	int getHomePitcherNP() const;
	void setAwayPitcherNP(int NP);
	int getAwayPitcherNP() const;
	//Ÿ�� �� ���� �� ���ڿ� ���� ����

private:
	//�ƿ�ī��Ʈ
	int OutCount;
	//�̴�
	//�� ����vs �� ���� 1�̸� �� ����,0�̸� �� ����
	int InnNum;
	bool InnHA;
	//���� ��Ȳ *���� INFO�� ���� ��.
	bool BaseSit[3];
	//Ȩ,����� ����
	int HomeScore;
	int AwayScore;
	//������
	int HomePitcherNP;
	int AwayPitcherNP;
	int CurrentPitcherNP;
	//���� ���� �� ���� Ÿ�ڿ� ���� ����
	/*
	�ڷ��� �̰���
	CurrentBatter
	CurrentBatterInfo[n]: Ÿ��,��Ÿ�� �� ����� ��ܾ���.
	CurrentPitcher
	CurrentPitcherInfo[n]: �������� ��ϵ��� ��ܾ���
	CurrentFielder[n]
	CurrentFielderInfo[n][n]
	+���� INFO �Ƹ��� CurrentRunner[3]
	*/
};

