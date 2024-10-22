#include "../include/master_header.h"

Asteroid::Asteroid() {}

Asteroid::Asteroid(Vector2 pos, int radius, float life) {
    SetPosition(pos.x, pos.y);
    SetRadius(radius);
    SetLife(life, life, 0.0f);
    SetVelocity(0.0f, 0.0f);
    SetAcceleration(0.0f, 0.0f);
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

void Asteroid::Move(float delta) {

    SetVelocity(GetVelocity().current.x + GetAcceleration().current.x * delta,
                GetVelocity().current.y + GetAcceleration().current.y * delta);

    SetPosition(GetPosition().x + GetVelocity().current.x * delta,
                GetPosition().y + GetVelocity().current.y * delta);

}

bool Asteroid::IsOutOfBounds(std::vector<Vector2> bounds) {

    Vector2 pos = this->GetPosition();
    Vector2 min = bounds.front();
    Vector2 max = bounds.back();

    return (pos.x < min.x - 1000 || pos.x > max.x + 1000 || pos.y < min.y - 1000 || pos.y > max.y + 1000);
}
