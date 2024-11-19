#include "health.h"
#include "./playerEntity.h"
Health::Health(int x, int y, int width, int height, PowerUpType type, int cost, int level):PowerUps(type, x, y, width, height)
{
	this->setCost(cost);
	this->setLevel(level);
	PubSub::subscribe("power_up", this);
}

void Health::tick()
{

}

void Health::receiveMessage(string channel, string message, void* data)
{
	if (channel == "power_up" && message == "buy") {
		PowerUps* pu = (PowerUps*)data;
		if (pu == this){}
		player->setHealth(player->getMaxHealth());
		this->setCost(this->getCost() * 1.5);
	}
}
