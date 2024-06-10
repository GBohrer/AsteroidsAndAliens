#pragma once
#include "../master_header.h"

#include "entity.h"

class Character : public Entity {

public:
    Character();

    float GetSpeed();
    void SetSpeed(float speed);
    Vector2 GetDirection();
    void SetDirection(Vector2 direction);

    void CreateBullet(Vector2 pos, float speed, float life);
    void DrawHitBox();
    void Move();

private:
    float speed;
    Vector2 direction;

};