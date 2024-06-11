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
    

private:
    float speed;
    Vector2 direction;

};