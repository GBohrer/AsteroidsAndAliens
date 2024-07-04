#include "../include/master_header.h"


Player::Player() {}

Player::Player(Vector2 pos) {
    SetPosition(pos.x, pos.y);
    SetAimTarget(pos);
    SetHitBox();
    this->score = 0;
    this->isBuffed = false;
    SetMaxSpeed(5.0f);
    SetCurrentSpeed(GetMaxSpeed());
    SetDirection({0,0});
    SetMaxLife(100.0f);
    SetCurrentLife(GetMaxLife());
}

// GETTERS & SETTERS
Rectangle Player::GetHitBox() {
    return hitbox;
}

void Player::SetHitBox() {
    this->hitbox.width = 20.0f;
    this->hitbox.height = 20.0f;
    this->hitbox.x = GetPosition().x - hitbox.width/2.0f;
    this->hitbox.y = GetPosition().y - hitbox.height/2.0f;
}

int Player::GetScore() {
    return score;
}

void Player::SetScore(int value) {
    this->score = value;
}

bool Player::GetIsBuffed() {
    return isBuffed;
}

void Player::SetIsBuffed(bool value) {
    this->isBuffed = value;
}

Vector2 Player::GetAimTarget() {
    return aimTarget;
}

void Player::SetAimTarget(Vector2 target) {
    this->aimTarget = target;
}

//METHODS

void Player::Move(Vector2 direction) {

    SetDirection(direction);

    SetPosition(GetPosition().x + GetDirection().x * GetCurrentSpeed(),
                GetPosition().y + GetDirection().y * GetCurrentSpeed());
    SetHitBox();
}

void Player::UpdateAim () {

    Vector2 mouseDelta = GetMouseDelta();
    Vector2 newAimTarget = {GetAimTarget().x + mouseDelta.x,
                            GetAimTarget().y + mouseDelta.y };

    newAimTarget.x += GetDirection().x * GetCurrentSpeed();
    newAimTarget.y += GetDirection().y * GetCurrentSpeed();
    
    SetAimTarget(newAimTarget);
}

void Player::DrawHitBox(){
    DrawRectangleLinesEx(GetHitBox(), 2.0f, YELLOW);
}

void Player::DrawAim() {
    float mag = GetCurrentSpeed() * 20.0f;
    Vector2 dir = {GetPosition().x - Vector2Normalize(Vector2Subtract(GetPosition(), GetAimTarget())).x * mag,
                   GetPosition().y - Vector2Normalize(Vector2Subtract(GetPosition(), GetAimTarget())).y * mag};

    DrawLineEx(dir, GetPosition(), 3, GREEN);
}

void Player::DrawHealthBar () {
    DrawRectangle(GetPosition().x, GetPosition().y - GetHitBox().height, (int)GetMaxLife(), 10, RED);                 
    DrawRectangle(GetPosition().x, GetPosition().y - GetHitBox().height, (int)GetCurrentLife(), 10, GREEN);                 

}

