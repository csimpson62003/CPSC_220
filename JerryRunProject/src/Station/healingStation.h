#ifndef HEALINGSTATION_H
#define HEALINGSTATION_H

#include "../entity.h"
#include "../pubSub.h"

using namespace std;

class HealingStation : public Entity, public Subscriber {

private:
	int buyTimer = 0;
public:
	HealingStation(float x, float y, int width, int height, EntityType type, string playerName,int price);
	void tick();
	void receiveMessage(string channel, string name, void* data);
	bool handleCollision();
};



#endif