
#include "../include/master_header.h"

// COMMON-VARIABLES
Color Background_Color = Color{200, 200, 245, 255};


int main()
{

    const int screenWidth = 500;
    const int screenHeight = 500;

    Alien alien = Alien(30, 30, 25, 1);
    Player p1 = Player("Gabriel");

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");
    SetTargetFPS(60);
    //HideCursor();

    while (!WindowShouldClose())
    {
    /// UPDATES



    /// RENDERS
        BeginDrawing();

        ClearBackground(Background_Color);
        //DrawText("P1", alien.GetPosition().GetX(), alien.GetPosition().GetY(),25, BLACK);
        alien.Draw();
        p1.Draw();
    
        EndDrawing();
    }

    

    CloseWindow();
    return 0;
}