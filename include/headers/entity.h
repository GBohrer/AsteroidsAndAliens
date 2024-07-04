#pragma once
#include "../master_header.h"

class Entity {

public:
    Entity();
    Entity(Vector2 pos, Image sprite);

    Vector2 GetPosition();
    void SetPosition(float x, float y);
    float GetMaxLife();
    void SetMaxLife(float lifeMax);
    float GetCurrentLife();
    void SetCurrentLife(float lifeCurrent);
    Image GetImage();
    void SetImage(Image sprite);


private:
    Vector2 pos;
    float lifeMax;
    float lifeCurrent;

    Image sprite;

};