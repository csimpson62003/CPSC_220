
#include "enemyEntity.h"
#include "world.h"
#include "playerEntity.h"
#include <raylib.h>
using namespace std;

EnemyEntity::EnemyEntity(float x, float y, int width, int height, EntityType type, string playerName, float health, Entity* playerToAttack):Entity(x, y, width, height, type, playerName) {
	setHealth(health);
	setMaxHealth(health);
	movementCountdown = 2;
	this->playerToAttack = playerToAttack;
	PubSub::subscribe("action", this);
}

EnemyEntity::~EnemyEntity()
{
	PubSub::unsubscribe("action", this);
	PubSub::unsubscribe("entity", this);
}

void EnemyEntity::tick()
{

	//// enemy will move SE
	//if (playerToAttack->getXPos() > this->getXPos() && playerToAttack->getYPos() > this->getYPos()) {

	//}
	////enemy will move SW
	//else if (playerToAttack->getXPos() < this->getXPos() && playerToAttack->getYPos() > this->getYPos()) {

	//}
	////enemy will move NW
	//else if (playerToAttack->getXPos() < this->getXPos() && playerToAttack->getYPos() < this->getYPos()) {

	//}
	////enemy will move NE
	//else if (playerToAttack->getXPos() > this->getXPos() && playerToAttack->getYPos() < this->getYPos()) {

	//}
	//enemy will move N
	if (movementCountdown != 0 && stunnedCountdown==0) {
		if (playerToAttack->getYPos() < this->getYPos()) {
			if (getYPos() > 0) {
				targetX = getXPos();
				targetY = getYPos() - 1;
				setSpeedX(0);
				setSpeedY(- 1);
				setMoving(true);
				setFacing(up);
				movementCountdown = 2;
			}
		}
		//enemy will move S
		else if (playerToAttack->getYPos() > this->getYPos()) {
			if (getYPos() > 0) {
				targetX = getXPos();
				targetY = getYPos() + 1;
				setSpeedX(0);
				setSpeedY(1);
				setMoving(true);
				setFacing(down);
				movementCountdown = 2;
			}
		}
		//enemy will move E
		else if (playerToAttack->getXPos() < this->getXPos()) {
			if (getXPos() < screenWidth - getWidth()) {
				targetX = getXPos() - 1;
				targetY = getYPos();
				setSpeedX(-1);
				setSpeedY(0);
				setMoving(true);
				setFacing(left);
				movementCountdown = 2;
			}
		}
		//enemy will move W
		else if (playerToAttack->getXPos() > this->getXPos()) {
			if (getXPos() < screenWidth - getWidth()) {
				targetX = getXPos() + 1;
				targetY = getYPos();
				setSpeedX(1);
				setSpeedY(0);
				setMoving(true);
				setFacing(right);
				movementCountdown = 2;
			}
		}
	}
	else {
		if (stunnedCountdown != 0) {
			stunnedCountdown--;
			movementCountdown = -1;
		}
	}
	


	if (movementCountdown > 0)
	{

		movementCountdown--;

		if (movementCountdown == 0)
		{
			setMoving(false);
			setXPos(targetX);
			setYPos(targetY);

		}
		else
		{
			setXPos(getXPos() + getSpeedX());
			setYPos(getYPos() + getSpeedY());

		}
	}
}

void EnemyEntity::receiveMessage(string channel, string message, void* data) {
	if (channel == "action" && message == "attack") {
		Entity* entity = (Entity*)data;
		if (entity->getType() == jerry) {
			PlayerEntity* attacker = (PlayerEntity*) entity;
			Rectangle thisEntityRectangle = { getXPos(),getYPos(),getWidth(), getHeight() };
			Rectangle attackerRectangle{};
			switch (attacker->getFacing()) {
			case right:
				attackerRectangle = { attacker->getXPos() + attacker->getWidth(),attacker->getYPos(),attacker->getAttackRange(),(float)attacker->getHeight()};
				break;
			case left:
				attackerRectangle = { attacker->getXPos()  - attacker->getAttackRange(),attacker->getYPos(),attacker->getAttackRange(),(float)attacker->getHeight() };
				break;
			case up:
				attackerRectangle = {attacker->getXPos(), attacker->getYPos() - attacker->getAttackRange(),(float)attacker->getWidth(),attacker->getAttackRange() };
				break;
			case down:
				attackerRectangle = { attacker->getXPos(), attacker->getYPos() + attacker->getHeight(),(float)attacker->getWidth(),attacker->getAttackRange() };
				break;
			}
			if (CheckCollisionRecs(thisEntityRectangle, attackerRectangle)) {
				setHealth(getHealth() - attacker->getPower());
				
			}
		}
	}
}

bool EnemyEntity::handleCollision() {
	
		for (Entity* entity : collisions) {
			if (entity->getType() == jerry && stunnedCountdown == 0) {
				PubSub::publish("entity", "hit", entity);
				stunnedCountdown = 90;
			}
	
	}
	collisions.clear();
	return false;
}
