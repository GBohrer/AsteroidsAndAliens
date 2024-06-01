#pragma once
#include "../master_header.h"


class Entity {

public:
    Entity();
    Entity(Vector2 pos, float life, Image sprite);

    Vector2 GetPosition();
    void SetPosition(int x, int y);
    float GetLife();
    void SetLife(float life);
    Image GetImage();
    void SetImage(Image sprite);


private:
    Vector2 pos;
    float life;
    Image sprite;

};