#include "Base.h"
#include "Random.h"
enum 숫자계산 { BB, SIN, DOU, TRI, HR, SO, FO, GO,DO};

void Base::init() {
	firstBase.clear();
	secondBase.clear();
	thirdBase.clear();
	backHome.clear();
}
void Base::moveRunner(int what,Runner who) {
	if (what == SIN) {
		if (thirdBase.size() == 1)
			backHome.push_back(thirdBase[0]);
		thirdBase.clear();
		if (secondBase.size() == 1)
			thirdBase=secondBase;
		secondBase.clear();
		if (firstBase.size() == 1)
			secondBase=firstBase;
		firstBase.clear();
		firstBase.push_back(who);
	}
	if (what == DOU) {
		if (thirdBase.size() == 1)
			backHome.push_back(thirdBase[0]);
		thirdBase.clear();
		if (secondBase.size() == 1)
			backHome.push_back(secondBase[0]);
		secondBase.clear();
		if (firstBase.size() == 1)
			thirdBase = firstBase;
		firstBase.clear();
		secondBase.push_back(who);
	}
	if (what == TRI) {
		if (thirdBase.size() == 1)
			backHome.push_back(thirdBase[0]);
		thirdBase.clear();
		if (secondBase.size() == 1)
			backHome.push_back(secondBase[0]);
		secondBase.clear();
		if (firstBase.size() == 1)
			backHome.push_back(firstBase[0]);
		firstBase.clear();
		thirdBase.push_back(who);

	}
	if (what == HR) {
		if (thirdBase.size() == 1)
			backHome.push_back(thirdBase[0]);
		thirdBase.clear();
		if (secondBase.size() == 1)
			backHome.push_back(secondBase[0]);
		secondBase.clear();
		if (firstBase.size() == 1)
			backHome.push_back(firstBase[0]);
		firstBase.clear();
		backHome.push_back(who);
	}
	if (what == BB) {
		if (firstBase.size() == 1 && secondBase.size() == 0) {
			//1루 채워져 있고, 2루 비었다
			secondBase = firstBase;
			firstBase.clear();
			firstBase.push_back(who);
		}
		else if (firstBase.size() == 1 && secondBase.size() == 1 && thirdBase.size()==0) {
			//12루에서 만루로
			thirdBase = secondBase;
			secondBase.clear();
			secondBase = firstBase;
			firstBase.clear();
			firstBase.push_back(who);

		}
		else if (firstBase.size() == 1 && secondBase.size() == 1 && thirdBase.size() == 1) {
			backHome.push_back(thirdBase[0]);
			thirdBase.clear();
			thirdBase = secondBase;
			secondBase.clear();
			secondBase = firstBase;
			firstBase.clear();
			firstBase.push_back(who);
		}

		else if (firstBase.size() == 0)
			firstBase.push_back(who);

	}
}

void Base::additionalBase(int what) {
	Random random;
	int number = random.hitBall();
	switch (what) {
		case DOU:
			if (thirdBase.size() == 1) {
				int bound = (int)(thirdBase[0].getStat()[addBaseP] * 4090);
				if (number <= bound)
					backHome.push_back(thirdBase[0]);
				thirdBase.clear();
			}
			break;
		case SIN:
			if (thirdBase.size() == 1) {
				int bound = (int)(thirdBase[0].getStat()[addBaseP] * 6800);
				if (number <= bound)
					backHome.push_back(thirdBase[0]);
				thirdBase.clear();
			}
			else if (thirdBase.size() == 0 && secondBase.size() == 1) {
				int bound = (int)(secondBase[0].getStat()[addBaseP] * 2880);
				if (number <= bound)
					thirdBase = secondBase;
				secondBase.clear();
			}
			break;
		case FO:
			if (thirdBase.size() == 1) {
				int bound = (int)(thirdBase[0].getStat()[addBaseP] * 7640);
				if (number <= bound)
					backHome.push_back(thirdBase[0]);
				thirdBase.clear();
			}
			else if (thirdBase.size() == 0 && secondBase.size() == 1) {
				int bound = (int)(secondBase[0].getStat()[addBaseP] * 2880);
				if (number <= bound)
					thirdBase = secondBase;
				secondBase.clear();
			}
			break;
		case GO:
			if (thirdBase.size() == 1) {
				int bound = (int)(thirdBase[0].getStat()[addBaseP] * 5160);
				if (number <= bound)
					backHome.push_back(thirdBase[0]);
				thirdBase.clear();
			}
			else if (thirdBase.size() == 0 && secondBase.size() == 1) {
				int bound = (int)(secondBase[0].getStat()[addBaseP] * 6400);
				if (number <= bound)
					thirdBase = secondBase;
				secondBase.clear();
			}
			else if (secondBase.size() == 0 && firstBase.size() == 1) {
				int bound = (int)(firstBase[0].getStat()[addBaseP] * 6400);
				if (number <= bound)
					secondBase = firstBase;
				firstBase.clear();
			}
			break;
		case DO:
			if (thirdBase.size() == 1 && firstBase.size() == 0) {
				thirdBase.clear();
				thirdBase = secondBase;
				secondBase = firstBase;
				firstBase.clear();
			}
			else if (thirdBase.size() == 1&&firstBase.size()==1) {
				if (number <= 2500) {
					thirdBase.clear();
					thirdBase = secondBase;
					secondBase = firstBase;
					firstBase.clear();
				}
				else {
					backHome.push_back(thirdBase[0]);
					thirdBase = secondBase;
					secondBase.clear();
					firstBase.clear();
				}
			}
			else if (firstBase.size() == 1) {
				thirdBase = secondBase;
				secondBase.clear();
				firstBase.clear();
			}
			break;

	}
	
}
int Base::retScore() {
	int ret = backHome.size();
	backHome.clear();
	return ret;
}


bool Base::checkDO(int OutCount) {
	if (OutCount >= 2) {
		return 0;
	}
	else {
		Random random;
		int number = random.hitBall();
		if (thirdBase.size() == 1&&firstBase.size()==0) {
			if (number <= 1000) {
				return 1;
			}
			else
				return 0;
		}
		else if(number<=3800&&firstBase.size()==1) {
			return 1;
		}
		return 0;
	}
}