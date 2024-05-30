#include <raylib.h>
#include "../include/master_header.h"
#include <string>
#include <iostream>

int main()
{
    Color basicColor1 = Color{200, 200, 245, 255};

    const int screenWidth = 500;
    const int screenHeight = 500;

    Ball ball = Ball(10);
    Player p1 = Player("Gabriel");

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");
    SetTargetFPS(60);
    //HideCursor();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(basicColor1);
        DrawText("P1", ball.GetPosition().GetX(), ball.GetPosition().GetY(),25, BLACK);
        ball.DiagonalMove();
        ball.Draw();
    
        EndDrawing();
    }

    

    CloseWindow();
    return 0;
}