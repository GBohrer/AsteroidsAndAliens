#pragma once
#include "../master_header.h"

class Game {

    public:
        Game();

        std::vector<Alien> GetCurrentAliens();
        int GetAliensInGame();
        void SetInitialAliens(Player p1);
        void UpdateAlienInGame(Alien alien, int position);

        std::vector<Character> GetCurrentBullets();
        int GetBulletsInGame();
        void UpdateBulletsInGame(Character bullet, int position);
        void SpawnBullets(Player p1);

        void UpdateAnimationTime();
        float GetDeltaT();

    protected:
        int totalAliens;
        int totalBullets;

    private:
        std::vector<Alien> aliensInGame;
        std::vector<Character> bulletsInGame;
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
};

