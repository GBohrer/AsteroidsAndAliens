
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{
    bool show_text = true;
    bool IsGameRunning = true;

    const int screenWidth  = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    SetTargetFPS(60);

    Game game = Game();

    while (IsGameRunning)
    {

        /// UPDATES
        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_T)) show_text = !show_text;
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (game.GetGameState() != GameState::Menu){
                if (game.GetGameState() == GameState::Paused){
                    game.SetGameState(GameState::InGame);
                } else { game.SetGameState(GameState::Paused);}
            }
        }

        switch (game.GetGameState()) {
            case GameState::Menu:

                break;

            case GameState::Paused:
                
                break;
            
            case GameState::InGame:
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) game.PlayerMove();
                if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) game.SpawnBullets();

                if (game.CheckDifficultyIncrease(game.GetPlayer().GetScore())){ game.IncreaseDifficulty();}

                game.UpdateAnimationTime();
                game.SpawnAliens();
                game.CheckEntityCollisions();

                break;

            case GameState::GameOver:
                IsGameRunning = false;

                break;
        }

        /// RENDERS
        BeginDrawing();

        switch (game.GetGameState()) {
            case GameState::Menu:

                break;

            case GameState::Paused:
                //PrintTextInGame(false, game.GetPlayer().GetScore(), {GetScreenWidth()/2.0f, 70}, 50, WHITE);
                DrawText("PAUSE", (int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f, 35, WHITE);
                break;
            
            case GameState::InGame:
                ClearBackground(color_space_background);

                game.GetPlayer().DrawHitBox();
                PrintTextInGame(false, game.GetPlayer().GetScore(), {GetScreenWidth()/2.0f, 70}, 50, WHITE);

                for (Alien& a : game.GetCurrentAliens()){ a.DrawHitBox(); }
                for (Bullet& b : game.GetCurrentBullets()){b.DrawHitBox(); }

                if (show_text) {
                    for (int i = 0; i < game.GetAliensInGame(); i++){
                        PrintTextInGame(false, i, game.GetCurrentAliens()[i].GetPosition(), 20, WHITE);
                    }
                }
                break;

            case GameState::GameOver:

                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}