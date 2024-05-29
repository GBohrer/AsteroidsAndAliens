#include <raylib.h>
#include "spaceship.h"

int main()
{
    Color darkGreen = Color{30, 160, 133, 255};

    const int screenWidth = 1280;
    const int screenHeight = 920;

    Spaceship player = Spaceship();

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        player.Update();
        player.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}