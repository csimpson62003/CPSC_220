#include "../world.h"
#include "healingStation.h"

HealingStation::HealingStation(float x, float y, int width, int height, EntityType type, string playerName, int price):Entity(x, y, width, height, type, playerName)
	{
	PubSub::subscribe("healing", this);
	PubSub::subscribe("action", this);
	this->price = price;
	this->setLevel(1);
	this->setHealth(1);
	};
void HealingStation::tick() {
	if (buyTimer != 0) {
		buyTimer--;
	}
}


void HealingStation::receiveMessage(string channel, string message, void* data) {

}

bool HealingStation::handleCollision()
{

	for (Entity* entity : collisions) {
		if (entity->getType() == jerry && buyTimer==0) {
			if (entity->getMaxHealth() != entity->getHealth()) {
				PubSub::publish("entity", "buyStation", this);
				buyTimer = 90;
			}
		}
	}
	collisions.clear();
	return false;
}
