#include "../include/master_header.h"

Asteroid::Asteroid() {}

Asteroid::Asteroid(Vector2 pos, int radius, float life) {
    SetPosition(pos.x, pos.y);
    SetRadius(radius);
    SetLife(life);
}

float Asteroid::GetRadius() {
    return radius;
}

void Asteroid::SetRadius(float radius) {
    this->radius = radius;
}

void Asteroid::DrawHitBox(){
    DrawCircleLines(this->GetPosition().x, this->GetPosition().y, GetRadius(), GRAY);
}

void Asteroid::DrawDirectionVector() {
    Vector2 dir = {GetPosition().x + GetDirection().x * GetSpeed(),
                   GetPosition().y + GetDirection().y * GetSpeed()};

    DrawLineEx(GetPosition(), dir, 2, GREEN);
}
