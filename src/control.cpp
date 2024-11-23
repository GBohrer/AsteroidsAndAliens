#include "../include/master.hpp"

// INTERFACE

void Handle_UI(Game& game, std::function<void(TextBox*)> callback) {
    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (tb && CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    callback(tb);
                    return;
                }
            } else {
                tb->SetIsCursorOn(false);
            }
        }
    }
}

// GAMESTATE HANDLERS

std::map<State, std::function<void(Game&)>> stateHandlers = {
    {State::START_MENU, Handle_START_MENU},
    {State::MAIN_MENU, Handle_MAIN_MENU},
    {State::SCORES_MENU, Handle_SCORES_MENU},
    {State::OPTIONS_MENU, Handle_OPTIONS_MENU},
    {State::ABOUT_MENU, Handle_ABOUT_MENU},
    {State::GAME, Handle_GAME},
    {State::GAME, Handle_MAP_GAME},
    {State::GAMEOVER, Handle_GAMEOVER},
    {State::SAVE_MENU, Handle_SAVE_MENU},
    {State::LEAVING, Handle_LEAVING}
};

void Handle_START_MENU(Game& game) {
    if(IsKeyPressed(KEY_ENTER))
        game.SetCurrentGameState(State::MAIN_MENU);
}

void Handle_MAIN_MENU(Game& game) {
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::PLAY:
                game.StartMission();
                game.SetCurrentGameState(State::GAME);
                return;
            case BoxID::LEADERBOARD:
                game.SetCurrentGameState(State::SCORES_MENU);
                return;
            case BoxID::OPTIONS:
                game.SetCurrentGameState(State::OPTIONS_MENU);
                return;
            case BoxID::ABOUT:
                game.SetCurrentGameState(State::ABOUT_MENU);
                return;
            case BoxID::EXIT:
                game.SetCurrentGameState(State::LEAVING);
                return;
            default:
                break;
        }
    });
}

void Handle_SCORES_MENU(Game& game) {
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::BACK:
                game.SetCurrentGameState(State::MAIN_MENU);
                return;
            default:
                break;
        }
    });
}

void Handle_OPTIONS_MENU(Game& game) {
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::SCREEN_MODE:
                tb->SetNextText();
                ToggleFullscreen();
                break;
            case BoxID::BACK:
                game.SetCurrentGameState(State::MAIN_MENU);
                return;
            default:
                break;
        }
    });
}

void Handle_ABOUT_MENU(Game& game) {
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::BACK:
                game.SetCurrentGameState(State::MAIN_MENU);
                return;
            default:
                break;
        }
    });
}

void Handle_GAME(Game& game) {
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::MAP:
                game.SetCurrentGameState(State::MAP_GAME);
                return;
            case BoxID::ABORT:
                game.SetCurrentGameState(State::GAMEOVER);
                return;
            default:
                break;
        }
    });

    game.UpdateSystems();
}

void Handle_MAP_GAME(Game& game) {
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::BACK:
                game.SetCurrentGameState(State::GAME);
                return;
            default:
                break;
        }
    });

    game.UpdateSystems();
}

void Handle_GAMEOVER(Game& game) {
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::RESUME:
                game.SetCurrentGameState(State::SAVE_MENU);
                break;
            case BoxID::EXIT:
                game.SetCurrentGameState(State::LEAVING);
                break;
            default:
                break;
        }
        game.ResetMission();
    });
}

void Handle_SAVE_MENU(Game& game) {
    ClearBackground(COLOR_BACKGROUND);
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()) {
            case BoxID::YES:
                // SALVAR MISSION SCORE NO SAVEFILE
                game.SetCurrentGameState(State::SCORES_MENU);
                return;
            case BoxID::NO:
                game.SetCurrentGameState(State::MAIN_MENU);
                return;
            default:
                break;
        }
    });
}

void Handle_LEAVING(Game& game) {
    ClearBackground(COLOR_BACKGROUND);
    Handle_UI(game, [&game](TextBox* tb) {
        switch(tb->GetID()){
            case BoxID::EXIT:
                game.Close();
                return;
            case BoxID::BACK:
                game.SetCurrentGameState(State::MAIN_MENU);
                return;
            default:
                break;
        }
    });
}


// OUTRO

std::unordered_map<std::string, Texture2D> LoadGameImages() {
    std::unordered_map<std::string, Texture2D> gi;

    Texture2D logo = LoadTexture("include/resources/images/xbox_logo.png");
    gi.insert({"LOGO", logo});

    return gi;
}

void UnloadGameImages(std::unordered_map<std::string, Texture2D>& gameImages) {
    for (auto& image : gameImages)
        UnloadTexture(image.second);
    gameImages.clear();
}
