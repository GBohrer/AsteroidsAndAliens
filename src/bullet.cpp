#include "../include/master_header.h"


Bullet::Bullet() {}

Bullet::Bullet(Vector2 pos, float speed, float rate, float damage) {
    SetPosition(pos.x, pos.y);
    SetHitBox();
    SetDirection(Vector2Normalize(Vector2Subtract(pos, GetMousePosition())));
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
    this->hitbox.width = 6;
    this->hitbox.height = 6;
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
void Bullet::Move(float delta) {
    float bullet_desloc = GetSpeed() * delta;
    SetPosition((float)this->GetPosition().x + GetDirection().x * bullet_desloc,
                (float)this->GetPosition().y + GetDirection().y * bullet_desloc);
    SetHitBox();
}

bool Bullet::IsOutOfBounds(Vector2 pos) {
    if ((GetPosition().x < 0 || GetPosition().x > GetScreenWidth()) ||
        (GetPosition().y < 0 || GetPosition().y > GetScreenHeight())) {
        
        return true;
    } else {
        return false;
    }
}