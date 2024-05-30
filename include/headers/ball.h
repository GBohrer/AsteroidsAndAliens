#pragma once
#include "position.h"

class Ball
{
public:
    Ball();
    Ball(int radius);

    int GetRadius();
    void SetRadius(int radius);
    Position GetPosition();
    void SetPosition(Position pos);

    void DiagonalMove();
    void Draw();


private:
    Position pos;
    int radius;
};