#include "../include/master_header.h"

Alien::Alien(){}

Alien::Alien(int radius, float speed, float life){
    SetRadius(radius);
    SetVelocity(0.0f, 0.0f);
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
void Alien::SetAlienToPlayer(Player p, int Player_distance){

    float Alien_spawn_angle = GetRandomValue(0, 360) / 57.2957795;
    SetPosition((float) p.GetPosition().x + Player_distance * cos(Alien_spawn_angle),
                (float) p.GetPosition().y + Player_distance * sin(Alien_spawn_angle));
}

void Alien::Move(Player p, float delta) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(p.GetPosition(), GetPosition()));
    SetDirection(dir.x, dir.y);

    SetVelocity(GetVelocity().current.x + GetAcceleration().current.x * delta,
                GetVelocity().current.y + GetAcceleration().current.y * delta);

    SetPosition(GetPosition().x + GetVelocity().current.x * delta + GetDirection().x * GetSpeed(),
                GetPosition().y + GetVelocity().current.y * delta + GetDirection().y * GetSpeed() );
}

void Alien::DrawHitBox(){
    DrawCircleLines(this->GetPosition().x, this->GetPosition().y, GetRadius(), LIGHTGRAY);
}

void Alien::DrawDirectionVector() {
    float mag = 100.0f;
    Vector2 dir = {GetPosition().x + GetDirection().x * mag,
                   GetPosition().y + GetDirection().y * mag};

    DrawLineEx(GetPosition(), dir, 2, GREEN);
}

void Alien::DrawHealthBar () {
    DrawRectangle(GetPosition().x - GetLife().max/2.0f, GetPosition().y - GetRadius() - 20, (int)GetLife().max*2, 10, RED);
    DrawRectangle(GetPosition().x - GetLife().max/2.0f, GetPosition().y - GetRadius() - 20, (int)GetLife().current*2, 10, GREEN);              
}
