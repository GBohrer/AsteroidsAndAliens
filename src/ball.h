#pragma once

class Ball
{
public:
    Ball();

    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);

    int GetSpeedX();
    void SetSpeedX(int speedX);
    int GetSpeedY();
    void SetSpeedY(int speedY);

    int GetRadius();
    void SetRadius(int radius);

    void DiagonalMove();
    void Draw();


private:
    int x;
    int y;
    int speedX;
    int speedY;
    int radius;
};