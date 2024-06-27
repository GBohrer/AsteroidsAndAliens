#pragma once
#include "../master_header.h"

#include "bullet.h"
#include "asteroid.h"

enum GameState {
    Menu,
    InGame,
    GameOver,
    Paused
};

class Game {

    public:
        Game();

        void Start();
        void Reset();
        void UpdateAnimationTime();
        float GetDeltaT();
        bool CheckDifficultyIncrease(int score);
        void IncreaseDifficulty();
        GameState GetGameState();
        void SetGameState(GameState state);

        std::vector<Vector2>& GetCurrentLevelBounds();
        void SetCurrenLevelBounds(std::vector<Vector2> level_bounds);

        //ASTEROIDS
        std::vector<Asteroid>& GetCurrentAsteroids();
        int GetAsteroidsInGame();
        void SpawnAsteroids();
        void UpdateAsteroidInGame(Asteroid ast, int position);
        void DeleteAsteroidInGame(int position);

        bool CollisionAsteroidAsteroid(Asteroid ast1, Asteroid ast2);
        bool CollisionAsteroidAlien(Asteroid ast, Alien a);
        bool CollisionAsteroidBullet(Asteroid ast, Bullet b);
        bool CollisionAsteroidPlayer(Asteroid ast, Player p);
        void CheckAsteroidCollisions();

        //ALIENS
        std::vector<Alien>& GetCurrentAliens();
        int GetAliensInGame();
        void SpawnAliens();
        void UpdateAlienInGame(Alien alien, int position);
        void DeleteAlienInGame(int position);

        bool CollisionAlienAlien(Alien a1, Alien a2);
        bool CollisionAlienPlayer(Alien a);
        void CheckAlienCollisions();

        //BULLETS
        std::vector<Bullet>& GetCurrentBullets();
        int GetBulletsInGame();
        void SpawnBullets();
        void UpdateBulletInGame(Bullet bullet, int position);
        void DeleteBulletInGame(int position);

        bool CollisionBulletAlien(Bullet b, Alien a);
        bool CollisionBulletPlayer(Bullet b);
        void CheckBulletCollisions();

        //PLAYER
        Player& GetPlayer();
        void SetPlayer(Player p);
        void UpdatePlayer();
        void UpdatePlayerScore();
        bool IsPlayerOutOfBounds();

        //CAMERA
        Camera2D& GetCamera();
        void SetCamera();
        void SetCameraZoom(float zoom);
        void UpdateCamera(int screenWidth, int screenHeight);

        void CheckEntityCollisions();

    protected:
        int totalAliens;
        int totalAsteroids;
        float AlienSpawnTimer;
        float BulletSpawnTimer;
        int scoreThreshold;
        bool isPlayerOutOfBounds;
        float PlayerOutOfBoundsTimer;


    private:
        GameState state;
        std::vector<Vector2> currentLevelBounds;
        std::vector<Asteroid> asteroidsInGame;
        std::vector<Alien> aliensInGame;
        std::vector<Bullet> bulletsInGame;
        Player player;
        Camera2D camera;
        
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;
};

