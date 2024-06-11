#pragma once
#include "../master_header.h"

#include "character.h"


class Bullet : public Character {

    public:
        Bullet();
        Bullet(Vector2 pos, float speed, float rate, float damage);

        Rectangle GetHitBox();
        void SetHitBox();
        void DrawHitBox();
        float GetFireRate();
        void SetFireRate(float value);
        float GetDamage();
        void SetDamage(float value);

        void Move(float delta);
        bool IsOutOfBounds(Vector2 pos);

    private:
        Rectangle hitbox;
        float fireRate;
        float damage;

};