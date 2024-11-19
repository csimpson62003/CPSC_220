#include "screenView.h"
#include "textures.h"
#include "raylib.h"
#include <string>

ScreenView::ScreenView(vector<PowerUps*> powerUpsArray)
{
    this->background = Textures::loadTexture("resources/streets.png");
    this->width = background.width;
    this->height = background.height;
    this->powerUpsArray = powerUpsArray;
}

void ScreenView::drawBackground(int viewportX, int viewportY, int viewportWidth, int viewportHeight) {


    // Source rectangle: part of the texture to be drawn (the specific frame)
    Rectangle srcRec = {viewportX, viewportY,viewportWidth,viewportHeight};


    // Destination rectangle: where to draw the sprite on screen (with scaling)
    Rectangle destRec = {0,0, viewportWidth, viewportHeight};



    // Draw the texture region to the screen using the destination rectangle
    //Draw Player Name

    //Draw Entity Texture
    DrawTexturePro(background, srcRec, destRec, {0,0}, 0.0f, WHITE);

}
void ScreenView::draw(int coins, int worldLevel, int deletedEnemies, int viewportX, int viewportY, int viewportDrawX, int viewportDrawY,  int viewportWidth, int viewportHeight) {

 
    string coinText = "Coins: " + std::to_string(coins);
    string levelText = "Level " + std::to_string(worldLevel);
    string enemiesKilled = "Enemies Killed: " + std::to_string(deletedEnemies);
    DrawText(levelText.c_str(), (viewportWidth)-300, 10, 50, BROWN);
    DrawText(coinText.c_str(), (viewportWidth)-300, 60, 30, GRAY);
    DrawText(enemiesKilled.c_str(), (viewportWidth)-300, 90, 30, {20,20,20,255});

    //Drawing powerups
    for (int i = 0; i < powerUpsArray.size(); i++) {
        
        if (hitbox) {
            DrawRectangle(powerUpsArray[i]->getXPos(), powerUpsArray[i]->getYPos(), powerUpsArray[i]->getWidth(), powerUpsArray[i]->getHeight(), RED);

        }
        DrawTexturePro(powerUpsArray[i]->getTexture(), { 0,0,32,32 }, { powerUpsArray[i]->getXPos(),powerUpsArray[i]->getYPos(),powerUpsArray[i]->getWidth(),powerUpsArray[i]->getHeight()}, {0, 0}, 0.0f, WHITE);
        //the powerup level and price of station
        int fontSize = 6 * hudScale;
        string levelText = "lvl. "+ to_string((powerUpsArray[i]->getLevel()));
        string costText = "$" + to_string(powerUpsArray[i]->getCost());
        DrawText((costText+ " " +levelText).c_str(), powerUpsArray[i]->getXPos(), powerUpsArray[i]->getYPos() + powerUpsArray[i]->getHeight() + (fontSize / 2.5) + 10, fontSize, WHITE);
    }
}

void ScreenView::deathScreenDraw(int worldLevel, int deletedEnemies, int viewportDrawX, int viewportDrawY, int viewportWidth, int viewportHeight) {

    // Source rectangle: part of the texture to be drawn (the specific frame)
    Rectangle srcRec = { 0,0,width,height };


    // Destination rectangle: where to draw the sprite on screen (with scaling)
    Rectangle destRec = {viewportDrawX, viewportDrawY, viewportWidth, viewportHeight};


    // Draw the texture region to the screen using the destination rectangle
    //Draw Player Name

    //Draw Entity Texture
    DrawTexturePro(background, srcRec, destRec, { 0, 0 }, 0.0f, GRAY);
    string levelText = "You made it to level " + std::to_string(worldLevel);
    string enemiesKilled = "Enemies Killed: " + std::to_string(deletedEnemies);
    DrawText(levelText.c_str(), viewportWidth / 4, viewportHeight / 4, 100, WHITE);
    DrawText(enemiesKilled.c_str(), viewportWidth / 4, viewportHeight / 2, 100, WHITE);


}