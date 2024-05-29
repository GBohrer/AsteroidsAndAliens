#pragma once

class Spaceship
{
public:
    Spaceship();
    void Update();
    void Draw();

private:
    int x;
    int y;
    int speedX;
    int speedY;
    int radius;
};