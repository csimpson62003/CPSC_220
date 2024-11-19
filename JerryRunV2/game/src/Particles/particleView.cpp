#include "particleView.h"
#include <map>

struct SpriteSheetInfo
{
    string fileName;
    int numFrames = 0;
    map<ParticleDirection, int> facings;
};
using namespace std;
map<ParticleType, SpriteSheetInfo> spriteMapping = {
    {
    attackParticle,
    {"resources/attackparticles.png",1, {
        {up_direction, 0}
}}
    }
};

ParticleView::ParticleView(Particles* particle)
{
	this->particle = particle;
    texture = Textures::loadTexture(spriteMapping[particle->getParticleType()].fileName);
    if(particle->getParticlesEntity()->getFacing() == up){
        this->xCoordinate = this->particle->getXCoordinate();
        this->yCoordinate = this->particle->getYCoordinate() + 30;
    }
}

bool ParticleView::isViewFor(Particles* particle)
{
	return false;
}

void ParticleView::draw()
{
    int numFrames = spriteMapping[particle->getParticleType()].numFrames;


    int frameWidth = texture.width / numFrames;
    int row = spriteMapping[particle->getParticleType()].facings[particle->getParticleDirection()];

    if (particle->getDuration() > 0) {
        particle->setDuration(particle->getDuration() - 1);
        DrawTexture(this->texture, xCoordinate, yCoordinate, WHITE);
    }
}
