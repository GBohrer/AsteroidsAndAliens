#pragma once
#include "../master_header.h"


class LevelMap {

    public:
        LevelMap();

        void Set();
        void Reset();
        void ResetTimestamps();
        void ClearEntities();
        void SetLevelModifiers();

        std::vector<Vector2>& GetCurrentLevelBounds();
        void SetCurrenLevelBounds(std::vector<Vector2> level_bounds);


    //Aliens
        std::vector<Alien>& GetCurrentAliens();
        int GetAliensInGame();
        void SpawnAliens(Player p);
        void UpdateAlienInGame(Alien alien, int position);
        void DeleteAlienInGame(int position);

    //Asteroids
        std::vector<Asteroid>& GetCurrentAsteroids();
        int GetAsteroidsInGame();
        void SpawnAsteroids();
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

        void UpdateAnimationTime();
        float GetDeltaT();

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

        std::vector<Vector2> currentLevelBounds;
        bool isPlayerOutOfBounds;
        float PlayerOutOfBoundsTimer;
        
        float VoidVelocityDecay;
        float VoidVelocityMin;
        float VoidDecayTimer;

    // Timestamps
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;

};