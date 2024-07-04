#pragma once
#include "../master_header.h"

#include "entity.h"

class Character : public Entity {

public:
    Character();

    float GetCurrentSpeed();
    void SetCurrentSpeed(float speedMax);
    float GetMaxSpeed();
    void SetMaxSpeed(float speedCurrent);
    Vector2 GetDirection();
    void SetDirection(Vector2 direction);

private:
    float speedMax;
    float speedCurrent;
    Vector2 direction;

};