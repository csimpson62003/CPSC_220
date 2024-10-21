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
public:
	SimpleBot();

	void takeTurn();
};

#endif
