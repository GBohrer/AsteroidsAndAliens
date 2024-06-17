
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{
    bool show_text = true;
    bool IsGameRunning = true;
    float camera_zoom;

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
           GameState currentState = game.GetGameState();

           if (currentState == GameState::InGame) {
               game.SetGameState(GameState::Paused);
           } else if (currentState == GameState::Paused) {
               game.SetGameState(GameState::InGame);
           }
        }

        switch (game.GetGameState()) {
            case GameState::Menu:
                if (IsKeyPressed(KEY_ENTER)) game.Start("Nickname");
                if (IsKeyPressed(KEY_ESCAPE)) IsGameRunning = false;
                break;

            case GameState::Paused:
                
                break;
            
            case GameState::InGame:
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) game.PlayerMove();
                if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) game.SpawnBullets();

                camera_zoom = game.GetCamera().zoom;
                camera_zoom += ((float)GetMouseWheelMove()*0.1f);

                if (camera_zoom > 2.0f) camera_zoom = 2.0f;
                else if (camera_zoom < 0.25f) camera_zoom = 0.25f;

                game.SetCameraZoom(camera_zoom);

                if (game.CheckDifficultyIncrease(game.GetPlayer().GetScore())){ game.IncreaseDifficulty();}

                game.UpdateAnimationTime();
                game.SpawnAliens();
                game.CheckEntityCollisions();

                break;

            case GameState::GameOver:
                if (IsKeyPressed(KEY_ENTER)) game.Reset();

                break;
        }

        /// RENDERS
        BeginDrawing();

        switch (game.GetGameState()) {
            case GameState::Menu:
                ClearBackground(color_space_background);
                DrawText("GALACTIC ADVENTURES", 400, (int)GetScreenHeight()/2.0f - 200, 90, WHITE);
                DrawText("Press ENTER to start", (int)GetScreenWidth()/2.0f - 200, (int)GetScreenHeight()/2.0f - 50, 40, WHITE);

                break;

            case GameState::Paused:
                //ClearBackground(color_space_background);
                DrawText("PAUSE", (int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f, 35, WHITE);
                break;
            
            case GameState::InGame:
                ClearBackground(color_space_background);

                BeginMode2D(game.GetCamera());

                    game.GetPlayer().DrawHitBox();

                    for (Alien& a : game.GetCurrentAliens()){ a.DrawHitBox(); a.DrawDirectionVector(); }
                    for (Bullet& b : game.GetCurrentBullets()){b.DrawHitBox(); }

                    if (show_text) {
                        for (int i = 0; i < game.GetAliensInGame(); i++){
                            PrintTextInGame(false, i, game.GetCurrentAliens()[i].GetPosition(), 20, WHITE);
                        }
                    }
                EndMode2D();

                PrintTextInGame(true, game.GetCamera().zoom, {50,50}, 30, WHITE);
                PrintTextInGame(false, game.GetPlayer().GetScore(), {GetScreenWidth()/2.0f, 70}, 50, WHITE);
                
                PrintTextInGame(false, game.GetPlayer().GetPosition().x, {GetScreenWidth()/2.0f, GetScreenHeight() - 120.0f}, 30, WHITE);
                PrintTextInGame(false, game.GetPlayer().GetPosition().y, {GetScreenWidth()/2.0f, GetScreenHeight() - 90.0f}, 30, WHITE);

                break;

            case GameState::GameOver:
                DrawText("GAME OVER", 500, (int)GetScreenHeight()/2.0f - 200, 90, WHITE);
                DrawText("Press ENTER to return to the Menu", (int)GetScreenWidth()/2.0f - 150, (int)GetScreenHeight()/2.0f - 50, 40, WHITE);

                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}