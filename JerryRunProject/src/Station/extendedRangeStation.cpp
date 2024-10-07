#include "../world.h"
#include "extendedRangeStation.h"
ExtendedRangeStation::ExtendedRangeStation(float x, float y, int width, int height, EntityType type, string playerName, int price):Entity(x, y, width, height, type, playerName)
{
	PubSub::subscribe("extendedRange", this);
	PubSub::subscribe("action", this);
	this->price = price;
	this->setLevel(1);
	this->setHealth(1);
}

void ExtendedRangeStation::tick()
{
	if (buyTimer != 0) {
		buyTimer--;
	}
}

void ExtendedRangeStation::receiveMessage(string channel, string name, void* data)
{
	
}

bool ExtendedRangeStation::handleCollision()
{
	for (Entity* entity : collisions) {
		if (entity->getType() == jerry && buyTimer == 0) {
			PubSub::publish("entity", "buyStation", this);
		}
	}
	collisions.clear();
	return false;
}
