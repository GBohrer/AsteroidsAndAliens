
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{
    const int screenWidth  = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    std::vector<TextBox> text_boxes;

    TextBox tb1("Start", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 100, 230, 70 }, false);
    text_boxes.push_back(tb1);

    TextBox tb2("Exit", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 200, 230, 70 }, false);
    text_boxes.push_back(tb2);

    SetTargetFPS(60);

    Game game = Game();
    bool IsGameRunning = true;

    while (IsGameRunning)
    {

        /// UPDATES
        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_X)) IsGameRunning = false;
        if (IsKeyPressed(KEY_G)) game.SetGameState(GameState::GameOver);

        switch (game.GetGameState()) {
            case GameState::Menu:
                if (IsKeyPressed(KEY_ESCAPE)) IsGameRunning = false;

                for (int i = 0; i < (int)text_boxes.size(); i++){
                    TextBox tb = text_boxes[i];
                    if (CheckCollisionPointRec(GetMousePosition(), tb.box)) {
                        text_boxes[i].isMouseOn = true;

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { 
                            if (i == 0) game.Start();
                            if (i == 1) IsGameRunning = false;
                        }

                    } else { text_boxes[i].isMouseOn = false; }
                }

                break;

            case GameState::Paused:
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        game.SetGameState(GameState::InGame);
                        SetMousePosition((int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f);
                        game.GetPlayer().SetAimTarget(game.GetPlayer().GetPosition());
                    }
                break;
            
            case GameState::InGame:
                game.UpdateAnimationTime();

                if (IsKeyPressed(KEY_ESCAPE)) { game.SetGameState(GameState::Paused); break;}

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

                DrawText("GALACTIC ADVENTURES", 400, (int)GetScreenHeight()/2.0f - 200, 90, LIGHTGRAY);
                //DrawText("Press ENTER to start", (int)GetScreenWidth()/2.0f - 200, (int)GetScreenHeight()/2.0f - 50, 40, WHITE);

                for (int i = 0; i < (int)text_boxes.size(); i++) {
                    TextBox tb = text_boxes[i];

                    if (tb.isMouseOn) {
                        DrawRectangleRec(tb.box, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, BLACK);
                    } else {
                        DrawRectangleLinesEx(tb.box, 4, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, LIGHTGRAY);
                    }
                }
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