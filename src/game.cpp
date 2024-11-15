#include "../include/master.hpp"


// CORE METHODS:

Game::Game() {
    this->isGameRunning = true;
    this->debugMode = false;
    this->info = GameInfoInit();
    this->currentGameState = info.gameStates.at(State::START_MENU);
    this->t = GameTimerInit();
    //this->SaveFile = LoadSaveFile();
    this->ECSManager = GameECSManagerInit();
}

void Game::Start() {

    std::vector<Entity> asteroids (1);

    for (auto& asteroid : asteroids) {
        asteroid = ECSManager->CreateEntity();

        ECSManager->AddComponent(
            asteroid,
            Transform {
                .translation = Vector3({100.0f, 100.0f, 1.0f}),
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
                .current = Vector2({0.5f, 0.5f}),
                .max = 10.0f,
                .min = 0.0f
            });
    }
}

bool Game::Running() {
    return this->isGameRunning;
}

std::vector<std::shared_ptr<UIObject>>& Game::GetUIObjects() {
    return this->currentGameState.gameScreen;
}

void Game::Update() {

    if(IsKeyPressed(KEY_X)) isGameRunning = false;
    if(IsKeyPressed(KEY_F3)) debugMode = !debugMode;

    UpdateGameTimer();

    if (stateHandlers.find(currentGameState.state) != stateHandlers.end()) {
        stateHandlers[currentGameState.state](*this);
    } else {
        // Se o estado não tiver função associada, você pode tratar o erro aqui
    }
}

void Game::Draw() {

    BeginDrawing();

    ClearBackground(COLOR_BACKGROUND);
    
    for (const auto& obj : currentGameState.gameScreen) {
        obj->Draw(t.run_time);
    }

    for (const auto& system : ECSManager->GetSystems()) {
        for (const auto& entity : system->mEntities) {

            auto const& transform = ECSManager->GetComponent<Transform>(entity);
            DrawCircle(transform.translation.x, transform.translation.y, transform.scale.x, WHITE);
        }
    }

    if (debugMode) {
        DrawFPS(15,DEBUG_FONTSIZE);
        PrintValueInGame("RunTime", t.run_time, {15,DEBUG_FONTSIZE + 5}, DEBUG_FONTSIZE, WHITE);
    }

    EndDrawing();
}

void Game::Close() {
    UnloadGameImages(info.gameImages);
    this->isGameRunning = false;
}

GameState& Game::GetCurrentGameState() {
    return this->currentGameState;
}

void Game::SetCurrentGameState(State state) {
    GameState gs = info.gameStates.at(state);
    this->currentGameState = gs;
}

// ==========================================================================

void Game::UpdateGameTimer() {
    t.animation_t_now = static_cast<double>(GetTime());
    t.delta_t = t.animation_t_now - t.animation_t_prev;
    t.animation_t_prev = t.animation_t_now;

    t.run_time += t.delta_t;
}

double Game::GetRunTime() {
    return this->t.run_time;
}

double Game::GetDeltaT() {
    return this->t.delta_t;
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