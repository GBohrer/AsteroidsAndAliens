
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{
    const int screenWidth  = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    SetTargetFPS(60);

    Game game = Game();

    bool IsGameRunning = true;
    int TextBoxIndex;

    while (IsGameRunning)
    {

        /// UPDATES
        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_X)) IsGameRunning = false;
        if (IsKeyPressed(KEY_G)) {
            game.SetCurrentGameState(game.GetGameStates().at(State::GameOver));
        }

        switch (game.GetCurrentGameState().state) {

            case State::InMenu:
                if (IsKeyPressed(KEY_ESCAPE)) IsGameRunning = false;

                TextBoxIndex = 0;
                for (TextBox& tb : game.GetCurrentGameState().text_boxes) {
                    if (CheckCollisionPointRec(GetMousePosition(), tb.box)) {
                        tb.isMouseOn = true;
                        game.UpdateCurrentGameStateTextBox(tb, TextBoxIndex);

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            if (tb.text == "Start") game.Start();
                            if (tb.text == "Exit") IsGameRunning = false;
                        }

                    } else {
                        tb.isMouseOn = false;
                        game.UpdateCurrentGameStateTextBox(tb, TextBoxIndex);
                    }
                    TextBoxIndex++;
                }

            break;

            case State::Paused:

                TextBoxIndex = 0;
                for (TextBox& tb : game.GetCurrentGameState().text_boxes) {
                    if (CheckCollisionPointRec(GetMousePosition(), tb.box)) {
                        tb.isMouseOn = true;
                        game.UpdateCurrentGameStateTextBox(tb, TextBoxIndex);

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            if (tb.text == "Resume") {
                                game.SetCurrentGameState(game.GetGameStates().at(State::InGame));   
                                SetMousePosition((int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f);
                                game.GetPlayer().SetAimTarget(game.GetPlayer().GetPosition());
                            }
                            if (tb.text == "Exit") IsGameRunning = false;
                        }

                    } else {
                        tb.isMouseOn = false;
                        game.UpdateCurrentGameStateTextBox(tb, TextBoxIndex);
                    }
                    TextBoxIndex++;
                }
            break;
            
            case State::InGame:
                game.UpdateAnimationTime();

                if (IsKeyPressed(KEY_ESCAPE)) {
                    game.SetCurrentGameState(game.GetGameStates().at(State::Paused));
                    break;
                }

                game.UpdatePlayer();
                if (IsKeyDown(KEY_SPACE)) game.SpawnBullets();

                if (game.CheckDifficultyIncrease(game.GetPlayer().GetScore())){ game.IncreaseDifficulty();}
                
                game.SpawnAsteroids();
                game.SpawnAliens();

                game.CheckEntityCollisions();

                game.UpdateCamera(GetScreenWidth(), GetScreenHeight());
            break;

            case State::GameOver:

                TextBoxIndex = 0;
                for (TextBox& tb : game.GetCurrentGameState().text_boxes) {
                    if (CheckCollisionPointRec(GetMousePosition(), tb.box)) {
                        tb.isMouseOn = true;
                        game.UpdateCurrentGameStateTextBox(tb, TextBoxIndex);

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                            switch (tb.id) {
                                case TextBoxId::Restart:
                                    game.Reset();
                                    game.Start();
                                break;
                            
                                case TextBoxId::Menu:
                                    game.Reset();
                                break;

                                case TextBoxId::Exit:
                                    IsGameRunning = false;
                                break;

                                default:
                                break;
                            }
                        }

                    } else {
                        tb.isMouseOn = false;
                        game.UpdateCurrentGameStateTextBox(tb, TextBoxIndex);
                    }
                    TextBoxIndex++;
                }

            break;

            case State::IsLoading:
            break;

            default:
            break;
        }

        /// RENDERS
        BeginDrawing();

        switch (game.GetCurrentGameState().state) {
            case State::InMenu:
                ClearBackground(color_space_background);

                DrawText("GALACTIC ADVENTURES", 400, (int)GetScreenHeight()/2.0f - 200, 90, LIGHTGRAY);

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (tb.isMouseOn) {
                        DrawRectangleRec(tb.box, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, BLACK);
                    } else {
                        DrawRectangleLinesEx(tb.box, 4, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, LIGHTGRAY);
                    }
                }
            break;

            case State::Paused:
                DrawText("PAUSE", (int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f - 200, 35, WHITE);

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (tb.isMouseOn) {
                        DrawRectangleRec(tb.box, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, BLACK);
                    } else {
                        DrawRectangleLinesEx(tb.box, 4, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, LIGHTGRAY);
                    }
                }

            break;
            
            case State::InGame:
                ClearBackground(color_space_background);

                BeginMode2D(game.GetCamera());

                    //Draw Level Boundries
                    DrawRectangleLinesEx( {0, 0,  game.GetCurrentLevelBounds().back().x,  game.GetCurrentLevelBounds().back().y}, 15.0f, PURPLE);

                    game.GetPlayer().DrawHitBox();
                    game.GetPlayer().DrawHealthBar();
                    game.GetPlayer().DrawAim();

                    for (Alien& a : game.GetCurrentAliens()) { 
                        a.DrawHitBox();
                        a.DrawHealthBar();
                        //a.DrawDirectionVector();
                     }

                    for (Bullet& b : game.GetCurrentBullets()) { b.DrawHitBox(); } 
                    for (Asteroid& ast : game.GetCurrentAsteroids()) {
                        ast.DrawHitBox();
                    }

                EndMode2D();

                //CAMERA ZOOM
                PrintTextInGame(true, game.GetCamera().zoom - 0.5f, {50,50}, 30, WHITE);
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

            case State::GameOver:
                DrawText("GAME OVER", (int)GetScreenWidth()/2.0f - 250, (int)GetScreenHeight()/2.0f - 200, 90, WHITE);

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (tb.isMouseOn) {
                        DrawRectangleRec(tb.box, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, BLACK);
                    } else {
                        DrawRectangleLinesEx(tb.box, 4, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, LIGHTGRAY);
                    }
                }
            break;

            case State::IsLoading:
            break;

            default:
            break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}