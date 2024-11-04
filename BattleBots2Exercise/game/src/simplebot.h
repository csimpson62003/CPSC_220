#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "battlebot.h"

class SimpleBot: public BattleBot
{
private:
	bool isLeft = false;
	bool isRight = false;
	bool directionMove = false;
	char lastTurn;
	bool isTurningAround = false;
	bool objectInFront = false;
	bool checkLeft = false;
	bool checkRight = false;
	bool checkDirection = false;
public:
	SimpleBot();

	void takeTurn();
};

#endif
