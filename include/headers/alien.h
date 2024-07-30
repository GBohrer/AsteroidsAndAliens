#pragma once
#include "../master_header.h"

#include "player.h"

class Alien : public Entity {

    public:
        Alien();
        Alien(Vector2 pos, int radius, float speed, float life);

        int GetRadius();
        void SetRadius(int radius);
        Vector2 GetDirection();
        void SetDirection(float x, float y);

        void DrawHitBox();
        void DrawDirectionVector();
        void DrawHealthBar();

        void Move(float delta);
        void UpdateDirection(Player p);

    private:
        int radius;
        Vector2 direction;
};