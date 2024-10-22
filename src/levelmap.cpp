#include "../include/master_header.h"


LevelMap::LevelMap() {};

void LevelMap::Set(Player p) {
    timeSinceLastShot = timeSinceLastAlienSpawn = 0.0f;
    SetCurrenLevelBounds({{0,0}, {5000,5000}});
    SetLevelModifiers(LevelDifficulty::MEDIUM);
    SetMission();
    while (GetAsteroidsInGame() < totalAsteroids) { SpawnAsteroids(p); }
}

void LevelMap::Reset() {
    ClearEntities();
}

void LevelMap::ClearEntities() {
    aliensInGame.clear();
    bulletsInGame.clear();
    asteroidsInGame.clear();
}

void LevelMap::SetLevelModifiers(LevelDifficulty ld) {
    
    switch(ld) {
        case LevelDifficulty::VERY_EASY:
            totalAliens = 2;
            totalAsteroids = 20;
            AlienSpawnTimer = 5.0f;
            VoidVelocityDecay = 5.0f;
            VoidDecayTimer = 1.0f;
            VoidVelocityMin = 30.0f;
        break;

        case LevelDifficulty::EASY:
            totalAliens = 5;
            totalAsteroids = 50;
            AlienSpawnTimer = 4.0f;
            VoidVelocityDecay = 10.0f;
            VoidDecayTimer = 1.0f;
            VoidVelocityMin = 25.0f;
        break;

        case LevelDifficulty::MEDIUM:
            totalAliens = 8;
            totalAsteroids = 50;
            AlienSpawnTimer = 3.0f;
            VoidVelocityDecay = 15.0f;
            VoidDecayTimer = 1.0f;
            VoidVelocityMin = 15.0f;
        break;

        case LevelDifficulty::HARD:
            totalAliens = 10;
            totalAsteroids = 70;
            AlienSpawnTimer = 3.0f;
            VoidVelocityDecay = 15.0f;
            VoidDecayTimer = 0.5f;
            VoidVelocityMin = 10.0f;
        break;

        case LevelDifficulty::VERY_HARD:
            totalAliens = 10;
            totalAsteroids = 100;
            AlienSpawnTimer = 2.0f;
            VoidVelocityDecay = 25.0f;
            VoidDecayTimer = 0.5f;
            VoidVelocityMin = 2.0f;
        break;

        default:
        break;

    }
    AsteroidDirectionAngle = GetRandomValue(1,360) / 57.2957795f;
    BulletSpawnTimer = 1.0f;
}

std::vector<Vector2>& LevelMap::GetCurrentLevelBounds() {
    return LevelBounds;
}

void LevelMap::SetCurrenLevelBounds(std::vector<Vector2> bounds) {
    this->LevelBounds = bounds;
}

Mission& LevelMap::GetLevelCurrentMission() {
    return currentMission;
}

void LevelMap::SetLevelCurrentMission(Mission m) {
    this->currentMission = m;
}

void LevelMap::SetMission() {
    Mission m = Mission();
    m.SetTotalTime(100.0f);
    m.SetCurrentTime(m.GetTotalTime());
    SetLevelCurrentMission(m);
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

void LevelMap::SpawnAsteroids(Player p) {

    if (GetAsteroidsInGame() < totalAsteroids) {

        Vector2 min = GetCurrentLevelBounds().front();
        Vector2 max = GetCurrentLevelBounds().back();

        float posX = GetRandomValue((int)min.x, (int)max.x);
        float posY = GetRandomValue((int)min.y, (int)max.y);

        int radius = GetRandomValue(15,40);
        float life = radius*10;

        Asteroid asteroid = Asteroid({posX, posY}, radius, life);
        asteroid.SetVelocity(cos(AsteroidDirectionAngle) * 10.0f, sin(AsteroidDirectionAngle) * 10.0f);
        if (!CheckCollisionPlayerAsteroid(p, asteroid)) asteroidsInGame.push_back(asteroid);
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

void LevelMap::UpdateCurrentMissionTime(float delta_t) {
    currentMission.SetCurrentTime(currentMission.GetCurrentTime() - delta_t);
}

void LevelMap::UpdateEntityTimers(float delta_t) {
    timeSinceLastShot += delta_t;
    timeSinceLastAlienSpawn += delta_t;
}