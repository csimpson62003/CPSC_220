#include <iostream>
#include "simplebot.h"

SimpleBot::SimpleBot()
{

}
int firstRunCount = 0;
void SimpleBot::takeTurn()
{

    if (amOnExit()) {
        return;
    }
    if (scan().getType() == Exit) {
        move();
        return;
    }
    //If the exit is behind at the start;
    if (firstRunCount <4) {
        firstRunCount++;
        if (firstRunCount == 1 || firstRunCount == 2) {
            turnLeft();
            return;
        }
        else {
            turnRight();
            return;
        }

   }
    if (isTurningAround) {
        isTurningAround = false;
        turnLeft();
        return;
    }

    if (!checkDirection) {
        checkDirection = true;
        checkLeft = leftIsClear();
        checkRight = rightIsClear();
        if (!checkRight && !checkLeft && !frontIsClear()) {
            turnLeft();
            isTurningAround = true;
        }
    }

    if (checkLeft) {
        if (!directionMove) {
            turnLeft();
            directionMove = true;
            return;
        }
        else {
            turnRight();
            checkLeft = false;
            directionMove = false;
            return;
        }
    }

    if (checkRight) {
        if (!directionMove) {
            directionMove = true;
            turnRight();
            return;
        }
        else {
            turnLeft();
            checkRight = false;
            directionMove = false;
            return;
        }
    }

    if (!frontIsClear() && leftIsClear()) {
        turnLeft();
        return;
    }
    else if (!frontIsClear() && rightIsClear()) {
        turnRight();
        return;
    }
    else {
        if (frontIsClear()) {
            checkDirection = false;
            move();
            
        }
        return;
    }

    
}