#include "../include/master_header.h"


Game::Game() {
    SetInitialGameStates();
    currentGameState = GetGameStates().at(State::InMenu);
}

void Game::Start() {
    SetCurrentGameState(GetGameStates().at(State::InGame));
    this->level = LevelMap();
    this->level.Set(GetPlayer());
    this->player = Player(Vector2Scale(GetGameLevelMap().GetCurrentLevelBounds().back(), 0.5f));
    SetCamera();
    SetMousePosition((int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f);
}

void Game::Reset() {
    currentGameState = GetGameStates().at(State::InMenu);
    level.Reset();
}

LevelMap& Game::GetGameLevelMap() {
    return this->level;
}

// GAME STATE:
std::unordered_map<State, GameStateInfo>& Game::GetGameStates() {
    return gameStates;
}

void Game::SetInitialGameStates() {

    //TEXT BOXES
    TextBox start(TextBoxId::Start,"Start", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 100, 230, 70 });
    TextBox restart(TextBoxId::Restart,"Restart", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 100, 230, 70 });
    TextBox exit(TextBoxId::Exit,"Exit", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 200, 230, 70 });
    TextBox resume(TextBoxId::Resume,"Resume", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 100, 230, 70 });
    TextBox menu(TextBoxId::Menu,"Menu", { (int)GetScreenWidth()/2.0f - 115, (int)GetScreenHeight()/2.0f + 300, 230, 70 });
    TextBox loading(TextBoxId::Loading,"Loading...", { (int)GetScreenWidth()/2.0f - 140, (int)GetScreenHeight()/2.0f + 100, 230, 70 });

    GameStateInfo state1(State::InMenu, {start,exit});
    GameStateInfo state2(State::InGame, {});
    GameStateInfo state3(State::Paused, {resume,exit});
    GameStateInfo state4(State::GameOver, {restart,menu,exit});
    GameStateInfo state5(State::IsLoading, {loading});

    this->gameStates.insert({{State::InMenu,state1}, 
                             {State::InGame,state2}, 
                             {State::Paused, state3}, 
                             {State::GameOver,state4},
                             {State::IsLoading,state5}});
}

GameStateInfo Game::GetCurrentGameState () {
    return currentGameState;
}

void Game::SetCurrentGameState(GameStateInfo gameStateInfo) {
    this->currentGameState = gameStateInfo;
}

void Game::UpdateCurrentGameStateTextBox (TextBox tb, int position) {
    this->currentGameState.text_boxes[position] = tb;
}

Vector2 Game::GetLastMousePosition() {
    return LastMousePosition;
}

void Game::SetLastMousePosition(Vector2 mouse) {
    this->LastMousePosition = mouse;
}


// PLAYER
Player& Game::GetPlayer() {
    return player;
}

void Game::SetPlayer(Player p) {
    this->player = player;
}

void Game::UpdatePlayer() {

    EntityVelocity v = GetPlayer().GetVelocity();

    //Check Spaceship Fuel:
    if (v.current.x != 0.0f || v.current.y != 0.0f) {
        Spaceship s = GetPlayer().GetSpaceshipStats();
        float new_current_fuel = s.currentFuel - ((0.0001f * (abs(v.current.x) + abs(v.current.y))) / s.fuelInfo.burningEfficiency);
        //PrintValueInGame(true, s.currentFuel - new_current_fuel, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 220.0f}, 20, WHITE);
        GetPlayer().UpdateSpaceshipCurrentFuel(new_current_fuel);
    }

    //Player Move:
    this->player.Move(GetDeltaT());
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) GetPlayer().SetVelocity(0.0f, 0.0f);
    this->player.UpdateAim(GetDeltaT());
}


// CAMERA 2D
Camera2D& Game::GetCamera() {
    return camera;
}

void Game::SetCamera() {
    camera.offset = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    camera.target = GetPlayer().GetPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;
}

void Game::SetCameraZoom(float zoom){
    this->camera.zoom = zoom;
}

void Game::UpdateCamera(int screenWidth, int screenHeight) {

    ////////// ZOOM
    float camera_zoom = camera.zoom;
    camera_zoom += GetMouseWheelMove() * 0.1f;

    if (camera_zoom > 2.0f) camera_zoom = 2.0f;
    else if (camera_zoom < 0.25f) camera_zoom = 0.25;
    SetCameraZoom(camera_zoom);

    ////////// OFFSET and TARGET

    this->camera.target = GetPlayer().GetPosition();
}

bool Game::isGameOver() {

    if (GetPlayer().GetLife().current <= 0.0f) return true;
    if (GetPlayer().GetSpaceshipStats().currentFuel <= 0.0f) return true;
    if (level.GetLevelCurrentMission().GetCurrentTime() <= 0.0f) return true;

    return false;
}

void Game::Update() {

    level.UpdateCurrentMissionTime(GetDeltaT());
    level.UpdateEntityTimers(GetDeltaT());

    if (IsKeyPressed(KEY_ESCAPE)) {
        SetCurrentGameState(GetGameStates().at(State::Paused));
        SetLastMousePosition(GetMousePosition());
        return;
    }
    
    UpdatePlayer();

    if (IsKeyDown(KEY_SPACE)) level.SpawnBullets(GetPlayer());

    level.SpawnAsteroids(GetPlayer());
    level.SpawnAliens(GetPlayer());

    UpdateCamera(GetScreenWidth(), GetScreenHeight());

    CheckEntityCollisions(GetDeltaT(), &level, &player);

    if (isGameOver()) SetCurrentGameState(GetGameStates().at(State::GameOver));

}

void Game::UpdateTime() {

    animation_t_now = static_cast<float>(GetTime());
    delta_t = animation_t_now - animation_t_prev;
    animation_t_prev = animation_t_now;
}

float Game::GetDeltaT() {
    return delta_t;
}

void Game::Render() {
    ClearBackground(Color{10, 10, 40, 255});

    BeginMode2D(GetCamera());

        //Draw Level Boundries
        DrawRectangleLinesEx( {0, 0, level.GetCurrentLevelBounds().back().x,  level.GetCurrentLevelBounds().back().y}, 15.0f, PURPLE);
        GetPlayer().DrawHitBox();
        GetPlayer().DrawHealthBar();
        GetPlayer().DrawAimDirection();
        //GetPlayer().DrawAimTarget();

        for (Alien& a : level.GetCurrentAliens()) { 
            a.DrawHitBox();
            a.DrawHealthBar();
            //a.DrawDirectionVector();
        }

        for (Bullet& b : level.GetCurrentBullets()) { b.DrawHitBox(); } 
        for (Asteroid& ast : level.GetCurrentAsteroids()) { ast.DrawHitBox();}
        
    EndMode2D();

    //CAMERA ZOOM
    PrintValueInGame(true, GetCamera().zoom - 0.5f, {50,50}, 30, WHITE);

    //PLAYER STATS
    GetPlayer().DrawSpacechipFuelBar();
    DrawText("COORDS", (int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 160.0f, 30, WHITE );
    PrintValueInGame(false, GetPlayer().GetPosition().x, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 120.0f}, 30, WHITE);
    PrintValueInGame(false, GetPlayer().GetPosition().y, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 90.0f}, 30, WHITE);
    DrawText("ACC", (int)GetScreenWidth()/2.0f - 200, (int)GetScreenHeight() - 160.0f, 30, WHITE );
    PrintValueInGame(true, GetPlayer().GetAcceleration().current.x, {(int)GetScreenWidth()/2.0f - 200, (int)GetScreenHeight() - 120.0f}, 30, WHITE);
    PrintValueInGame(true, GetPlayer().GetAcceleration().current.y, {(int)GetScreenWidth()/2.0f - 200, (int)GetScreenHeight() - 90.0f}, 30, WHITE);
    DrawText("VELOCITY", (int)GetScreenWidth()/2.0f + 200, (int)GetScreenHeight() - 160.0f, 30, WHITE );
    PrintValueInGame(false, GetPlayer().GetVelocity().current.x, {(int)GetScreenWidth()/2.0f + 200, (int)GetScreenHeight() - 120.0f}, 30, WHITE);
    PrintValueInGame(false, GetPlayer().GetVelocity().current.y, {(int)GetScreenWidth()/2.0f + 200, (int)GetScreenHeight() - 90.0f}, 30, WHITE);
    
    //MISSION STATS
    PrintTimerInGame(GetGameLevelMap().GetLevelCurrentMission().GetTotalTime(), GetGameLevelMap().GetLevelCurrentMission().GetCurrentTime(), {(int)GetScreenWidth()/2.0f, 120.0f}, 50);
    
    if (GetPlayer().GetisOutOfBounds()) {
        DrawText("WARNING!!!", GetScreenWidth()/2.0f - 200, GetScreenHeight() - 360, 80, RED);
        DrawText("The spaceship is entering the void",GetScreenWidth()/2.0f - 260, GetScreenHeight() - 280, 30, RED);
    }
}