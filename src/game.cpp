#include "../include/master.hpp"


// CORE METHODS:

Game::Game() {
    this->info = GameInfoInit();
    //this->SaveFile = LoadSaveFile();
    this->ECSManager = GameECSManagerInit();
}

void Game::Start() {

    std::vector<Entity> asteroids (MAX_ENTITIES - 1);
    int teste = 20;

    for (auto& asteroid : asteroids) {
        asteroid = ECSManager->CreateEntity();


        ECSManager->AddComponent(
            asteroid,
            Transform {
                .translation = Vector3({100.0f + teste , 100.0f, 1.0f}),
                .rotation = Quaternion({1.0f, 1.0f, 1.0f, 1.0f}),
                .scale = Vector3({5.0f, 5.0f, 5.0f})
            });

        ECSManager->AddComponent(
            asteroid,
            Velocity {
                .current = Vector2({0.0f, 0.0f}),
                .max = 200.0f,
                .min = -200.0f
            });

        ECSManager->AddComponent(
            asteroid,
            Acceleration {
                .current = Vector2({2.5f, 2.5f}),
                .max = 10.0f,
                .min = 0.0f
            });

        ECSManager->AddComponent(
            asteroid,
            EState {
                EttState::MOVING
            });

        teste += 10;
    }
}

void Game::Reset() {

    ECSManager->DestroyAllEntities();

}

bool Game::Running() {
    return this->info.isGameRunning;
}

std::vector<std::shared_ptr<UIObject>>& Game::GetUIObjects() {
    return this->info.currentGameState.gameScreen;
}

void Game::Update() {

    if(IsKeyPressed(KEY_X)) info.isGameRunning = false;
    if(IsKeyPressed(KEY_F3)) info.debugMode = !info.debugMode;

    UpdateGameTimer();

    if (stateHandlers.find(info.currentGameState.state) != stateHandlers.end()) {
        stateHandlers[info.currentGameState.state](*this);
    } else {
        // Se o estado não tiver função associada, você pode tratar o erro aqui
    }
}

void Game::Draw() {

    BeginDrawing();

    ClearBackground(COLOR_BACKGROUND);
    
    for (const auto& obj : info.currentGameState.gameScreen) {
        obj->Draw(info.t.run_time);
    }

    if(GetCurrentGameState().state == State::GAME) {

        for (const auto& system : ECSManager->GetSystems()) {
            for (const auto& entity : system->mEntities) {

                auto const& transform = ECSManager->GetComponent<Transform>(entity);
                DrawCircle(transform.translation.x, transform.translation.y, transform.scale.x, WHITE);
            }
        }
    }

    if (info.debugMode) {
        DrawFPS(15,15);
        PrintValueInGame("Version", GAME_VERSION, {15, DEBUG_FONTSIZE*2 + 15}, DEBUG_FONTSIZE, WHITE);
        PrintValueInGame("RunTime", info.t.run_time, {15, DEBUG_FONTSIZE*3 + 15}, DEBUG_FONTSIZE, WHITE);
    }

    EndDrawing();
}

void Game::Close() {
    UnloadGameImages(info.gameImages);
    this->info.isGameRunning = false;
}

GameState& Game::GetCurrentGameState() {
    return this->info.currentGameState;
}

void Game::SetCurrentGameState(State state) {
    GameState gs = info.gameStates.at(state);
    this->info.currentGameState = gs;
}

// ==========================================================================

void Game::UpdateGameTimer() {
    GameTimer &timer = info.t;

    timer.animation_t_now = static_cast<double>(GetTime());
    timer.delta_t = timer.animation_t_now - timer.animation_t_prev;
    timer.animation_t_prev = timer.animation_t_now;

    timer.run_time += timer.delta_t;
}

double Game::GetRunTime() {
    return this->info.t.run_time;
}

double Game::GetDeltaT() {
    return this->info.t.delta_t;
}

void Game::UpdateSystems() {

    for (auto& system : ECSManager->GetSystems() ) {
        system->Update(ECSManager, GetDeltaT());
    }

}

void Game::UpdateFileName(PromptBox* pb) {
//
//    int charCount = currentSavefile.fileName.size();
//
//    int key = GetCharPressed();
//    while (key > 0)
//    {
//        if ((key >= 32) && (key <= 125) && (charCount < MAX_FILENAME_CHARS)){
//            currentSavefile.fileName[charCount] = (char)key;
//            currentSavefile.fileName[charCount + 1] = '\0';
//            charCount++;
//        }
//        key = GetCharPressed();
//    }
//    if (IsKeyPressed(KEY_BACKSPACE))
//    {
//        charCount--;
//        if (charCount < 0) charCount = 0;
//        currentSavefile.fileName[charCount] = '\0';
//    }
//
//    // Mudar a promptBox atual pb inserindo o filename em sem campo SimpleText text
//    std::string fileNameStr(currentSavefile.fileName);
//    if (charCount < MAX_FILENAME_CHARS) {
//        fileNameStr.append("_");
//    }
//    pb->SetText(fileNameStr);
}