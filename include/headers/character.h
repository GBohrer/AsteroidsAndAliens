#pragma once
#include "../master_header.h"

#include "entity.h"

class Character : public Entity {

public:
    Character();

    Camera2D GetCamera();
    void SetCamera(Vector2 offset, Vector2 target, float rotation, float zoom);
    float GetSpeed();
    void SetSpeed(float speed);


private:
    Camera2D camera;
    float speed;


};