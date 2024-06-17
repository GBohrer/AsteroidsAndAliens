#include "../include/master_header.h"


Game::Game() {
    state = GameState::Menu;
    animation_t_now = animation_t_prev = delta_t = 0;
}

void Game::Start(std::string nickname) {
    this->state = GameState::InGame;
    totalAliens = 4;
    AlienSpawnTimer = 2.0f;
    BulletSpawnTimer = 0.5f;
    timeSinceLastShot = timeSinceLastAlienSpawn = 0.0f;
    scoreThreshold = 15;
    this->player = Player(nickname);
    SetCamera();
}

void Game::Reset() {
    this->state = GameState::Menu;
    aliensInGame.clear();
    bulletsInGame.clear();
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
        Alien a_aux = Alien(30, 2.0f);
        a_aux.SetAlienToPlayer(GetPlayer(), 600);
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
    this->player.Move();
    //UpdateCamera();
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

void Game::UpdateCamera() {
    //camera->target = player->position;
    //camera->offset = (Vector2){ width/2.0f, height/2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    //for (int i = 0; i < envItemsLength; i++){
    //    EnvItem *ei = envItems + i;
    //    minX = fminf(ei->rect.x, minX);
    //    maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
    //    minY = fminf(ei->rect.y, minY);
    //    maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    //}

    Vector2 max = GetWorldToScreen2D({ maxX, maxY }, camera);
    Vector2 min = GetWorldToScreen2D({ minX, minY }, camera);
    float width = GetScreenWidth();
    float height = GetScreenHeight();

    if (max.x < width) camera.offset.x = width - (max.x - width/2);
    if (max.y < height) camera.offset.y = height - (max.y - height/2);
    if (min.x > 0) camera.offset.x = width/2 - min.x;
    if (min.y > 0) camera.offset.y = height/2 - min.y;
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

void Game::CheckEntityCollisions() {

    if (GetAliensInGame() != 0) {

        int index1 = 0;
        for (Alien& a : GetCurrentAliens()) {
            bool collision = false;

            // Collision: Alien - Player
            if (CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), GetPlayer().GetHitBox())){
                state = GameState::GameOver;
                break;
            }
            if(GetBulletsInGame() > 0) {
                int index2 = 0;
                for (Bullet& bullet : GetCurrentBullets()){
                    if (bullet.IsOutOfBounds(GetPlayer().GetPosition())) {
                        DeleteBulletInGame(index2);
                        continue;
                    }
                    // Collision: Alien - Bullet
                    if (CheckCollisionCircleRec(a.GetPosition(), (float)a.GetRadius(), bullet.GetHitBox())){
                        collision = true;
                        DeleteBulletInGame(index2);
                        DeleteAlienInGame(index1);
                        UpdatePlayerScore();
                    } else {
                        bullet.Move(GetDeltaT());
                        UpdateBulletInGame(bullet, index2);
                    }
                    index2++;
                }
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