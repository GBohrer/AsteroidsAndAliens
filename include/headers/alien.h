#pragma once
#include "../master_header.h"

#include "player.h"

class Alien : public Entity {

    public:
        Alien();
        Alien(int radius, float speed, float life);

        int GetRadius();
        void SetRadius(int radius);
        Vector2 GetDirection();
        void SetDirection(float x, float y);

        void DrawHitBox();
        void DrawDirectionVector();
        void DrawHealthBar();

        void SetAlienToPlayer(Player p, int Player_distance);
        void Move(Player p, float delta);


    private:
        int radius;
        Vector2 direction;
};