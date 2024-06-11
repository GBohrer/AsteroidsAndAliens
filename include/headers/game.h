#pragma once
#include "../master_header.h"

#include "bullet.h"

class Game {

    public:
        Game();

        std::vector<Alien> GetCurrentAliens();
        int GetAliensInGame();
        void SpawnAliens();
        void UpdateAlienInGame(Alien alien, int position);
        void DeleteAlienInGame(int position);

        std::vector<Bullet> GetCurrentBullets();
        int GetBulletsInGame();
        void SpawnBullets();
        void UpdateBulletInGame(Bullet bullet, int position);
        void DeleteBulletInGame(int position);

        Player GetPlayer();
        void SetPlayer(Player p);
        void PlayerMove();
        void UpdatePlayerScore(int value);

        void UpdateAnimationTime();
        float GetDeltaT();

        bool CheckDifficultyIncrease(int score);
        void IncreaseDifficulty();

    protected:
        int totalAliens;
        float AlienSpawnTimer;
        float BulletSpawnTimer;
        int scoreThreshold;

    private:
        std::vector<Alien> aliensInGame;
        std::vector<Bullet> bulletsInGame;
        Player player;
        
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;
};

