#pragma once
#include "../master_header.h"

class Game {

    public:
        Game();

        std::vector<Alien> GetCurrentAliens();
        int GetAliensInGame();
        void SetInitialAliens(Player p1);
        void UpdateAlienInGame(Alien alien, int position);
        void UpdateAnimationTime();
        float GetDeltaT();

        bool CheckCollision (Entity obj1, Entity obj2);

    protected:
        int totalAliens;

    private:
        std::vector<Alien> aliensInGame;
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
};

