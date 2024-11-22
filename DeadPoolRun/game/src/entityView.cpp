#include <map>
#include <string>
#include "entityView.h"
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
    {Deadpool, {"resources/nakedDude.png", 4, {
        {right, 2},
        {up, 1},
        {down, 0},
        {left, 3}}
    }},
    {portal, {"resources/GlowingWisp.png", 4, {
        {right, 0}}
    }},
    {
zombie, {"resources/zombie.png", 4, {
   {right, 2},
   {up, 1},
   {down, 0},
   {left, 3}}
}
},
  {
clown, {"resources/clown.png", 4, {
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

void EntityView::draw(int vx, int vy, int vdx, int vdy, int vw, int vh)
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
    else if (entity->getType() != zombie && entity->getType() != Deadpool && entity->getType() != clown) {
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
    Rectangle entityDestRec = {
       (entity->getXPos() - vx) + vdx,
        (entity->getYPos() - vy) + vdy,
        frameWidth * scale,    // Scaled width
        frameWidth * scale     // Scaled height (same as width for a square frame)
    };

    DrawTexturePro(this->texture, srcRec, entityDestRec, {0,0}, 0,RAYWHITE);

    //Drawing the player health
    //First the fillbox
     //Draw Entity Health
    float healthBarWidth = (entity->getWidth()) * (entity->getHealth() / entity->getMaxHealth());
    float healthBarHeight = 20;

    // Draw inner healthBar
    DrawRectangle(entityDestRec.x, entityDestRec.y - 20, healthBarWidth, 10, RED);

    //Draw outer HealthBar Line
    DrawRectangleLines(entityDestRec.x, entityDestRec.y - 20, entity->getWidth(), 10, BLACK);


    //Draw the circle of the player range
    if (entity->getType() == Deadpool) {

        Rectangle entityDestRec = {
       (entity->getXPos() - vx) + vdx,
        (entity->getYPos() - vy) + vdy,
        frameWidth * scale,    // Scaled width
        frameWidth * scale     // Scaled height (same as width for a square frame)
        };

        PlayerEntity* player = (PlayerEntity*)entity;
        float circleX, circleY;
        switch (player->getFacing()) {
        case right:
            circleX = entityDestRec.x + entityDestRec.width + player->getAttackRange();
            circleY = entityDestRec.y + (entityDestRec.height/2);
            break;
        case left:
            circleX = entityDestRec.x - player->getAttackRange();
            circleY = entityDestRec.y + (entityDestRec.height / 2);
            break;
        case up:
            circleX = entityDestRec.x + (entityDestRec.width / 2);
            circleY = entityDestRec.y - player->getAttackRange();
            break;
        case down:
            circleX = entityDestRec.x + (entityDestRec.width / 2);
            circleY = entityDestRec.y + entityDestRec.height + player->getAttackRange();
            break;
        default:
            circleX = entityDestRec.x - (entityDestRec.width / 2);
            circleY = entityDestRec.y - player->getAttackRange();
        }
        DrawCircle(circleX, circleY, 5, BLUE);
        DrawCircleLines(circleX, circleY, 6, DARKBLUE);

    }

}