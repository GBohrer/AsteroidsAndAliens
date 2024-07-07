#pragma once
#include "../master_header.h"


class Asteroid : public Entity {

    public:
        Asteroid();
        Asteroid(Vector2 pos, int radius, float life);

        float GetRadius();
        void SetRadius(float radius);

        void DrawHitBox();
    
        void Move(float delta);
        bool IsOutOfBounds(std::vector<Vector2> bounds);

    private:
        int radius;

};