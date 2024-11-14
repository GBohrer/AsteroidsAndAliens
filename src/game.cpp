#include "../include/master.hpp"


Game::Game() {
    this->isGameRunning = true;
    this->gameInfo = GameInfoInit();
    this->currentGameState = gameInfo.gameStates.at(State::START_MENU);
    this->t = GameTimerInit();
    //this->SaveFile = LoadSaveFile();
    this->ECSManager = GameECSManagerInit();
}

void Game::Close() {
    UnloadGameImages(gameInfo.gameImages);
    this->isGameRunning = false;
}

GameState& Game::GetCurrentGameState() {
    return this->currentGameState;
}

void Game::SetCurrentGameState(State state) {
    GameState gs = gameInfo.gameStates.at(state);
    this->currentGameState = gs;
}

bool Game::Running() {
    return this->isGameRunning;
}

std::vector<std::shared_ptr<UIObject>>& Game::GetUIObjects() {
    return this->currentGameState.gameScreen;
}


void Game::Update() {

    if(IsKeyPressed(KEY_X)) isGameRunning = false;

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

    EndDrawing();
}

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