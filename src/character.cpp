#include "../include/master_header.h"


Character::Character(){}


// GETTERS & SETTERS
float Character::GetSpeed() {
    return speed;
}

void Character::SetSpeed(float speed) {
    this->speed = speed;
}

Vector2 Character::GetDirection(){
    return direction;
}

void Character::SetDirection(Vector2 direction){
    this->direction = direction;
}

void Character::CreateBullet(Vector2 pos, float speed, float life) {
    SetPosition(pos.x, pos.y);
    SetDirection(Vector2Subtract(GetMousePosition(), pos));
    SetSpeed(speed);
    SetLife(life);
}

void Character::Move() {
    SetPosition(GetPosition().x + GetDirection().x * GetSpeed(),
                GetPosition().y + GetDirection().y * GetSpeed());
}

void Character::DrawHitBox() {
    DrawRectangleLines(GetPosition().x, GetPosition().y, 2, 10, BLUE);
}