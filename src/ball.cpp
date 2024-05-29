#include "ball.h"
#include <raylib.h>

Ball::Ball()
{
    x = 100;
    y = 100;
    speedX = 5;
    speedY = 5;
    radius = 15;
}

// GETTERS & SETTERS
int Ball::GetX(){
    return x;
}

int Ball::GetY(){
    return y;
}

void Ball::SetX(int x){
    this->x = x;
}

void Ball::SetY(int y){
    this->y = y;
}

int Ball::GetSpeedX(){
    return speedX;
}

int Ball::GetSpeedY(){
    return speedY;
}

void Ball::SetSpeedX(int speedX){
    this->speedX = speedX;
}

void Ball::SetSpeedY(int speedY){
    this->speedY = speedY;
}

int Ball::GetRadius(){
    return radius;
}

void Ball::SetRadius(int radius){
    this->radius = radius;
}

// METHODS
void Ball::Draw()
{
    DrawCircle(x, y, radius, BLACK);
}

void Ball::DiagonalMove()
{
    //x += speedX;
    //y += speedY;
    SetX(GetX() + GetSpeedX());
    SetY(GetY() + GetSpeedY());

    if (GetX() + GetRadius() >= GetScreenWidth() || GetX() - GetRadius() <= 0)
        //speedX *= -1;
        SetSpeedX(GetSpeedX() * -1);

    if (GetY() + GetRadius() >= GetScreenHeight() || GetY() - GetRadius() <= 0)
        //speedY *= -1;
        SetSpeedY(GetSpeedY() * -1);
}
