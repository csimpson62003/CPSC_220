#include <iostream>
#include "simplebot.h"

SimpleBot::SimpleBot()
{
	
}

void SimpleBot::takeTurn()
{
	if (directionMove) {
		directionMove = false;
		move();
		return;
	}

	if (isLeft) {
		isLeft = false;
		turnLeft();
		return;
	}
	else if (isRight) {
		isRight = false;
		turnRight();
		return;
	}

	if (amOnExit()) {
		return;
	}

	if (frontIsClear()) {
		move();
	}
	else {

		if (leftIsClear() && lastTurn != 'L') {
			lastTurn = 'L';
			turnLeft();
			directionMove = true;
			isLeft = true;
			return;
		}
		else if (rightIsClear() && lastTurn != 'R') {
			lastTurn = 'R';
			turnRight();
			directionMove = true;
			isRight = true;
			return;
		}

		else if (!leftIsClear()) {
			lastTurn = 'R';
			turnRight();
			isRight = true;
			return;
		}
		else if (!rightIsClear()) {
			lastTurn = 'L';
			turnLeft();
			isLeft = true;
			return;
		}
	}
}