#pragma once

class Position
{
public:
    Position();
    Position(int x, int y, int speed);

    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);

    int GetSpeedX();
    void SetSpeedX(int speedX);
    int GetSpeedY();
    void SetSpeedY(int speedY);

private:
    int x;
    int y;
    int speedX;
    int speedY;
};