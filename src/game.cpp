#include "../include/master_header.h"


Game::Game() {
    SetInitialGameStates();
    currentGameState = GetGameStates().at(State::InMenu);
}

void Game::Start() {
    SetCurrentGameState(GetGameStates().at(State::InGame));
    SetGameLevel();
    timeSinceLastShot = timeSinceLastAlienSpawn = PlayerOutOfBoundsTimer = 0.0f;
    animation_t_now = animation_t_prev = delta_t = 0.0f;
    isPlayerOutOfBounds = false;
    this->player = Player(Vector2Scale(GetCurrentLevelBounds().back(), 0.5f));
    SetCamera();
    SetMousePosition((int)GetScreenWidth()/2.0f, (int)GetScreenHeight()/2.0f);
}

void Game::Reset() {
    currentGameState = GetGameStates().at(State::InMenu);
    aliensInGame.clear();
    bulletsInGame.clear();
    asteroidsInGame.clear();
}

void Game::SetGameLevel() {
    SetCurrenLevelBounds({{0,0}, {4000,4000}});
    SetScore(0);
    
    totalAliens = 5;
    totalAsteroids = 50;
    AlienSpawnTimer = 4.0f;
    BulletSpawnTimer = 0.1f;
    scoreThreshold = 10;
    VoidVelocityDecay = 10.0f;
    VoidDecayTimer = 1.0f;
    VoidVelocityMin = 10.0f;
    AsteroidDirectionAngle = GetRandomValue(1,360) / 57.2957795f;

    while (GetAsteroidsInGame() < totalAsteroids) { SpawnAsteroids(); }
}

void Game::IncreaseDifficulty() {
    totalAliens++;
    AlienSpawnTimer -= 0.5f;
    BulletSpawnTimer -= 0.03f;
    scoreThreshold += 5;
}

bool Game::CheckDifficultyIncrease() {
    if (GetScore() > scoreThreshold) { return true; } else { return false; }
}

void Game::UpdateAnimationTime() {
    animation_t_now = (float)GetTime();
    delta_t = animation_t_now - animation_t_prev;
    animation_t_prev = animation_t_now;

    timeSinceLastShot += delta_t;
    timeSinceLastAlienSpawn += delta_t;
}

float Game::GetDeltaT() {
    return delta_t;
}

int Game::GetScore() {
    return score;
}

void Game::SetScore(int value) {
    this->score = value;
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


// LEVEL
std::vector<Vector2>& Game::GetCurrentLevelBounds() {
    return currentLevelBounds;
}

void Game::SetCurrenLevelBounds(std::vector<Vector2> level_bounds) {
    this->currentLevelBounds = level_bounds;
}


// ASTEROIDS
std::vector<Asteroid>& Game::GetCurrentAsteroids() {
    return asteroidsInGame;
}

int Game::GetAsteroidsInGame() {
    if (asteroidsInGame.empty()) { return 0; }
    else { return (int)asteroidsInGame.size(); }
}

void Game::SpawnAsteroids() {

    if (GetAsteroidsInGame() < totalAsteroids) {

        Vector2 min = GetCurrentLevelBounds().front();
        Vector2 max = GetCurrentLevelBounds().back();

        float posX = GetRandomValue((int)min.x, (int)max.x);
        float posY = GetRandomValue((int)min.y, (int)max.y);

        int radius = GetRandomValue(15,40);
        float life = radius*10;

        Asteroid asteroid = Asteroid({posX, posY}, radius, life);
        Vector2 dir = {asteroid.GetPosition().x - (asteroid.GetPosition().x + 10.0f * cos(AsteroidDirectionAngle)),
                       asteroid.GetPosition().y - (asteroid.GetPosition().y + 10.0f * sin(AsteroidDirectionAngle))};

        asteroid.SetVelocity(dir.x, dir.y);

        if (!CollisionAsteroidPlayer(asteroid, GetPlayer())) { asteroidsInGame.push_back(asteroid); }
    }
}

void Game::UpdateAsteroidInGame(Asteroid ast, int position) {
    this->asteroidsInGame[position] = ast;
}

void Game::DeleteAsteroidInGame(int position) {
    this->asteroidsInGame.erase(asteroidsInGame.begin() + position);
}


// ALIENS
std::vector<Alien>& Game::GetCurrentAliens() {
    return aliensInGame;
}

int Game::GetAliensInGame() {
    if (aliensInGame.empty()) { return 0; }
    else { return (int)aliensInGame.size(); }
}

void Game::SpawnAliens() {
    if (GetAliensInGame() < totalAliens && timeSinceLastAlienSpawn >= AlienSpawnTimer){
        int radius = GetRandomValue(15,40);
        float speed = -0.076 * radius + 4.14;
        float life = radius*2;

        Alien a_aux = Alien(radius, speed, life);
        a_aux.SetAlienToPlayer(GetPlayer(), 700);
        this->aliensInGame.push_back(a_aux);

        timeSinceLastAlienSpawn = 0.0f;
    }
}

void Game::UpdateAlienInGame(Alien alien, int position){
    this->aliensInGame[position] = alien;
}

void Game::DeleteAlienInGame(int position) {
    this->aliensInGame.erase(aliensInGame.begin() + position);
}

// BULLETS
std::vector<Bullet>& Game::GetCurrentBullets() {
    return bulletsInGame;
}

int Game::GetBulletsInGame() {
    if (bulletsInGame.empty()) {return 0; }
    else { return (int)bulletsInGame.size(); }
}

void Game::SpawnBullets() {
    if (timeSinceLastShot >= BulletSpawnTimer){

        Vector2 direction = Vector2Normalize(Vector2Subtract(GetPlayer().GetAimTarget(), GetPlayer().GetPosition()));

        Rectangle pos = GetPlayer().GetHitBox();
        Vector2 bullet_pos = {(pos.x + pos.width/2) + direction.x * 35.0f,
                              (pos.y + pos.height/2) + direction.y * 35.0f};

        this->bulletsInGame.push_back(Bullet(bullet_pos, direction, 10.0f, 0.8f, 20.0f));
        timeSinceLastShot = 0.0f;
    }
}

void Game::UpdateBulletInGame(Bullet bullet, int position) {
    this->bulletsInGame[position] = bullet;
}

void Game::DeleteBulletInGame(int position) {
    this->bulletsInGame.erase(bulletsInGame.begin() + position);
}

// PLAYER
Player& Game::GetPlayer() {
    return player;
}

void Game::SetPlayer(Player p) {
    this->player = player;
}

void Game::UpdatePlayer() {

    Vector2 min = GetCurrentLevelBounds().front();
    Vector2 max = GetCurrentLevelBounds().back();
    EntityVelocity v = GetPlayer().GetVelocity();
    Vector2 player_pos = GetPlayer().GetPosition();

    PlayerOutOfBoundsTimer += GetDeltaT();

    if (player_pos.x < min.x || player_pos.y < min.y || player_pos.x > max.x || player_pos.y > max.y) {
        isPlayerOutOfBounds = true;
        if (PlayerOutOfBoundsTimer >= VoidDecayTimer && v.max > VoidVelocityMin) {
            GetPlayer().SetVelocity(v.current, v.max - VoidVelocityDecay, v.min + VoidVelocityDecay);
            PlayerOutOfBoundsTimer = 0;
        }
    } else { 
        isPlayerOutOfBounds = false;
        if (PlayerOutOfBoundsTimer >= VoidDecayTimer * 0.20f && v.max < GetPlayer().GetSpaceshipStats().VelocityMax) {
            GetPlayer().SetVelocity(v.current, v.max + VoidVelocityDecay, v.min - VoidVelocityDecay);
            PlayerOutOfBoundsTimer = 0;
        }
    }

    this->player.Move(GetDeltaT());
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) game.GetPlayer().SetVelocity(0.0f, 0.0f);
    this->player.UpdateAim(GetDeltaT());
}

bool Game::IsPlayerOutOfBounds() {
    return isPlayerOutOfBounds;
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


// COLLISIONS
bool Game::CollisionAlienAlien(Alien a1, Alien a2) {

    if (CheckCollisionCircles(a1.GetPosition(), (float)a1.GetRadius(), a2.GetPosition(), (float)a2.GetRadius())) {
        return true;
    } else {
        return false;
    }
}

bool Game::CollisionAlienPlayer(Alien a) {

    if (CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), GetPlayer().GetHitBox())) {
        return true;
    } else {
        return false;
    }
}

// ALIEN COLLISIONS
void Game::CheckAlienCollisions() {

    if (GetAliensInGame() > 0){

        bool alien_collision = false;
        int index1 = 0;
        for (Alien& a : GetCurrentAliens()) {
            // ALIEN - PLAYER
            if (CollisionAlienPlayer(a)){
                SetCurrentGameState(GetGameStates().at(State::GameOver));
                break;
            }
            
            if (GetAliensInGame() > 1) {
                alien_collision = false;
                int index2 = 0;

                for (Alien& aa : GetCurrentAliens()) {
                    // ALIEN - ALIEN
                    if (&a != &aa) {
                        if (CollisionAlienAlien(a, aa)) {
                            alien_collision = true;
                            
                            const auto velocities = CollisionResponse(a.GetVelocity().current, aa.GetVelocity().current,
                                                                      a.GetPosition(), aa.GetPosition(),
                                                                      a.GetRadius(), aa.GetRadius());
                            Vector2 a_v = std::get<0>(velocities);
                            a.SetVelocity(a_v.x, a_v.y);
                            UpdateAlienInGame(a, index1);
                            
                            a_v = std::get<1>(velocities);
                            aa.SetVelocity(a_v.x, a_v.y);
                            UpdateAlienInGame(aa, index2);
                            break;
                        }
                    }
                    index2++;
                }
            }

            if (!alien_collision) {
                a.Move(GetPlayer(), GetDeltaT());
                UpdateAlienInGame(a, index1);
            }
            index1++;
        }
    }
}

bool Game::CollisionBulletAlien(Bullet b, Alien a) {

    if (CheckCollisionCircleRec(a.GetPosition(), (float)a.GetRadius(), b.GetHitBox())) {
        return true;
    } else {
        return false;
    }
}

bool Game::CollisionBulletPlayer(Bullet b) {
    if (CheckCollisionRecs(b.GetHitBox(), GetPlayer().GetHitBox())) {
        return true;
    } else {
        return false;
    }
}

// BULLET COLLISIONS
void Game::CheckBulletCollisions() {

    if (GetBulletsInGame() > 0) {

        int b_index = 0;
        bool delete_bullet;
        for (Bullet& b : GetCurrentBullets()) {
            delete_bullet = false;
            // BULLET MOVEMENT

            if (b.IsOutOfBounds(GetPlayer().GetPosition())) {
                DeleteBulletInGame(b_index);
                continue;

            // BULLET - PLAYER
            } else if (CollisionBulletPlayer(b)) {
                float new_life = GetPlayer().GetLife().current - (b.GetDamage()/2.0f);
                GetPlayer().UpdateCurrentLife(new_life);
                DeleteBulletInGame(b_index);

                if (GetPlayer().GetLife().current <= 0) {
                    SetCurrentGameState(GetGameStates().at(State::GameOver));
                    break;
                }
                
            } else {
                b.Move(GetDeltaT());
                UpdateBulletInGame(b, b_index);
            }

            if (GetAliensInGame() > 0) {

                int a_index = 0;
                for (Alien& a : GetCurrentAliens()) {
                    // BULLET - ALIEN
                    if (CollisionBulletAlien(b, a) && !delete_bullet) {
                        float new_life = a.GetLife().current - b.GetDamage();
                        a.UpdateCurrentLife(new_life);
                        delete_bullet = true;

                        if(a.GetLife().current <= 0) {
                            DeleteAlienInGame(a_index);
                            SetScore(GetScore() + 1);
                        }
                    }
                    a_index++;
                }
            }
            if(delete_bullet) DeleteBulletInGame(b_index);
            b_index++;
        }
    }
}

bool Game::CollisionAsteroidAsteroid(Asteroid ast1, Asteroid ast2) {
    if (CheckCollisionCircles(ast1.GetPosition(), ast1.GetRadius(), ast2.GetPosition(), ast2.GetRadius())) {
        return true;
    } else {
        return false;
    }
}

bool Game::CollisionAsteroidAlien(Asteroid ast, Alien a) {
    if (CheckCollisionCircles(ast.GetPosition(), ast.GetRadius(), a.GetPosition(), a.GetRadius())) {
        return true;
    } else {
        return false;
    }
}

bool Game::CollisionAsteroidBullet(Asteroid ast, Bullet b) {
    if (CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), b.GetHitBox())) {
        return true;
    } else {
        return false;
    }
}

bool Game::CollisionAsteroidPlayer(Asteroid ast, Player p) {
    if (CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), p.GetHitBox())) {
        return true;
    } else {
        return false;
    }
}

// ASTEROID COLLISIONS
void Game::CheckAsteroidCollisions () {
    if (GetAsteroidsInGame() > 0) {

        int ast_index = 0;
        for (Asteroid& ast : GetCurrentAsteroids()) {
            bool delete_asteroid = false;

            if (ast.IsOutOfBounds(GetCurrentLevelBounds())) {
                float new_life = ast.GetLife().current - 1.0f;
                ast.UpdateCurrentLife(new_life);
                if (ast.GetLife().current <= 0) {delete_asteroid = true;}
            }

            //ASTEROID-ALIEN
            if (GetAliensInGame() > 0) {

                int a_index = 0;
                for (Alien& a : GetCurrentAliens()) {

                    if (CollisionAsteroidAlien(ast, a)) {
                        const auto velocities = CollisionResponse(ast.GetVelocity().current, a.GetVelocity().current,
                                                                  ast.GetPosition(), a.GetPosition(),
                                                                  ast.GetRadius(), a.GetRadius());
                        Vector2 ast_v = std::get<0>(velocities);
                        ast.SetVelocity(ast_v.x, ast_v.y);
                        UpdateAsteroidInGame(ast, ast_index);
                        
                        Vector2 a_v = std::get<1>(velocities);
                        a.SetVelocity(a_v.x, a_v.y);
                        UpdateAlienInGame(a, a_index);
                    }
                    a_index++;
                }
            }

            //ASTEROID-BULLET
            if(GetBulletsInGame() > 0) {

              int b_index = 0;
              for (Bullet& b : GetCurrentBullets()) {

                if (CollisionAsteroidBullet(ast, b)) {
                    float new_life = ast.GetLife().current - b.GetDamage();
                    ast.UpdateCurrentLife(new_life);
                    DeleteBulletInGame(b_index);
                    if (ast.GetLife().current <= 0) { delete_asteroid = true; }
                }
                b_index++;
              }  
            }

            //ASTEROID-PLAYER
            if (CollisionAsteroidPlayer(ast, GetPlayer())) {
                
                const auto velocities = CollisionResponse(ast.GetVelocity().current, GetPlayer().GetVelocity().current,
                                                          ast.GetPosition(), GetPlayer().GetPosition(),
                                                          ast.GetRadius(), GetPlayer().GetHitBox().width);
                Vector2 ast_v = std::get<0>(velocities);
                ast.SetVelocity(ast_v.x, ast_v.y);
                UpdateAsteroidInGame(ast, ast_index);

                Vector2 player_v = std::get<1>(velocities);
                GetPlayer().SetVelocity(player_v.x, player_v.y);
            }

            //ASTEROID-ASTEROID
            if (GetAsteroidsInGame() > 1) {

                int ast2_index = 0;
                for (Asteroid& ast2 : GetCurrentAsteroids()) {

                    if (&ast != &ast2) {
                        if (CollisionAsteroidAsteroid(ast, ast2)) {

                            const auto velocities = CollisionResponse(ast.GetVelocity().current, ast2.GetVelocity().current,
                                                                      ast.GetPosition(), ast2.GetPosition(),
                                                                      ast.GetRadius(), ast2.GetRadius());
                            Vector2 ast_v = std::get<0>(velocities);
                            ast.SetVelocity(ast_v.x, ast_v.y);
                            UpdateAsteroidInGame(ast, ast_index);

                            ast_v = std::get<1>(velocities);
                            ast2.SetVelocity(ast_v.x, ast_v.y);
                            UpdateAsteroidInGame(ast2, ast2_index);
                        }
                    }
                    ast2_index++;
                }
            }

            ast.Move(GetDeltaT());
            UpdateAsteroidInGame(ast, ast_index);

            if (delete_asteroid) DeleteAsteroidInGame(ast_index);
            ast_index++;
        }
    }
}

void Game::CheckEntityCollisions() {

    CheckAlienCollisions();
    CheckBulletCollisions();
    CheckAsteroidCollisions();
}

std::tuple<Vector2, Vector2> Game::CollisionResponse (Vector2 v1, Vector2 v2, Vector2 pos1, Vector2 pos2, float m1, float m2) {

    Vector2 C1 = Vector2Subtract(pos1,pos2);
    Vector2 C2 = Vector2Subtract(pos2,pos1);

    float value1 = (2 * m2) / (m1 + m2);
    float value2 = Vector2DotProduct(v1,C1) - Vector2DotProduct(v2,C1);
    float value3 = Vector2LengthSqr(C1);

    Vector2 new_velocity1 = Vector2Subtract(v1, (Vector2Scale(C1,(value1 * value2 / value3))));

    value1 = (2 * m1) / (m1 + m2);
    value2 = Vector2DotProduct(v2,C2) - Vector2DotProduct(v1,C2);
    value3 = Vector2LengthSqr(C2);

    Vector2 new_velocity2 = Vector2Subtract(v2, (Vector2Scale(C2,(value1 * value2 / value3))));

    return {new_velocity1, new_velocity2};

}