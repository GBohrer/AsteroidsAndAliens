#pragma once
#include "../master_header.h"

#include "alien.h"
#include "player.h"

class Game {

    public:
        Game();

        std::vector<Alien> GetCurrentAliens();
        int GetAliensInGame();
        void SetInitialAliens(Player p1);
        void UpdateAliensInGame(Alien alien, int position);
        void UpdateAnimationTime();
        float GetDeltaT();

    protected:
        int totalAliens;

    private:
        std::vector<Alien> aliensInGame;
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
};

