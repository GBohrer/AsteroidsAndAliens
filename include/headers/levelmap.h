#pragma once
#include "../master_header.h"

enum LevelDifficulty {
    VERY_EASY,
    EASY,
    MEDIUM,
    HARD,
    VERY_HARD
};

class LevelMap {

    public:
        LevelMap();

        void Set(Player p);
        void Reset();
        void ClearEntities();
        void SetLevelModifiers(LevelDifficulty ld);

        std::vector<Vector2>& GetCurrentLevelBounds();
        void SetCurrenLevelBounds(std::vector<Vector2> bounds);

        Mission& GetLevelCurrentMission();
        void SetLevelCurrentMission(Mission m);
        void SetMission();

    //Aliens
        std::vector<Alien>& GetCurrentAliens();
        int GetAliensInGame();
        void SpawnAliens(Player p);
        void UpdateAlienInGame(Alien alien, int position);
        void DeleteAlienInGame(int position);

    //Asteroids
        std::vector<Asteroid>& GetCurrentAsteroids();
        int GetAsteroidsInGame();
        void SpawnAsteroids(Player p);
        void UpdateAsteroidInGame(Asteroid ast, int position);
        void DeleteAsteroidInGame(int position);

    //Bullets
        std::vector<Bullet>& GetCurrentBullets();
        int GetBulletsInGame();
        void SpawnBullets(Player p);
        void UpdateBulletInGame(Bullet bullet, int position);
        void DeleteBulletInGame(int position);

        bool EntityIsOutOfBounds(Vector2 pos);
        EntityVelocity UpdateVelocityByVoidDecay(EntityVelocity v, float time);

        void UpdateCurrentMissionTime(float delta_t);
        void UpdateEntityTimers(float delta_t);

    protected:
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;

    private:

    // Entities
        std::vector<Alien> aliensInGame;
        std::vector<Asteroid> asteroidsInGame;
        std::vector<Bullet> bulletsInGame;

    // Current LevelMap-Modifiers
        int totalAliens;
        int totalAsteroids;
        float AlienSpawnTimer;
        float BulletSpawnTimer;
        float AsteroidDirectionAngle;
        float VoidVelocityDecay;
        float VoidVelocityMin;
        float VoidDecayTimer;

    // Level Componds
        std::vector<Vector2> LevelBounds;
        LevelDifficulty ld;
        Mission currentMission;

};