#pragma once
#include "../master_header.h"

#include "character.h"

class Asteroid : public Character {

    public:
        Asteroid();
        Asteroid(Vector2 pos, int radius, float life);

        float GetRadius();
        void SetRadius(float radius);

        void DrawHitBox();
        void DrawDirectionVector();
    
        void Move(Vector2 direction);

    private:
        int radius;

};