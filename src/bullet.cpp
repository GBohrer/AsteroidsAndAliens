#include "../include/master_header.h"


Bullet::Bullet() {}

Bullet::Bullet(Player p, float speed, float rate, float damage) {
    SetPosition(p.GetPosition().x, p.GetPosition().y);
    SetHitBox();
    SetDirection(Vector2Normalize(Vector2Subtract(p.GetAimTarget(), p.GetPosition() )));
    SetSpeed(speed);
    SetFireRate(rate);
    SetDamage(damage);
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
    DrawRectangleLinesEx(GetHitBox(), 2.0f, BLUE);
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
void Bullet::Move() {
    float bullet_speed = GetSpeed();
    SetPosition(this->GetPosition().x + GetDirection().x * bullet_speed,
                this->GetPosition().y + GetDirection().y * bullet_speed);
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