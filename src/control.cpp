#include "../include/master.hpp"


// GAME

std::unordered_map<State, GameState> GameStateInit () {
    std::unordered_map<State, GameState> gameStates;
    std::vector<std::shared_ptr<UIObject>> screenObjs;

    // START_MENU
    screenObjs = {
        std::make_shared<SimpleText>("GALACTIC ADVENTURES", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("Press Enter", 40, SCREEN_POS_CENTER, true, true)
    };
    gameStates.emplace(State::START_MENU, GameState(State::START_MENU, screenObjs));
    screenObjs.clear();

    // MAIN_MENU
    screenObjs = {
        std::make_shared<SimpleText>("GALACTIC ADVENTURES", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<TextBox>(BoxID::PLAY, std::vector<std::string>{"Play"}, SCREEN_POS_CENTER_1, false, true),
        std::make_shared<TextBox>(BoxID::LEADERBOARD, std::vector<std::string>{"Leaderboard"}, SCREEN_POS_CENTER_2, false, true),
        std::make_shared<TextBox>(BoxID::OPTIONS, std::vector<std::string>{"Options"}, SCREEN_POS_CENTER_3, false, true),
        std::make_shared<TextBox>(BoxID::ABOUT, std::vector<std::string>{"About"}, SCREEN_POS_CENTER_4, false, true),
        std::make_shared<TextBox>(BoxID::EXIT, std::vector<std::string>{"Exit"}, SCREEN_POS_CENTER_5, false, true),
        std::make_shared<SimpleText>(GAME_VERSION, TEXTBOX_FONTSIZE, SCREEN_POS_LEFT_BOTTOM, false, false)
    };
    gameStates.emplace(State::MAIN_MENU, GameState(State::MAIN_MENU, screenObjs));
    screenObjs.clear();

    // SCORES_MENU
    screenObjs = {
        std::make_shared<SimpleText>("LEADERBOARD", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("ABC   12000", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_1, false, false),
        std::make_shared<TextBox>(BoxID::SEE, std::vector<std::string>{"See"}, SCREEN_POS_CENTER_LEFT_1, false, true),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
        std::make_shared<SimpleText>(GAME_VERSION, TEXTBOX_FONTSIZE, SCREEN_POS_LEFT_BOTTOM, false, false)
    };
    gameStates.emplace(State::SCORES_MENU, GameState(State::SCORES_MENU, screenObjs));
    screenObjs.clear();

    // OPTIONS_MENU
    screenObjs = {
        std::make_shared<SimpleText>("OPTIONS", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("Screen Mode:", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_LEFT_1, false, false),
        std::make_shared<TextBox>(BoxID::SCREEN_MODE, std::vector<std::string>{"Windowed", "FullScreen"}, SCREEN_POS_CENTER_1, false, true),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM, false, true),
        std::make_shared<SimpleText>(GAME_VERSION, TEXTBOX_FONTSIZE, SCREEN_POS_LEFT_BOTTOM, false, false)
    };
    gameStates.emplace(State::OPTIONS_MENU, GameState(State::OPTIONS_MENU, screenObjs));
    screenObjs.clear();

    // ABOUT_MENU
    screenObjs = {
        std::make_shared<SimpleText>("GALACTIC ADVENTURES", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("You are lost in deep space. You have only one spacechip.", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_1, false, false),
        std::make_shared<SimpleText>("Aliens lives in deep space and are not friendly.", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_2, false, false),
        std::make_shared<SimpleText>("Endure. Survive. Explore.", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_3, false, false),
        std::make_shared<SimpleText>("Created by GAB", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_5, false, false),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM, false, true),
        std::make_shared<SimpleText>(GAME_VERSION, TEXTBOX_FONTSIZE, SCREEN_POS_LEFT_BOTTOM, false, false)
    };
    gameStates.emplace(State::ABOUT_MENU, GameState(State::ABOUT_MENU, screenObjs));
    screenObjs.clear();

    // GAME
    screenObjs = {
        std::make_shared<SimpleText>("Score: 0", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<TextBox>(BoxID::ABORT, std::vector<std::string>{"Abort Mission"}, SCREEN_POS_LEFT_BOTTOM, false, true),
    };
    gameStates.emplace(State::GAME, GameState(State::GAME, screenObjs));
    screenObjs.clear();

    // PAUSE
    screenObjs = {
        std::make_shared<SimpleText>("PAUSED", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_2, false, false),
        std::make_shared<TextBox>(BoxID::RESUME, std::vector<std::string>{"Continue"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::ABORT, std::vector<std::string>{"Abort"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
    };
    gameStates.emplace(State::PAUSE, GameState(State::PAUSE, screenObjs));
    screenObjs.clear();

    // GAMEOVER
    screenObjs = {
        std::make_shared<SimpleText>("GAME OVER", TITLE_FONTSIZE, SCREEN_POS_CENTER_1, false, false),
        std::make_shared<TextBox>(BoxID::RESUME, std::vector<std::string>{"Next"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::EXIT, std::vector<std::string>{"Exit"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
    };
    gameStates.emplace(State::GAMEOVER, GameState(State::GAMEOVER, screenObjs));
    screenObjs.clear();

    // SAVE_MENU
    screenObjs = {
        std::make_shared<SimpleText>("MISSION SCORE", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<SimpleText>("Save score in Leaderboard?", TEXTBOX_FONTSIZE, SCREEN_POS_CENTER_4, false, false),
        std::make_shared<TextBox>(BoxID::YES, std::vector<std::string>{"Yes"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::NO, std::vector<std::string>{"No"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true),
    };
    gameStates.emplace(State::SAVE_MENU, GameState(State::SAVE_MENU, screenObjs));
    screenObjs.clear();

    // LEAVING
    screenObjs = {
        std::make_shared<SimpleText>("ARE YOU SURE?", TITLE_FONTSIZE, SCREEN_POS_CENTER_TOP, false, false),
        std::make_shared<TextBox>(BoxID::EXIT, std::vector<std::string>{"Exit"}, SCREEN_POS_CENTER_BOTTOM_RIGHT, false, true),
        std::make_shared<TextBox>(BoxID::BACK, std::vector<std::string>{"Back"}, SCREEN_POS_CENTER_BOTTOM_LEFT, false, true)
    };
    gameStates.emplace(State::LEAVING, GameState(State::LEAVING, screenObjs));
    screenObjs.clear(); 
    
    return gameStates;
}

GameInfo GameInfoInit() {
    GameInfo info;
    info.gameStates = GameStateInit();
    //info.gameImages = LoadGameImages();
    return info;
}

GameTimer GameTimerInit() {
    GameTimer t;
    t.run_time = t.animation_t_now = t.animation_t_prev = t.delta_t = 0.0f;
    return t;
}

std::unique_ptr<ECSManager> GameECSManagerInit() {

    auto ecs = std::make_unique<ECSManager>();
    ecs->Init();

    // Component:
    ecs->RegisterComponent<Transform>();
    ecs->RegisterComponent<Velocity>();
    ecs->RegisterComponent<Acceleration>();


    // System:
    auto movementSys = ecs->RegisterSystem<MovementSystem>();
    {
        Signature sig;
        sig.set(ecs->GetComponentType<Transform>());
        sig.set(ecs->GetComponentType<Velocity>());
        sig.set(ecs->GetComponentType<Acceleration>());
        ecs->SetSystemSignature<MovementSystem>(sig);
    }
    movementSys->Init();

    return ecs;

}


// GAMESTATE HANDLERS

std::map<State, std::function<void(Game&)>> stateHandlers = {
    {State::START_MENU, Handle_START_MENU},
    {State::MAIN_MENU, Handle_MAIN_MENU},
    {State::SCORES_MENU, Handle_SCORES_MENU},
    {State::OPTIONS_MENU, Handle_OPTIONS_MENU},
    {State::ABOUT_MENU, Handle_ABOUT_MENU},
    {State::GAME, Handle_GAME},
    {State::PAUSE, Handle_PAUSE},
    {State::GAMEOVER, Handle_GAMEOVER},
    {State::SAVE_MENU, Handle_SAVE_MENU},
    {State::LEAVING, Handle_LEAVING}
};

void Handle_START_MENU(Game& game) {
    if(IsKeyPressed(KEY_ENTER))
        game.SetCurrentGameState(State::MAIN_MENU);
}

void Handle_MAIN_MENU(Game& game) {
    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    switch(tb->GetID()) {
                        case BoxID::PLAY:
                            game.MissionInit();
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
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_SCORES_MENU(Game& game) {
        for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    switch(tb->GetID()) {
                        case BoxID::BACK:
                            game.SetCurrentGameState(State::MAIN_MENU);
                            return;
                        default:
                            break;
                    }
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_OPTIONS_MENU(Game& game) {
    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_ABOUT_MENU(Game& game) {
    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                   switch(tb->GetID()) {
                        case BoxID::BACK:
                            game.SetCurrentGameState(State::MAIN_MENU);
                            return;
                        default:
                            break;
                    }
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_GAME(Game& game) {

    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                   switch(tb->GetID()) {
                        case BoxID::ABORT:
                            game.SetCurrentGameState(State::GAMEOVER);
                            return;
                        default:
                            break;
                    }
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_PAUSE(Game& game) {
    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                   switch(tb->GetID()) {
                        case BoxID::RESUME:
                            game.SetCurrentGameState(State::GAME);
                            return;
                        case BoxID::ABORT:
                            game.SetCurrentGameState(State::GAMEOVER);
                            return;
                        default:
                            break;
                    }
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_GAMEOVER(Game& game) {

    game.ClearCurrentMission();

    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                   switch(tb->GetID()) {
                        case BoxID::RESUME:
                            game.SetCurrentGameState(State::SAVE_MENU);
                            return;
                        case BoxID::EXIT:
                            game.SetCurrentGameState(State::LEAVING);
                            return;
                        default:
                            break;
                    }
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_SAVE_MENU(Game& game) {
    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

void Handle_LEAVING(Game& game) {
    for (const auto& obj : game.GetUIObjects()) {
        if (obj && obj->isClickable) {
            TextBox* tb = dynamic_cast<TextBox*>(obj.get());
            if (CheckCollisionPointRec(GetMousePosition(), tb->GetBox())) {
                tb->SetIsCursorOn(true);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
                }
            } else { tb->SetIsCursorOn(false); }
        }
    }
}

// MISSION




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
