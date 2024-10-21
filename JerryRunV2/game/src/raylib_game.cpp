#include "raylib.h"

#include <math.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Following eyes");

    Vector2 scleraLeftPosition = { GetScreenWidth() / 2.0f - 100.0f, GetScreenHeight() / 2.0f };
    Vector2 scleraRightPosition = { GetScreenWidth() / 2.0f + 100.0f, GetScreenHeight() / 2.0f };
    float scleraRadius = 80;

    Vector2 irisLeftPosition = { GetScreenWidth() / 2.0f - 100.0f, GetScreenHeight() / 2.0f };
    Vector2 irisRightPosition = { GetScreenWidth() / 2.0f + 100.0f, GetScreenHeight() / 2.0f };
    float irisRadius = 24;

    float angle = 0.0f;
    float dx = 0.0f, dy = 0.0f, dxx = 0.0f, dyy = 0.0f;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        irisLeftPosition = GetMousePosition();
        irisRightPosition = GetMousePosition();

        // Check not inside the left eye sclera
        if (!CheckCollisionPointCircle(irisLeftPosition, scleraLeftPosition, scleraRadius - 20))
        {
            dx = irisLeftPosition.x - scleraLeftPosition.x;
            dy = irisLeftPosition.y - scleraLeftPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius) * cosf(angle);
            dyy = (scleraRadius - irisRadius) * sinf(angle);

            irisLeftPosition.x = scleraLeftPosition.x + dxx;
            irisLeftPosition.y = scleraLeftPosition.y + dyy;
        }

        // Check not inside the right eye sclera
        if (!CheckCollisionPointCircle(irisRightPosition, scleraRightPosition, scleraRadius - 20))
        {
            dx = irisRightPosition.x - scleraRightPosition.x;
            dy = irisRightPosition.y - scleraRightPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius) * cosf(angle);
            dyy = (scleraRadius - irisRadius) * sinf(angle);

            irisRightPosition.x = scleraRightPosition.x + dxx;
            irisRightPosition.y = scleraRightPosition.y + dyy;
        }
        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(scleraLeftPosition, scleraRadius, LIGHTGRAY);
        DrawCircleV(irisLeftPosition, irisRadius, BROWN);
        DrawCircleV(irisLeftPosition, 10, BLACK);

        DrawCircleV(scleraRightPosition, scleraRadius, LIGHTGRAY);
        DrawCircleV(irisRightPosition, irisRadius, DARKGREEN);
        DrawCircleV(irisRightPosition, 10, BLACK);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}