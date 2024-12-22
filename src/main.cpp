#include "../include/master.hpp"

int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids and Aliens");
     
    SetTargetFPS(60);

    Game& game = Game::GetGame();

    while (game.Running())
    {
        game.Update();
        game.Render();
    }

    CloseWindow();
}