#include "../include/master_header.h"


Bullet::Bullet() {}

Bullet::Bullet(Vector2 pos, Vector2 dir, float speed, float rate, float damage) {
    SetPosition(pos.x, pos.y);
    SetHitBox();
    SetDirection(dir);
    SetVelocity({0.0f, 0.0f}, 200.0f, -200.0f, 200.0f, -200.0f);
    SetAcceleration(0.0f, 0.0f);
    SetSpeed(speed);
    SetFireRate(rate);
    SetDamage(damage);
    SetIsOutOfBounds(false);
}

// GETTERS & SETTERS
Rectangle Bullet::GetHitBox() {
    return hitbox;
}

void Bullet::SetHitBox() {
    this->hitbox.x = GetPosition().x;
    this->hitbox.y = GetPosition().y;
    this->hitbox.width = 12;
    this->hitbox.height = 12;
}

void Bullet::DrawHitBox() {
    DrawRectangleRoundedLines(GetHitBox(), 1.0f, 4, 1.0f, BLUE);
}

float Bullet::GetFireRate() {
    return fireRate;
}

void Bullet::SetFireRate(float value) {
    this->fireRate = value;
}

float Bullet::GetDamage() {
    return damage;
}

void Bullet::SetDamage(float value) {
    this->damage = value;
}


// METHODS
void Bullet::Move(float delta) {

    SetVelocity(GetVelocity().current.x + GetAcceleration().current.x * delta,
                GetVelocity().current.y + GetAcceleration().current.y * delta);

    SetPosition(GetPosition().x + GetVelocity().current.x * delta + GetDirection().x * GetSpeed(),
                GetPosition().y + GetVelocity().current.y * delta + GetDirection().y * GetSpeed() );



    //float bullet_speed = GetCurrentSpeed();
   // SetPosition(this->GetPosition().x + GetDirection().x * bullet_speed,
    //            this->GetPosition().y + GetDirection().y * bullet_speed);
    SetHitBox();
}

bool Bullet::IsOutOfBounds(Vector2 pos) {

    int max_radius;
    if (GetScreenWidth() > GetScreenHeight()){ max_radius = GetScreenWidth(); }
    else { max_radius = GetScreenHeight(); }

    if (Vector2Distance(GetPosition(), pos) > max_radius) {
        return true;
    } else {
        return false;
    }
}