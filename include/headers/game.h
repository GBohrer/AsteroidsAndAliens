#pragma once
#include "../master_header.h"

#include "bullet.h"

enum GameState {
    Menu,
    InGame,
    GameOver,
    Paused
};

class Game {

    public:
        Game();

        GameState GetGameState();
        void SetGameState(GameState state);

        std::vector<Alien>& GetCurrentAliens();
        int GetAliensInGame();
        void SpawnAliens();
        void UpdateAlienInGame(Alien alien, int position);
        void DeleteAlienInGame(int position);

        std::vector<Bullet>& GetCurrentBullets();
        int GetBulletsInGame();
        void SpawnBullets();
        void UpdateBulletInGame(Bullet bullet, int position);
        void DeleteBulletInGame(int position);

        Player& GetPlayer();
        void SetPlayer(Player p);
        void PlayerMove();
        void UpdatePlayerScore();

        void UpdateAnimationTime();
        float GetDeltaT();

        bool CheckDifficultyIncrease(int score);
        void IncreaseDifficulty();

        void CheckEntityCollisions();

    protected:
        int totalAliens;
        float AlienSpawnTimer;
        float BulletSpawnTimer;
        int scoreThreshold;


    private:
        GameState state;
        std::vector<Alien> aliensInGame;
        std::vector<Bullet> bulletsInGame;
        Player player;
        
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;
};

