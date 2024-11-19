#ifndef PARTICLEVIEW_H
#define PARTICLEVIEW_H

#include "raylib.h"
#include "world.h";
#include "particles.h"
#include "textures.h"
#include "../entity.h"

class ParticleView
{
private:
	Particles* particle;
	Texture2D texture;
	int frame;
	float xCoordinate, yCoordinate;

public:
	ParticleView(Particles* particle);
	bool isViewFor(Particles* particle);
	void draw();
};



#endif