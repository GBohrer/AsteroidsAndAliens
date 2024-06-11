#include "../include/master_header.h"


Bullet::Bullet() {}

Bullet::Bullet(Vector2 pos, float speed, float life) {
    SetPosition(pos.x, pos.y);
    SetDirection(Vector2Subtract(GetMousePosition(), pos));
    SetSpeed(speed);
    SetLife(life);
}

Rectangle Bullet::GetHitBox() {
    return hitbox;
}

void Bullet::SetHitBox(float width, float height) {
    this->hitbox.x = GetPosition().x;
    this->hitbox.y = GetPosition().y;
    this->hitbox.width = width;
    this->hitbox.height = height;
}

void Bullet::Move() {
    SetPosition(GetPosition().x + GetDirection().x * GetSpeed(),
                GetPosition().y + GetDirection().y * GetSpeed());
}

void Bullet::DrawHitBox() {
    DrawRectangleLines(GetPosition().x, GetPosition().y, 2, 10, BLUE);
}