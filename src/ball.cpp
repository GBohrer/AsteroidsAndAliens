#include "../include/headers/ball.h"
#include <raylib.h>

Ball::Ball() {}

Ball::Ball(int radius){
    pos = Position(200, 40, 1);
    this->radius = radius;
}

// GETTERS & SETTERS
int Ball::GetRadius(){
    return radius;
}

void Ball::SetRadius(int radius){
    this->radius = radius;
}

Position Ball::GetPosition(){
    return this->pos;
}

void Ball::SetPosition(Position pos){
    this->pos = pos;
}


// METHODS
void Ball::Draw()
{
    DrawCircle(this->GetPosition().GetX(), this->GetPosition().GetY(), GetRadius(), BLACK);
}

void Ball::DiagonalMove()
{  
    if (pos.GetX() + GetRadius() >= GetScreenWidth() || pos.GetX() - GetRadius() <= 0)
        pos.SetSpeedX(pos.GetSpeedX() * -1);

    if (pos.GetY() + GetRadius() >= GetScreenHeight() || pos.GetY() - GetRadius() <= 0)
        pos.SetSpeedY(pos.GetSpeedY() * -1);

    pos.SetX(pos.GetX() + pos.GetSpeedX());
    pos.SetY(pos.GetY() + pos.GetSpeedY());

}
