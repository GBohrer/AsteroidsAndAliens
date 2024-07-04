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
    
    totalAliens = 5;
    totalAsteroids = 50;
    AlienSpawnTimer = 2.0f;
    BulletSpawnTimer = 0.9f;
    scoreThreshold = 10;
    AsteroidDirectionAngle = GetRandomValue(1,360) / 57.2957795f;

    while (GetAsteroidsInGame() < totalAsteroids) { SpawnAsteroids(); }
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

        Asteroid asteroid = Asteroid({posX, posY}, radius, life, 1);
        asteroid.SetPosition((float)posX, (float)posY);

        asteroid.SetDirection(Vector2Normalize({asteroid.GetPosition().x - (asteroid.GetPosition().x + 0.05f * cos(AsteroidDirectionAngle)),
                                                asteroid.GetPosition().y - (asteroid.GetPosition().y + 0.05f * sin(AsteroidDirectionAngle))}));

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
        Vector2 bullet_pos = {(pos.x + pos.width/2) + direction.x * 30,
                              (pos.y + pos.height/2) + direction.y * 30};

        this->bulletsInGame.push_back(Bullet(bullet_pos, direction, GetPlayer().GetCurrentSpeed() * 2.5, 0.8f, 20.0f));
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
    Vector2 player_pos = GetPlayer().GetPosition();
    float speed = GetPlayer().GetCurrentSpeed();

    if (IsKeyDown(KEY_W)) { player_pos.y -= speed; }
    if (IsKeyDown(KEY_A)) { player_pos.x -= speed; }
    if (IsKeyDown(KEY_S)) { player_pos.y += speed; }
    if (IsKeyDown(KEY_D)) { player_pos.x += speed; }

    Vector2 direction = Vector2Normalize(Vector2Subtract(player_pos, GetPlayer().GetPosition()));

    Vector2 min = GetCurrentLevelBounds().front();
    Vector2 max = GetCurrentLevelBounds().back();

    //float new_speed_min = pow(0.5f, abs(Vector2Distance(player_pos, min) / 10) );
    //float new_speed_max = pow(0.5f, abs(Vector2Distance(player_pos, max) / 10) );

    if (player_pos.x < min.x || player_pos.y < min.y) {
        isPlayerOutOfBounds = true;
        PlayerOutOfBoundsTimer += GetDeltaT();
        if (PlayerOutOfBoundsTimer >= 1.0f && speed > 0.2f) {
            GetPlayer().SetCurrentSpeed(speed/2.0f);
            PlayerOutOfBoundsTimer = 0;
        }
    } else if (player_pos.x > max.x || player_pos.y > max.y) {
        isPlayerOutOfBounds = true;
        PlayerOutOfBoundsTimer += GetDeltaT();
        if (PlayerOutOfBoundsTimer >= 1.0f && speed > 0.2f) {
            GetPlayer().SetCurrentSpeed(speed/2.0f);
            PlayerOutOfBoundsTimer = 0;
        }
    } else { 
        GetPlayer().SetCurrentSpeed(5.0f);
        isPlayerOutOfBounds = false;
    }

    this->player.Move(direction);
    this->player.UpdateAim();
}

void Game::UpdatePlayerScore() {
    this->GetPlayer().SetScore(this->GetPlayer().GetScore() + 1);
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

    //float minX = 10000, minY = 10000, maxX = -10000, maxY = -10000;
    //for (Vector2& pos : GetCurrentLevelBounds()) {
    //    minX = fminf(pos.x, minX);
    //    maxX = fmaxf(pos.x, maxX);
    //    minY = fminf(pos.y, minY);
    //    maxY = fmaxf(pos.y, maxY);
    //}
    //
    //Vector2 max = GetWorldToScreen2D({ maxX, maxY }, camera);
    //Vector2 min = GetWorldToScreen2D({ minX, minY }, camera);
    //if (max.x < screenWidth) camera.offset.x = screenWidth - (max.x - screenWidth/2);
    //if (max.y < screenHeight) camera.offset.y = screenHeight - (max.y - screenHeight/2);
    //if (min.x > 0) camera.offset.x = screenWidth/2 - min.x;
    //if (min.y > 0) camera.offset.y = screenHeight/2 - min.y;
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

bool Game::CheckDifficultyIncrease(int score) {
    if (score > scoreThreshold) {return true; }
    else {return false;}
}

void Game::IncreaseDifficulty() {
    totalAliens++;
    AlienSpawnTimer -= 0.5f;
    BulletSpawnTimer -= 0.02f;
    GetPlayer().SetCurrentSpeed(GetPlayer().GetCurrentSpeed() + 0.1f);

    scoreThreshold += 5;
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
                            Vector2 new_direction = (Vector2Add(a.GetDirection(), aa.GetDirection()));
                            aa.Move(GetPlayer(), GetDeltaT(), new_direction);
                            UpdateAlienInGame(aa, index2);
                            break;
                        }
                    }
                    index2++;
                }
            }

            if (!alien_collision) {
                a.Move(GetPlayer(), GetDeltaT(), a.GetDirection());
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
                GetPlayer().SetCurrentLife(GetPlayer().GetCurrentLife() - (b.GetDamage()/2.0f));
                DeleteBulletInGame(b_index);

                if (GetPlayer().GetCurrentLife() <= 0) {
                    SetCurrentGameState(GetGameStates().at(State::GameOver));
                    break;
                }
                
            } else {
                b.Move();
                UpdateBulletInGame(b, b_index);
            }

            if (GetAliensInGame() > 0) {

                int a_index = 0;
                for (Alien& a : GetCurrentAliens()) {
                    // BULLET - ALIEN
                    if (CollisionBulletAlien(b, a) && !delete_bullet) {

                        a.SetCurrentLife(a.GetCurrentLife() - b.GetDamage());
                        delete_bullet = true;

                        if(a.GetCurrentLife() <= 0) {
                            DeleteAlienInGame(a_index);
                            UpdatePlayerScore();
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
                ast.SetCurrentLife(ast.GetCurrentLife() - 1);
                if (ast.GetCurrentLife() <= 0) {delete_asteroid = true;}
            }

            //ASTEROID-ALIEN
            if (GetAliensInGame() > 0) {

                int a_index = 0;
                for (Alien& a : GetCurrentAliens()) {

                    if (CollisionAsteroidAlien(ast, a)) {
                        ast.Move(a.GetDirection());
                        UpdateAsteroidInGame(ast, ast_index);
                        a.SetCurrentSpeed(ast.GetCurrentSpeed());
                    }
                    a_index++;
                }
            }

            //ASTEROID-BULLET
            if(GetBulletsInGame() > 0) {

              int b_index = 0;
              for (Bullet& b : GetCurrentBullets()) {

                if (CollisionAsteroidBullet(ast, b)) {
                    ast.SetCurrentLife(ast.GetCurrentLife() - b.GetDamage());
                    DeleteBulletInGame(b_index);
                    if (ast.GetCurrentLife() <= 0) { delete_asteroid = true; }
                }
                b_index++;
              }  
            }

            //ASTEROID-PLAYER
            if (CollisionAsteroidPlayer(ast, GetPlayer())) {
                ast.Move(Vector2Scale(GetPlayer().GetDirection(), GetPlayer().GetCurrentSpeed()));
                UpdateAsteroidInGame(ast, ast_index);

            }

            //ASTEROID-ASTEROID
            if (GetAsteroidsInGame() > 1) {

                int ast2_index = 0;
                for (Asteroid& ast2 : GetCurrentAsteroids()) {

                    if (&ast != &ast2) {
                        if (CollisionAsteroidAsteroid(ast, ast2)) {

                            float ast_force = Vector2Length(ast.GetDirection());
                            float ast2_force = Vector2Length(ast2.GetDirection());

                            if (ast_force > ast2_force) {
                                ast2.Move(ast.GetDirection());
                                UpdateAsteroidInGame(ast2, ast2_index);
                            } else {
                                ast.SetDirection(ast2.GetDirection());
                                UpdateAsteroidInGame(ast, ast_index);
                            }
                            break;
                        }
                    }
                    ast2_index++;
                }
            }

            ast.Move(ast.GetDirection());
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