
#include "../include/master_header.h"

int main()
{
    const int screenWidth  = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    SetTargetFPS(60);

    Game game = Game();
    bool IsGameRunning = true;

    while (IsGameRunning)
    {
        /// UPDATES
        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_X)) IsGameRunning = false;
        if (IsKeyPressed(KEY_G)) game.SetCurrentGameState(game.GetGameStates().at(State::GameOver));

        switch (game.GetCurrentGameState().state) {

            case State::InMenu:
                if (IsKeyPressed(KEY_ESCAPE)) IsGameRunning = false;

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (CheckCollisionPointRec(GetMousePosition(), tb.box)) {
                        tb.isMouseOn = true;
                        game.UpdateCurrentGameStateTextBox(tb, i);
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            if (tb.text == "Start")  { game.Start(); }
                            else if (tb.text == "Exit")  { IsGameRunning = false; }
                        }
                    } else {
                        tb.isMouseOn = false;
                        game.UpdateCurrentGameStateTextBox(tb, i);
                    }
                }
            break;

            case State::Paused:

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (CheckCollisionPointRec(GetMousePosition(), tb.box)) {
                        tb.isMouseOn = true;
                        game.UpdateCurrentGameStateTextBox(tb, i);

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            if (tb.text == "Resume") {
                                game.SetCurrentGameState(game.GetGameStates().at(State::InGame));
                                SetMousePosition(game.GetLastMousePosition().x, game.GetLastMousePosition().y);
                            }
                            if (tb.text == "Exit") IsGameRunning = false;
                        }

                    } else {
                        tb.isMouseOn = false;
                        game.UpdateCurrentGameStateTextBox(tb, i);
                    }
                }
            break;
            
            case State::InGame:
                game.Update();

            break;

            case State::GameOver:

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (CheckCollisionPointRec(GetMousePosition(), tb.box)) {
                        tb.isMouseOn = true;
                        game.UpdateCurrentGameStateTextBox(tb, i);

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
                        game.UpdateCurrentGameStateTextBox(tb, i);
                    }
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
                ClearBackground(Color{10, 10, 40, 255});

                DrawText("GALACTIC ADVENTURES", 400, (int)GetScreenHeight()/2.0f - 200, 90, LIGHTGRAY);

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (tb.isMouseOn) {
                        DrawRectangleLinesEx(tb.box, 4, YELLOW);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, YELLOW);
                    } else {
                        DrawRectangleLinesEx(tb.box, 4, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, LIGHTGRAY);
                    }
                }
            break;

            case State::Paused:
                DrawText("PAUSE", (int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f - 200, 35, LIGHTGRAY);

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (tb.isMouseOn) {
                        DrawRectangleLinesEx(tb.box, 4, YELLOW);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, YELLOW);
                    } else {
                        DrawRectangleLinesEx(tb.box, 4, LIGHTGRAY);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, LIGHTGRAY);
                    }
                }

            break;
            
            case State::InGame:
                game.Render();

            break;

            case State::GameOver:
                DrawText("GAME OVER", (int)GetScreenWidth()/2.0f - 250, (int)GetScreenHeight()/2.0f - 200, 90, WHITE);

                for (int i = 0; i < (int)game.GetCurrentGameState().text_boxes.size(); i++) {
                    TextBox tb = game.GetCurrentGameState().text_boxes[i];

                    if (tb.isMouseOn) {
                        DrawRectangleLinesEx(tb.box, 4, YELLOW);
                        DrawText(ConvertText(tb.text), tb.box.x + tb.box.width/4, tb.box.y + tb.box.height/4, tb.box.height/2, YELLOW);
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

        game.UpdateTime();
    }

    CloseWindow();
    return 0;
}