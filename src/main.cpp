#include "../include/master.hpp"

int main(void)
{

    Image icon = LoadImage("../resources/aaa_logo.png");
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(icon);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids and Aliens");

    SetTargetFPS(60);

    Game& game = Game::GetGame();

    while (game.Running())
    {
        game.Update();
        game.Render();
    }

    UnloadImage(icon);
    CloseWindow();
}