#include "../include/master.hpp"

int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arcade Space Shooter");
     
    SetTargetFPS(60);

    Game& game = Game::GetGame();

    while (game.Running())
    {
        game.Update();
        game.Render();
    }

    CloseWindow();
}