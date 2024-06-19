#include "../include/master_header.h"


Game::Game() {
    state = GameState::Menu;
    animation_t_now = animation_t_prev = delta_t = 0;
    SetCurrenLevelBounds({{0,0},{0,2000},{2000,2000}, {2000,0}} );
}

void Game::Start(std::string nickname) {
    this->state = GameState::InGame;
    totalAliens = 4;
    AlienSpawnTimer = 8.0f;
    BulletSpawnTimer = 0.5f;
    timeSinceLastShot = timeSinceLastAlienSpawn = 0.0f;
    scoreThreshold = 15;
    this->player = Player(nickname);
    SetCamera();
    SetCurrentAsteroidsInGame();
}

void Game::Reset() {
    this->state = GameState::Menu;
    aliensInGame.clear();
    bulletsInGame.clear();
    asteroidsInGame.clear();
}

std::vector<Vector2>& Game::GetCurrentLevelBounds() {
    return currentLevelBounds;
}

void Game::SetCurrenLevelBounds(std::vector<Vector2> level_bounds) {
    this->currentLevelBounds = level_bounds;
}

std::vector<Entity>& Game::GetCurrentAsteroidsInGame() {
    return asteroidsInGame;
}

void Game::SetCurrentAsteroidsInGame() {
    for (int i = 0; i < 10; i++){
        int posX = GetRandomValue(0,1000);
        int posY = GetRandomValue(0,1000);

        Entity asteroid = Entity();
        asteroid.SetPosition((float)posX, (float)posY);
        asteroidsInGame.push_back(asteroid);
    }
}

GameState Game::GetGameState() {
    return state;
}

void Game::SetGameState(GameState state) {
    this->state = state;
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
        this->bulletsInGame.push_back(Bullet(GetPlayer().GetPosition(), 200.0f, 0.4f, 20.0f));
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

void Game::PlayerMove() {
    Vector2 mouse = GetMousePosition();
    Vector2 direction = Vector2Subtract(mouse, player.GetPosition());

    this->player.Move(direction);
}

void Game::UpdatePlayerScore() {
    this->GetPlayer().SetScore(this->GetPlayer().GetScore() + 1);
}

// CAMERA 2D
Camera2D& Game::GetCamera() {
    return camera;
}

void Game::SetCamera() {
    camera.offset = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    camera.target = GetPlayer().GetPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Game::SetCameraZoom(float zoom){
    this->camera.zoom = zoom;
}

void Game::UpdateCamera(int screenWidth, int screenHeight) {
    //ZOOM
    float camera_zoom = GetCamera().zoom;
    camera_zoom += GetMouseWheelMove() * 0.1f;

    if (camera_zoom > 2.0f) camera_zoom = 2.0f;
    else if (camera_zoom < 0.25f) camera_zoom = 0.25;
    SetCameraZoom(camera_zoom);

    // OFFSET and TARGET
    camera.target = GetPlayer().GetPosition();


    //camera.offset = { screenWidth/2.0f, screenHeight/2.0f };
//
    //float minX = 10000, minY = 10000, maxX = -10000, maxY = -10000;
//
    //for (Vector2& pos : GetCurrentLevelBounds()){
    //    
    //    minX = fminf(pos.x, minX);
    //    maxX = fmaxf(pos.x, maxX);
    //    minY = fminf(pos.y, minY);
    //    maxY = fmaxf(pos.y, maxY);
    //}
//
    //Vector2 max = GetWorldToScreen2D((Vector2){ maxX, maxY }, camera);
    //Vector2 min = GetWorldToScreen2D((Vector2){ minX, minY }, camera);
//
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
    AlienSpawnTimer -= 0.2f;
    BulletSpawnTimer -= 0.02f;
    GetPlayer().SetSpeed(GetPlayer().GetSpeed() + 0.01f);

    scoreThreshold += 10;
}

void Game::CheckAliensCollisions() {

    if (GetAliensInGame() > 0) {

        int index1 = 0;
        for (Alien& a : GetCurrentAliens()) {
            bool collision = false;

            // Collision: Alien - Player
            if (CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), GetPlayer().GetHitBox())){
                state = GameState::GameOver;
                break;
            }

            int index2 = 0;
            for (Alien& aa : GetCurrentAliens()) {
                // Collision: Alien - Alien
                if (&a != &aa && CheckCollisionCircles(a.GetPosition(), (float)a.GetRadius(), aa.GetPosition(), (float)aa.GetRadius())) {
                    collision = true;

                    Vector2 new_direction = (Vector2Add(a.GetDirection(), aa.GetDirection()));
                    aa.Move(GetPlayer(), GetDeltaT(), new_direction);
                    UpdateAlienInGame(aa, index2);
                    break;
                }
                index2++;
            }

            if (!collision) {
                a.Move(GetPlayer(), GetDeltaT(), a.GetDirection());
                UpdateAlienInGame(a, index1);
            }
            index1++;
        }
    }
}

void Game::CheckBulletsCollisions() {

    if(GetBulletsInGame() > 0) {

        int index1 = 0;
        for (Bullet& bullet : GetCurrentBullets()){

            if (bullet.IsOutOfBounds(GetPlayer().GetPosition())) {
                DeleteBulletInGame(index1);
                continue;

            } else {
                bullet.Move(GetDeltaT());
                UpdateBulletInGame(bullet, index1);
            }

            int index2 = 0;
            for (Alien& alien : GetCurrentAliens()){
                // Collision: Alien - Bullet
                if (CheckCollisionCircleRec(alien.GetPosition(), (float)alien.GetRadius(), bullet.GetHitBox())){

                    alien.SetLife(alien.GetLife() - bullet.GetDamage());
                    DeleteBulletInGame(index1);

                    if (alien.GetLife() <= 0) {
                        DeleteAlienInGame(index2);
                        UpdatePlayerScore();
                    }
                }
                index2++;
            }
            index1++;
        }
    }
}