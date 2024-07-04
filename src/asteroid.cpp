#include "../include/master_header.h"

Asteroid::Asteroid() {}

Asteroid::Asteroid(Vector2 pos, int radius, float life, float speed) {
    SetPosition(pos.x, pos.y);
    SetRadius(radius);
    SetCurrentSpeed(speed);
    SetMaxSpeed(speed);
    SetMaxLife(life);
    SetCurrentLife(life);
}

float Asteroid::GetRadius() {
    return radius;
}

void Asteroid::SetRadius(float radius) {
    this->radius = radius;
}

void Asteroid::DrawHitBox(){
    DrawCircle(this->GetPosition().x, this->GetPosition().y, GetRadius(), GRAY);
}

void Asteroid::DrawDirectionVector() {
    Vector2 dir = {GetPosition().x + GetDirection().x * GetCurrentSpeed(),
                   GetPosition().y + GetDirection().y * GetCurrentSpeed()};

    DrawLineEx(GetPosition(), dir, 2, GREEN);
}

void Asteroid::Move(Vector2 direction) {

    SetDirection(direction);
    SetPosition((float)this->GetPosition().x + GetDirection().x * GetCurrentSpeed(),
                (float)this->GetPosition().y + GetDirection().y * GetCurrentSpeed());

}

bool Asteroid::IsOutOfBounds(std::vector<Vector2> bounds) {

    Vector2 pos = this->GetPosition();
    Vector2 min = bounds.front();
    Vector2 max = bounds.back();

    return (pos.x < min.x - 1000 || pos.x > max.x + 1000 || pos.y < min.y - 1000 || pos.y > max.y + 1000);
}
