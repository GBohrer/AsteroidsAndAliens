
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
        if (IsKeyPressed(KEY_X)) IsGameRunning = false;
        if (IsKeyPressed(KEY_G)) game.SetGameState(GameState::GameOver);

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

                if (game.CheckDifficultyIncrease(game.GetPlayer().GetScore())){ game.IncreaseDifficulty();}

                game.UpdateAnimationTime();
                game.SpawnAliens();
                game.CheckAliensCollisions();
                game.CheckBulletsCollisions();

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
                DrawText("Press ENTER to start", (int)GetScreenWidth()/2.0f - 200, (int)GetScreenHeight()/2.0f - 50, 40, WHITE);

                break;

            case GameState::Paused:
                DrawText("PAUSE", (int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f, 35, WHITE);
                break;
            
            case GameState::InGame:
                ClearBackground(color_space_background);
                DrawRectangle(0,0, 1000, 1000, color_space_background);

                BeginMode2D(game.GetCamera());

                    game.GetPlayer().DrawHitBox();
                    game.GetPlayer().DrawAimDirection();

                    for (Alien& a : game.GetCurrentAliens()){ a.DrawHitBox(); }
                    for (Bullet& b : game.GetCurrentBullets()){b.DrawHitBox(); }
                    for (Entity& e : game.GetCurrentAsteroidsInGame()) {
                        DrawCircle(e.GetPosition().x, e.GetPosition().y, 15, WHITE);
                    }

                    if (show_text) {
                        //Draw Aliens
                        for (int i = 0; i < game.GetAliensInGame(); i++){
                            Alien a = game.GetCurrentAliens()[i];
                            DrawRectangle(a.GetPosition().x - a.GetLife()/2.0f, a.GetPosition().y - a.GetRadius() - 20, (int)a.GetLife()*2, 10, GREEN);
                        }
                        //Draw Level Boundries
                        for (int i = 0; i < (int)game.GetCurrentLevelBounds().size(); i++){
                            Vector2 pos = game.GetCurrentLevelBounds()[i];
                            DrawCircle(pos.x, pos.y, 10.0f, ORANGE);
                        }
                    }
                EndMode2D();

                PrintTextInGame(true, game.GetCamera().zoom, {50,50}, 30, WHITE);
                PrintTextInGame(false, game.GetPlayer().GetScore(), {(int)GetScreenWidth()/2.0f, 70}, 50, WHITE);
                
                PrintTextInGame(false, game.GetPlayer().GetPosition().x, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 120.0f}, 30, WHITE);
                PrintTextInGame(false, game.GetPlayer().GetPosition().y, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 90.0f}, 30, WHITE);

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