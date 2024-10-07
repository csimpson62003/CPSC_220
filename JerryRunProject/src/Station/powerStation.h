#ifndef POWERSTATION_H
#define POWERSTATION_H

#include "../entity.h"
#include "../pubSub.h"

using namespace std;

class PowerStation : public Entity, public Subscriber {

private:
	int buyTimer = 0;
public:
	PowerStation(float x, float y, int width, int height, EntityType type, string playerName, int price);
	void tick();
	void receiveMessage(string channel, string name, void* data);
	bool handleCollision();
};



#endif