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
    DrawCircle(this->GetPosition().x, this->GetPosition().y, GetRadius(), GRAY);
}

void Asteroid::DrawDirectionVector() {
    Vector2 dir = {GetPosition().x + GetDirection().x * GetSpeed(),
                   GetPosition().y + GetDirection().y * GetSpeed()};

    DrawLineEx(GetPosition(), dir, 2, GREEN);
}

void Asteroid::Move(Vector2 direction) {

    SetDirection(direction);
    SetPosition((float)this->GetPosition().x + GetDirection().x,
                (float)this->GetPosition().y + GetDirection().y);

}

bool Asteroid::IsOutOfBounds(Vector2 pos) {
    int max_radius;

    if (GetScreenWidth() > GetScreenHeight()){ max_radius = GetScreenWidth(); }
    else { max_radius = GetScreenHeight(); }

    if (Vector2Distance(GetPosition(), pos) > max_radius) {
        return true;
    } else {
        return false;
    }
}
