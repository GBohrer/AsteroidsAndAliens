#include "../include/master_header.h"

Alien::Alien(){}

Alien::Alien(Vector2 pos, int radius, float speed, float life){
    SetPosition(pos.x, pos.y);
    SetRadius(radius);
    SetVelocity({0.0f, 0.0f}, 200.0f, -200.0f, 200.0f, -200.0f);
    SetAcceleration(0.0f, 0.0f);
    SetSpeed(speed);
    SetLife(life,life, 0.0f);
}

// GETTERS & SETTERS
int Alien::GetRadius(){
    return radius;
}

void Alien::SetRadius(int radius){
    this->radius = radius;
}

Vector2 Alien::GetDirection() {
    return direction;
}

void Alien::SetDirection(float x, float y) {
    this->direction = {x,y};
}

// METHODS

void Alien::Move(float delta) {

    auto currentVelocity = GetVelocity().current;
    currentVelocity.x += GetAcceleration().current.x * delta;
    currentVelocity.y += GetAcceleration().current.y * delta;

    SetVelocity(currentVelocity.x, currentVelocity.y);

    SetPosition(GetPosition().x + currentVelocity.x * delta * GetSpeed(),
                GetPosition().y + currentVelocity.y * delta * GetSpeed());
}

void Alien::UpdateDirection(Player p) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(p.GetPosition(), GetPosition()));
    SetVelocity(dir.x, dir.y);
}

void Alien::DrawHitBox(){
    DrawCircleLines(this->GetPosition().x, this->GetPosition().y, GetRadius(), LIGHTGRAY);
}

void Alien::DrawDirectionVector() {
    float mag = 100.0f;
    Vector2 dir = {GetPosition().x + GetVelocity().current.x * mag,
                   GetPosition().y + GetVelocity().current.y * mag};

    DrawLineEx(GetPosition(), dir, 2, GREEN);
}

void Alien::DrawHealthBar () {
    DrawRectangle(GetPosition().x - GetLife().max/2.0f, GetPosition().y - GetRadius() - 20, (int)GetLife().max*2, 10, RED);
    DrawRectangle(GetPosition().x - GetLife().max/2.0f, GetPosition().y - GetRadius() - 20, (int)GetLife().current*2, 10, GREEN);              
}
