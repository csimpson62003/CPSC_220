// SameGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "model.h"
#include "view.h"
#include "raylib.h"
#include "Square.h"
#include <vector>
#include <string>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;
using namespace this_thread;

void play();
int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Same Game");
    SetTargetFPS(60);

    play();

    CloseWindow();
}

void play() {
    GameBoard gb;
    view view(gb);
    int numberOfMoves = 0;
    string scoreText;
    while (!WindowShouldClose()) {
            BeginDrawing();

            view.display();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Capture the mouse position
                Vector2 mousePosition = GetMousePosition();
                if (gb.getColor(mousePosition.y / 200, mousePosition.x / 200) != Colors::Empty) {
                    gb.remove(mousePosition.y / 200, mousePosition.x / 200);
                    numberOfMoves++;
                    string text = "Score: ";
                    scoreText = text + std::to_string(numberOfMoves);
                }
            }
            while (gb.stillFloatingColors()) {
                continue;
            }

            DrawText(scoreText.c_str(), 5, 10, 50, BLACK);
            EndDrawing();
            while (!gb.stillColors() && !WindowShouldClose()) {
                view.display();
                BeginDrawing();
                string text = "Score: ";
                scoreText = text + std::to_string(numberOfMoves);
                DrawText(scoreText.c_str(), 5, 10, 50, RED);
                DrawText("Game Over", 300, 200, 50, BLACK);
                DrawText("Click Anywhere to end", 300, 300, 50, BLACK);
                EndDrawing();
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    CloseWindow();
                    return;
                }
            }

        }
        EndDrawing();

    CloseWindow();

}



  
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
