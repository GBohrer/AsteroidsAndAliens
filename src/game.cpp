#include "../include/master.hpp"


// CORE METHODS:

Game::Game() {
    this->info = GameInfoInit();
    this->timer.Start();
    //this->SaveFile = LoadSaveFile();
    this->ECSManager = GameECSManagerInit();
}

void Game::Start() {

    this->mInfo.Init();
    SpawnAliens(ECSManager, mInfo);
    SpawnAsteroids(ECSManager, mInfo);
}

void Game::Pause() {
    mInfo.timer.Pause();
}

void Game::Resume() {
    mInfo.timer.Resume();
}

void Game::Reset() {

    ECSManager->DestroyAllEntities();
    mInfo.Reset();

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

    if (stateHandlers.find(info.currentGameState.state) != stateHandlers.end()) {
        stateHandlers[info.currentGameState.state](*this);
    } else {
        // Se o estado não tiver função associada, você pode tratar o erro aqui
    }

    this->timer.Update();

}

void Game::Render() {

    BeginDrawing();

    ClearBackground(COLOR_BACKGROUND);
    
    for (const auto& obj : info.currentGameState.gameScreen) {
        obj->Draw(timer.GetRunTime());
    }

    if(GetCurrentGameState().state == State::GAME) {

        for (const auto& system : ECSManager->GetSystems()) {
            for (const auto& entity : system->mEntities) {

                auto const& transform = ECSManager->GetComponent<Transform>(entity);
                DrawCircle(transform.translation.x, transform.translation.y, transform.scale.x, WHITE);
            }
        }
    }

    if (info.debugMode) RenderDebugScreen();

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

GameTimer Game::GetTimer() {
    return this->timer;
}

// ==========================================================================

void Game::UpdateSystems() {

    for (auto& system : ECSManager->GetSystems() ) {
        system->Update(ECSManager, timer.GetDeltaT());
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

void Game::RenderDebugScreen() {
    DrawFPS(15,15);
    PrintValueInGame("Version", GAME_VERSION, {15, DEBUG_FONTSIZE*2 + 15}, DEBUG_FONTSIZE, WHITE);
    PrintValueInGame("RunTime", GetTimer().GetRunTime(), {15, DEBUG_FONTSIZE*3 + 15}, DEBUG_FONTSIZE, WHITE);
    PrintValueInGame("MissionRunTime", mInfo.timer.ElapsedSeconds(), {15, DEBUG_FONTSIZE*4 + 15}, DEBUG_FONTSIZE, WHITE);
    PrintValueInGame("Aliens", mInfo.aliens.size(), {15, DEBUG_FONTSIZE*5 + 15}, DEBUG_FONTSIZE, WHITE);
    PrintValueInGame("Asteroids", mInfo.asteroids.size(), {15, DEBUG_FONTSIZE*6 + 15}, DEBUG_FONTSIZE, WHITE);
}

