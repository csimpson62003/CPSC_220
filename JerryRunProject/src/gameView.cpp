#include <map>
#include <string>
#include "gameView.h"
#include "textures.h"
#include "raylib.h"

struct SpriteSheetInfo
{
	string fileName;
	int numFrames = 0;
	map<EntityFacing, int> facings;
};
using namespace std;
map<EntityType, SpriteSheetInfo> spriteMapping = {
	{jerry, {"resources/nakedDude.png", 4, {
		{right, 2},
		{up, 1},
		{down, 0},
		{left, 3}}
	}},
	{portal, {"resources/GlowingWisp.png", 4, {
		{right, 0}}
	}},

    //extend range station
    {extendedRangeStation, {"resources/ExtendedRange.png", 4, {
        {right, 0}}
    }},
    //Healing station
    {healingStation, {"resources/HealingStation.png", 4, {
        {right, 0}}
    }},
    //Power Station
    {powerStation, {"resources/PowerStation.png", 4, {
        {right, 0}}
    }},
    //Speed Station
    {speedStation, {"resources/Speed.png", 4, {
        {right, 0}}
    }},
    {
enemy, {"resources/zombie.png", 4, {
   {right, 2},
   {up, 1},
   {down, 0},
   {left, 3}}
}
}
};

EntityView::EntityView(Entity* entity)
{
	this->entity = entity;
	texture = Textures::loadTexture(spriteMapping[entity->getType()].fileName);
	frame = 0;
	delay = 0;
}

bool EntityView::isViewFor(Entity* entity)
{
	return this->entity == entity;
}

void EntityView::draw()
{
        int animationDelay = 20;
        int numFrames = spriteMapping[entity->getType()].numFrames;

        if (entity->getMoving())
        {
            delay--;

            if (delay <= 0)
            {
                frame = (frame + 1) % numFrames;
                delay = animationDelay;
            }
        }
        else if (entity->getType() != enemy && entity->getType() != jerry) {
            delay--;

            if (delay <= 0)
            {
                frame = (frame + 1) % numFrames;
                delay = animationDelay;
            }
        }
        else
        {
            frame = 0;
            delay = animationDelay;
        }

        int frameWidth = texture.width / numFrames;
        int row = spriteMapping[entity->getType()].facings[entity->getFacing()];

        // Source rectangle: part of the texture to be drawn (the specific frame)
        Rectangle srcRec = {
            (frame * frameWidth),
            (row * frameWidth),
            frameWidth ,
            frameWidth };


        // Destination rectangle: where to draw the sprite on screen (with scaling)
        Rectangle destRec = {
            entity->getXPos(),
            entity->getYPos(),
            frameWidth * scale,    // Scaled width
            frameWidth* scale     // Scaled height (same as width for a square frame)
        };

        // Draw the texture region to the screen using the destination rectangle
        //Draw Player Name && the hit range circle
        if (entity->getType() == jerry) {
            PlayerEntity* player = (PlayerEntity*)entity;
            float circleX, circleY;
            switch (player->getFacing()) {
            case right:
                circleX = player->getWidth() + player->getXPos() + player->getAttackRange();
                circleY = player->getYPos() + (player->getHeight() / 2);
                break;
            case left:
                circleX = player->getXPos() - player->getAttackRange();
                circleY = player->getYPos() + (player->getHeight() / 2);
                break;
            case up:
                circleX = player->getXPos() + (player->getWidth() / 2);
                circleY = player->getYPos() - player->getAttackRange();;
                break;
            case down:
                circleX = player->getXPos() + (player->getWidth() / 2);
                circleY = player->getYPos() + player->getHeight() + player->getAttackRange();
                break;
            default:
                circleX = player->getWidth() + player->getXPos() + player->getAttackRange();
                circleY = player->getYPos() + (player->getHeight() / 2);
            }
            DrawCircle(circleX, circleY, 3, RED);

        }
        //Draw Level, if station has it:
        else if (entity->getLevel() != -1) {
            string nameAndLevel = entity->getEntityName();
            nameAndLevel += " " + to_string((entity->getLevel()));
            string cost = "Cost: $" + to_string((entity->getPrice()));
            int fontSize = 15;
            DrawText(nameAndLevel.c_str(), (entity->getXPos() + (entity->getWidth()/2)) - fontSize*2, entity->getYPos() + entity->getHeight() + 15, fontSize, BLACK);
            DrawText(cost.c_str(), (entity->getXPos() + (entity->getWidth()/2)) - fontSize*2, entity->getYPos() + entity->getHeight() + fontSize +15, fontSize, BLACK);
        }

        //Draw Entity Texture
        DrawTexturePro(texture, srcRec, destRec, { 0, 0 }, 0.0f, WHITE);
        //Draw Entity Hitbox
        if (hitbox) {
            DrawRectangleLines(entity->getXPos(), entity->getYPos(), entity->getWidth(), entity->getHeight(), GREEN);
        }
        //Draw Entity Health
        float healthBarWidth = (entity->getWidth()) * (entity->getHealth() / entity->getMaxHealth());
        float healthBarHeight = 20;
        
            // Draw inner healthBar
            DrawRectangle(entity->getXPos(), entity->getYPos() - 20, healthBarWidth, 10, RED);

            //Draw outer HealthBar Line
            DrawRectangleLines(entity->getXPos(), entity->getYPos() - 20, entity->getWidth(), 10, BLACK);
        
        
}