#include "../include/master_header.h"


LevelMap::LevelMap() {};

void LevelMap::Set() {
    ResetTimestamps();
    SetLevelModifiers();
}

void LevelMap::Reset() {
    ResetTimestamps();
    ClearEntities();
}

void LevelMap::ResetTimestamps() {
    timeSinceLastShot = timeSinceLastAlienSpawn = PlayerOutOfBoundsTimer = 0.0f;
    animation_t_now = animation_t_prev = delta_t = 0.0f;
}

void LevelMap::ClearEntities() {
    aliensInGame.clear();
    bulletsInGame.clear();
    asteroidsInGame.clear();
}

void LevelMap::SetLevelModifiers() {
    SetCurrenLevelBounds({{0,0}, {4000,4000}});
    
    totalAliens = 5;
    totalAsteroids = 50;
    AlienSpawnTimer = 4.0f;
    BulletSpawnTimer = 1.0f;
    VoidVelocityDecay = 10.0f;
    VoidDecayTimer = 1.0f;
    VoidVelocityMin = 10.0f;
    AsteroidDirectionAngle = GetRandomValue(1,360) / 57.2957795f;

    while (GetAsteroidsInGame() < totalAsteroids) { SpawnAsteroids(); }
}

std::vector<Vector2>& LevelMap::GetCurrentLevelBounds() {
    return currentLevelBounds;
}

void LevelMap::SetCurrenLevelBounds(std::vector<Vector2> level_bounds) {
    this->currentLevelBounds = level_bounds;
}

// ALIENS
std::vector<Alien>& LevelMap::GetCurrentAliens() {
    return aliensInGame;
}

int LevelMap::GetAliensInGame() {
    if (aliensInGame.empty()) { return 0; }
    else { return (int)aliensInGame.size(); }
}

void LevelMap::SpawnAliens(Player p) {
    if (GetAliensInGame() < totalAliens && timeSinceLastAlienSpawn >= AlienSpawnTimer){
        int radius = GetRandomValue(15,40);
        float speed = -0.076 * radius + 204.14;
        float life = radius*2;

        Alien a_aux = Alien(radius, speed, life);
        a_aux.SetAlienToPlayer(p, 700);
        this->aliensInGame.push_back(a_aux);

        timeSinceLastAlienSpawn = 0.0f;
    }
}

void LevelMap::UpdateAlienInGame(Alien alien, int position){
    this->aliensInGame[position] = alien;
}

void LevelMap::DeleteAlienInGame(int position) {
    this->aliensInGame.erase(aliensInGame.begin() + position);
}

// ASTEROIDS
std::vector<Asteroid>& LevelMap::GetCurrentAsteroids() {
    return asteroidsInGame;
}

int LevelMap::GetAsteroidsInGame() {
    if (asteroidsInGame.empty()) { return 0; }
    else { return (int)asteroidsInGame.size(); }
}

void LevelMap::SpawnAsteroids() {

    if (GetAsteroidsInGame() < totalAsteroids) {

        Vector2 min = GetCurrentLevelBounds().front();
        Vector2 max = GetCurrentLevelBounds().back();

        float posX = GetRandomValue((int)min.x, (int)max.x);
        float posY = GetRandomValue((int)min.y, (int)max.y);

        int radius = GetRandomValue(15,40);
        float life = radius*10;

        Asteroid asteroid = Asteroid({posX, posY}, radius, life);
        //asteroid.SetVelocity(cos(AsteroidDirectionAngle) * 10.0f, sin(AsteroidDirectionAngle) * 10.0f);
        asteroidsInGame.push_back(asteroid);
        //if (!CollisionAsteroidPlayer(asteroid)) { asteroidsInGame.push_back(asteroid); }
    }
}

void LevelMap::UpdateAsteroidInGame(Asteroid ast, int position) {
    this->asteroidsInGame[position] = ast;
}

void LevelMap::DeleteAsteroidInGame(int position) {
    this->asteroidsInGame.erase(asteroidsInGame.begin() + position);
}

// BULLETS
std::vector<Bullet>& LevelMap::GetCurrentBullets() {
    return bulletsInGame;
}

int LevelMap::GetBulletsInGame() {
    if (bulletsInGame.empty()) {return 0; }
    else { return (int)bulletsInGame.size(); }
}

void LevelMap::SpawnBullets(Player p) {
    if (timeSinceLastShot >= BulletSpawnTimer){

        Vector2 direction = Vector2Normalize(Vector2Subtract(p.GetAimTarget(), p.GetPosition()));

        Rectangle pos = p.GetHitBox();
        Vector2 bullet_pos = {(pos.x + pos.width/2) + direction.x * 35.0f,
                              (pos.y + pos.height/2) + direction.y * 35.0f};

        this->bulletsInGame.push_back(Bullet(bullet_pos, direction, 10.0f, 0.8f, 20.0f));
        timeSinceLastShot = 0.0f;
    }
}

void LevelMap::UpdateBulletInGame(Bullet bullet, int position) {
    this->bulletsInGame[position] = bullet;
}

void LevelMap::DeleteBulletInGame(int position) {
    this->bulletsInGame.erase(bulletsInGame.begin() + position);
}


bool LevelMap::EntityIsOutOfBounds(Vector2 pos) {

    Vector2 min = GetCurrentLevelBounds().front();
    Vector2 max = GetCurrentLevelBounds().back();

    if (pos.x < min.x || pos.y < min.y || pos.x > max.x || pos.y > max.y) {
        return true;
    } else {
        return false;
    }
}

EntityVelocity LevelMap::UpdateVelocityByVoidDecay(EntityVelocity v, float time) {

    EntityVelocity new_v(v.current, v.max - VoidVelocityDecay, v.min + VoidVelocityDecay);

    return new_v;
}



void LevelMap::UpdateAnimationTime() {
    animation_t_now = (float)GetTime();
    delta_t = animation_t_now - animation_t_prev;
    animation_t_prev = animation_t_now;

    timeSinceLastShot += delta_t;
    timeSinceLastAlienSpawn += delta_t;
}

float LevelMap::GetDeltaT() {
    return delta_t;
}