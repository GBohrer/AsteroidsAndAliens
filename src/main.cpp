
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{
    bool IsGameRunning = true;

    const int screenWidth  = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    Rectangle textBox = { screenWidth/2.0f - 100, screenHeight/2.0f, 225, 50 };
    Rectangle textBox2 = { screenWidth/2.0f - 100, screenHeight/2.0f - 100, 225, 50 };

    SetTargetFPS(60);

    Game game = Game();

    while (IsGameRunning)
    {

        /// UPDATES
        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_X)) IsGameRunning = false;
        if (IsKeyPressed(KEY_G)) game.SetGameState(GameState::GameOver);

        if (IsKeyPressed(KEY_ESCAPE)) {
           GameState currentState = game.GetGameState();

           if (currentState == GameState::InGame) { game.SetGameState(GameState::Paused); }
           else if (currentState == GameState::Paused) { game.SetGameState(GameState::InGame); }
           else if (currentState == GameState::Menu) { IsGameRunning = false; }
        }

        switch (game.GetGameState()) {
            case GameState::Menu:
                if (IsKeyPressed(KEY_ENTER)) game.Start();
                break;

            case GameState::Paused:
            
                break;
            
            case GameState::InGame:
                game.UpdateAnimationTime();

                game.UpdatePlayer();
                if (IsKeyDown(KEY_SPACE)) game.SpawnBullets();

                if (game.CheckDifficultyIncrease(game.GetPlayer().GetScore())){ game.IncreaseDifficulty();}
                
                game.SpawnAliens();

                game.CheckEntityCollisions();

                game.UpdateCamera(GetScreenWidth(), GetScreenHeight());
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
                //DrawText("Press ENTER to start", (int)GetScreenWidth()/2.0f - 200, (int)GetScreenHeight()/2.0f - 50, 40, WHITE);

                DrawRectangleRec(textBox, LIGHTGRAY);
                DrawRectangleRec(textBox2, LIGHTGRAY);
                break;

            case GameState::Paused:
                DrawText("PAUSE", (int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f, 35, WHITE);
                break;
            
            case GameState::InGame:
                ClearBackground(color_space_background);

                BeginMode2D(game.GetCamera());

                    //Draw Level Boundries
                    DrawRectangleLinesEx( {0, 0,  game.GetCurrentLevelBounds().back().x,  game.GetCurrentLevelBounds().back().y}, 15.0f, PURPLE);

                    game.GetPlayer().DrawHitBox();
                    game.GetPlayer().DrawHeathBar();
                    game.GetPlayer().DrawAim();

                    for (Alien& a : game.GetCurrentAliens()) { 
                        a.DrawHitBox();
                        DrawRectangle(a.GetPosition().x - a.GetLife()/2.0f, a.GetPosition().y - a.GetRadius() - 20, (int)a.GetLife()*2, 10, GREEN);
                    }

                    for (Bullet& b : game.GetCurrentBullets()) { b.DrawHitBox(); } 
                    for (Entity& e : game.GetCurrentAsteroidsInGame()) {
                        DrawCircle(e.GetPosition().x, e.GetPosition().y, 15, WHITE);
                    }

                EndMode2D();

                //CAMERA ZOOM
                PrintTextInGame(true, game.GetCamera().zoom, {50,50}, 30, WHITE);
                // SCORE
                PrintTextInGame(false, game.GetPlayer().GetScore(), {(int)GetScreenWidth()/2.0f, 70}, 50, WHITE);
                //COORDS
                PrintTextInGame(false, game.GetPlayer().GetPosition().x, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 120.0f}, 30, WHITE);
                PrintTextInGame(false, game.GetPlayer().GetPosition().y, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 90.0f}, 30, WHITE);

                if (game.IsPlayerOutOfBounds()) {
                    DrawText("WARNING!!!", GetScreenWidth()/2.0f - 200, GetScreenHeight() - 300, 80, RED);
                    DrawText("The spaceship is entering the void",GetScreenWidth()/2.0f - 260, GetScreenHeight() - 220, 30, RED);
                }

                break;

            case GameState::GameOver:
                DrawText("GAME OVER", 500, (int)GetScreenWidth()/2.0f - 200, 90, WHITE);
                DrawText("Press ENTER to return to the Menu", (int)GetScreenWidth()/2.0f - 150, (int)GetScreenHeight()/2.0f - 50, 40, WHITE);
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}