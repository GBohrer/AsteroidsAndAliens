#pragma once
#include "../master_header.h"

#include "character.h"


class Bullet : public Character {

    public:
        Bullet();
        Bullet(Vector2 pos, float speed, float life);

        Rectangle GetHitBox();
        void SetHitBox(float width, float height);

        void DrawHitBox();
        void Move();

    private:
        Rectangle hitbox;

};