#include "worldView.h"
#include "textures.h"
#include "raylib.h"
#include <string>

WorldView::WorldView()
{
	this->background = Textures::loadTexture("resources/Grass.png");
    this->width = background.width;
    this->height = background.height;
}


void WorldView::draw(int coins, int worldLevel, int deletedEnemies) {

    // Source rectangle: part of the texture to be drawn (the specific frame)
    Rectangle srcRec = { 0,0,width,height };


    // Destination rectangle: where to draw the sprite on screen (with scaling)
    Rectangle destRec = { 0,0,screenWidth, screenHeight };


    // Draw the texture region to the screen using the destination rectangle
    //Draw Player Name

    //Draw Entity Texture
    DrawTexturePro(background, srcRec, destRec, { 0, 0 }, 0.0f, WHITE);
    string coinText = "Coins: " + std::to_string(coins);
    string levelText = "Level " + std::to_string(worldLevel);
    string enemiesKilled = "Enemies Killed: " + std::to_string(deletedEnemies);
    Rectangle whiteBoxWrap = { screenWidth - 310, 55, 290, 70 };
    DrawRectangleRec(whiteBoxWrap, WHITE);
    DrawText(coinText.c_str(), screenWidth-300, 10, 50, BLACK);
    DrawText(levelText.c_str(), screenWidth-300, 60, 30, BLACK);
    DrawText(enemiesKilled.c_str(), screenWidth-300, 90, 30, BLACK);


}

void WorldView::deathScreenDraw(int worldLevel, int deletedEnemies) {

    // Source rectangle: part of the texture to be drawn (the specific frame)
    Rectangle srcRec = { 0,0,width,height };


    // Destination rectangle: where to draw the sprite on screen (with scaling)
    Rectangle destRec = { 0,0,screenWidth, screenHeight };


    // Draw the texture region to the screen using the destination rectangle
    //Draw Player Name

    //Draw Entity Texture
    DrawTexturePro(background, srcRec, destRec, { 0, 0 }, 0.0f, GRAY);
    string levelText = "You made it to level " + std::to_string(worldLevel);
    string enemiesKilled = "Enemies Killed: " + std::to_string(deletedEnemies);
    DrawText(levelText.c_str(), screenWidth/4, screenHeight/4, 100, WHITE);
    DrawText(enemiesKilled.c_str(), screenWidth/4, screenHeight/2, 100, WHITE);


}