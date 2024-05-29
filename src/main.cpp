#include <raylib.h>
#include "ball.h"

int main()
{
    Color basicColor1 = Color{200, 200, 245, 255};

    const int screenWidth = 1280;
    const int screenHeight = 920;

    Ball ball = Ball();

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");
    SetTargetFPS(60);
    HideCursor();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(basicColor1);
        DrawText("P1", ball.GetX()-15, ball.GetY()-40,25, BLACK);
        ball.DiagonalMove();
        ball.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}