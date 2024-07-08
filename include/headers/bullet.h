#pragma once
#include "../master_header.h"


class Bullet : public Entity {

    public:
        Bullet();
        Bullet(Vector2 pos, Vector2 dir, float speed, float rate, float damage);

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