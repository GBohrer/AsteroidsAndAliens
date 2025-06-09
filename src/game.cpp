#include "../include/master.hpp"


// CORE METHODS:

Game::Game() {
    this->info = GameInfoInit();
    this->timer.Start();
    //this->SaveFile = LoadSaveFile();
    this->ECSManager = GameECSManagerInit();
}

void Game::StartMission() {

    this->info.isMissionRunning = true;
    this->mInfo.Init();
    SpawnPlayer(ECSManager, mInfo);
    //SpawnAliens(ECSManager, mInfo);
    //SpawnAsteroids(ECSManager, mInfo);
    this->camera = GameCameraInit();
}

void Game::ResetMission() {

    ECSManager->DestroyAllEntities();
    mInfo.Reset();
    info.isMissionRunning = false;
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

    if (info.isMissionRunning) {
        UpdateCamera();
    }

    this->timer.Update();
}

void Game::Render() {

    BeginDrawing();

    ClearBackground(COLOR_BACKGROUND);
    
    // Render UIObjects
    for (const auto& obj : info.currentGameState.gameScreen) {
        obj->Draw(timer.GetRunTime());
    }

    if (info.isMissionRunning) {
        RenderPlayerStatus();
        if (info.debugMode) RenderDebugScreen();
    }

    // Render Level
    if(info.isMissionRunning) {

        BeginMode2D(this->camera);

            DrawGrid(80, 1.0f);

            // Entities in world
            for (Entity ett = 0; ett < MAX_ENTITIES; ett++) {
                if(ECSManager->CheckSignature(ett)) {
                    auto const& transform = ECSManager->GetComponent<Transform>(ett);

                    if (ett == mInfo.player) {                 
                        auto const& playerAim = ECSManager->GetComponent<Aim>(ett);

                        Vector2 playerPos = {transform.translation.x, transform.translation.y};
                        float playerRadius = transform.scale.x;

                        DrawCircle(playerPos.x, playerPos.y, playerRadius * 0.8f, ORANGE);
                        DrawLine(playerPos.x, playerPos.y,
                                playerPos.x + playerAim.direction.x,
                                playerPos.y + playerAim.direction.y, GREEN);

                    } else {
                        DrawCircle(transform.translation.x, transform.translation.y, transform.scale.x, WHITE);
                    }


                }
            }
            
        EndMode2D();
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

GameTimer Game::GetTimer() {
    return this->timer;
}

// ==========================================================================

void Game::UpdateCamera() {

    float camera_zoom = this->camera.zoom;
    camera_zoom += GetMouseWheelMove() * GAME_CAMERA_ZOOM_MODIFIER;

    if (camera_zoom > GAME_CAMERA_MAX_ZOOM) camera_zoom = GAME_CAMERA_MAX_ZOOM;
    else if (camera_zoom < GAME_CAMERA_MIN_ZOOM) camera_zoom = GAME_CAMERA_MIN_ZOOM;
    this->camera.zoom = camera_zoom;

    const auto& tr = ECSManager->GetComponent<Transform>(mInfo.player);
    this->camera.target = {tr.translation.x, tr.translation.y};
}

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

void Game::RenderPlayerStatus() {
    
    auto const& PlayerPos = ECSManager->GetComponent<Transform>(mInfo.player);
    PrintValueInGame("LAT",PlayerPos.translation.x, {SCREEN_POS_CENTER_BOTTOM.x, SCREEN_POS_CENTER_BOTTOM.y + DEBUG_FONTSIZE*2}, DEBUG_FONTSIZE, WHITE);
    PrintValueInGame("LON",PlayerPos.translation.y, {SCREEN_POS_CENTER_BOTTOM.x, SCREEN_POS_CENTER_BOTTOM.y + DEBUG_FONTSIZE*3}, DEBUG_FONTSIZE, WHITE);
}

template<typename T>
void PrintDebugLine(const std::string& label, const T value, int line, int fontSize, Color color) {
    const int x = 15;
    const int y = 15 + line * fontSize;
    PrintValueInGame(label, value, {x, y}, fontSize, color);
}

void Game::RenderDebugScreen() {
    DrawFPS(15, 15);

    int line = 1;
    PrintDebugLine("Version", GAME_VERSION, line++, DEBUG_FONTSIZE, WHITE);
    //PrintDebugLine("RunTime", std::to_string(GetTimer().GetRunTime()), line++, DEBUG_FONTSIZE, WHITE);
    //PrintDebugLine("Camera Zoom", std::to_string(camera.zoom), line++, DEBUG_FONTSIZE, WHITE);
    PrintDebugLine("MissionRunTime", std::to_string(mInfo.timer.ElapsedSeconds()), line++, DEBUG_FONTSIZE, WHITE);
    //PrintDebugLine("Aliens", std::to_string(mInfo.aliens.size()), line++, DEBUG_FONTSIZE, WHITE);
    //PrintDebugLine("Asteroids", std::to_string(mInfo.asteroids.size()), line++, DEBUG_FONTSIZE, WHITE);
    PrintDebugLine("Player Velocity X: ", ECSManager->GetComponent<Velocity>(mInfo.player).current.x, line++, DEBUG_FONTSIZE, WHITE);
    PrintDebugLine("Player Velocity Y: ", ECSManager->GetComponent<Velocity>(mInfo.player).current.y, line++, DEBUG_FONTSIZE, WHITE);
    PrintDebugLine("Player Acceleration X: ", ECSManager->GetComponent<Acceleration>(mInfo.player).current.x, line++, DEBUG_FONTSIZE, WHITE);
    PrintDebugLine("Player Acceleration Y: ", ECSManager->GetComponent<Acceleration>(mInfo.player).current.y, line++, DEBUG_FONTSIZE, WHITE);
}

