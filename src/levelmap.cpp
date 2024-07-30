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
            VoidMultiplier = 0.5f;
            VoidDecayTimer = 0.5f;
            VoidVelocity = 30.0f;
        break;

        case LevelDifficulty::EASY:
            totalAliens = 5;
            totalAsteroids = 50;
            AlienSpawnTimer = 4.0f;
            VoidMultiplier = 0.5f;
            VoidDecayTimer = 1.0f;
            VoidVelocity = 25.0f;
        break;

        case LevelDifficulty::MEDIUM:
            totalAliens = 8;
            totalAsteroids = 50;
            AlienSpawnTimer = 3.0f;
            VoidMultiplier = 1.0f;
            VoidDecayTimer = 1.0f;
            VoidVelocity = 15.0f;
        break;

        case LevelDifficulty::HARD:
            totalAliens = 10;
            totalAsteroids = 70;
            AlienSpawnTimer = 3.0f;
            VoidMultiplier = 2.0f;
            VoidDecayTimer = 1.5f;
            VoidVelocity = 10.0f;
        break;

        case LevelDifficulty::VERY_HARD:
            totalAliens = 10;
            totalAsteroids = 100;
            AlienSpawnTimer = 2.0f;
            VoidMultiplier = 3.0f;
            VoidDecayTimer = 1.5f;
            VoidVelocity = 2.0f;
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

        float Alien_spawn_angle = GetRandomValue(0, 360) / 57.2957795;
        Vector2 pos = {(float) p.GetPosition().x + 700 * cos(Alien_spawn_angle),
                       (float) p.GetPosition().y + 700 * sin(Alien_spawn_angle)};

        Alien a_aux = Alien(pos, radius, speed, life);
        a_aux.UpdateDirection(p);
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
        Vector2 pos = {(float)GetRandomValue((int)min.x, (int)max.x), (float)GetRandomValue((int)min.y, (int)max.y)};

        int radius = GetRandomValue(15,40);
        float life = radius*10;

        Asteroid asteroid = Asteroid(pos, radius, life);
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

void LevelMap::UpdateEntityVelocity(Entity* entity, float delta_t) {

    float time = entity->GetIsOutBoundsTime();
    EntityVelocity v = entity->GetVelocity();

    if (entity->CheckIsOutOfBounds(GetCurrentLevelBounds())) {
        entity->SetIsOutOfBounds(true);
        time += delta_t;

        if (v.current_max > VoidVelocity && abs(v.min) > VoidVelocity) {
            float velocity_decay = VoidMultiplier + time / 1000.0f;
            entity->SetVelocity(v.current, v.current_max - velocity_decay, v.current_min + velocity_decay);
            entity->SetSpeed(entity->GetSpeed() - velocity_decay / 100.0f);
        }
        entity->SetIsOutOfBoundsTime(time);

    } else {
        if (v.current_max != v.max || v.current_min != v.min) {

            entity->SetIsOutOfBounds(false);
            time = std::max(time - delta_t, 0.0f);

            if (v.current_max < v.max && abs(v.current_min) < abs(v.min)) {
                float velocity_decay = VoidMultiplier + time / 1000.0f;
                entity->SetVelocity(v.current, v.current_max + velocity_decay, v.current_min - velocity_decay);
                entity->SetSpeed(entity->GetSpeed() + velocity_decay / 100.0f);
            }
            entity->SetIsOutOfBoundsTime(time);
        }
    }
}

void LevelMap::UpdateEntites(float delta_t, Player* player) {

    CheckEntityCollisions(delta_t, this, player);

    // PLAYER
    UpdateEntityVelocity(player, delta_t);
    player->Update(delta_t);


    // ALIENS
    int a_index = 0;
    for (Alien& a : GetCurrentAliens()) {

        if (a.GetLife().current <= 0) DeleteAlienInGame(a_index);
        UpdateEntityVelocity(&a, delta_t);

        a_index++;
    }

    // ASTEROIDS
    int ast_index = 0;
    for (Asteroid& ast : GetCurrentAsteroids()) {

        if (ast.GetLife().current <= 0) DeleteAsteroidInGame(ast_index);
        UpdateEntityVelocity(&ast, delta_t);

        ast_index++;
    }

    // BULLETS
    int b_index = 0;
    for (Bullet& b : GetCurrentBullets()) {

        if (b.GetLife().current <= 0) DeleteBulletInGame(b_index);
        UpdateEntityVelocity(&b, delta_t);

        b_index++;
    }
}

void LevelMap::UpdateCurrentMissionTime(float delta_t) {
    currentMission.SetCurrentTime(currentMission.GetCurrentTime() - delta_t);
}

void LevelMap::UpdateEntityTimers(float delta_t) {
    timeSinceLastShot += delta_t;
    timeSinceLastAlienSpawn += delta_t;
}