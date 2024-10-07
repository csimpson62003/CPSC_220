#include "../world.h"
#include "speedStation.h"

SpeedStation::SpeedStation(float x, float y, int width, int height, EntityType type, string playerName, int price) :Entity(x, y, width, height, type, playerName)
{
	PubSub::subscribe("healing", this);
	PubSub::subscribe("action", this);
	this->price = price;
	this->setLevel(1);
	this->setHealth(1);
};
void SpeedStation::tick() {
	if (buyTimer != 0) {
		buyTimer--;
	}
}


void SpeedStation::receiveMessage(string channel, string message, void* data) {

}

bool SpeedStation::handleCollision()
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
