#include "../world.h"
#include "powerStation.h"

PowerStation::PowerStation(float x, float y, int width, int height, EntityType type, string playerName, int price) :Entity(x, y, width, height, type, playerName)
	{
	PubSub::subscribe("powerStation", this);
	PubSub::subscribe("action", this);
	this->price = price;
	this->setLevel(1);
	this->setHealth(1);
	};
void PowerStation::tick() {
	if (buyTimer != 0) {
		buyTimer--;
	}
}


void PowerStation::receiveMessage(string channel, string message, void* data) {

}

bool PowerStation::handleCollision()
{
	for (Entity* entity : collisions) {
		if (entity->getType() == jerry && buyTimer == 0) {
			PubSub::publish("entity", "buyStation", this);
			buyTimer = 90;
		}
	}
	collisions.clear();
	return false;
}
