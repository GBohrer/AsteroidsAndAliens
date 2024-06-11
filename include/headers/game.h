#pragma once
#include "../master_header.h"

#include "bullet.h"

class Game {

    public:
        Game();

        std::vector<Alien> GetCurrentAliens();
        int GetAliensInGame();
        void SetInitialAliens(Player p1);
        void UpdateAlienInGame(Alien alien, int position);

        std::vector<Bullet> GetCurrentBullets();
        int GetBulletsInGame();
        void UpdateBulletInGame(Bullet bullet, int position);
        void SpawnBullets(Player p1);

        void UpdateAnimationTime();
        float GetDeltaT();

    protected:
        int totalAliens;
        int totalBullets;

    private:
        std::vector<Alien> aliensInGame;
        std::vector<Bullet> bulletsInGame;
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
};

