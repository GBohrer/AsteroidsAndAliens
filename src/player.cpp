#include "../include/master_header.h"


Player::Player() {}

Player::Player(Vector2 pos) {
    SetPosition(pos.x, pos.y);
    SetAimTarget(pos);
    SetHitBox();
    this->score = 0;
    this->isBuffed = false;
    SetSpeed(5.0f);
    SetDirection({0,0});
    SetLife(100.0f);
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

    SetPosition(GetPosition().x + GetDirection().x * GetSpeed(),
                GetPosition().y + GetDirection().y * GetSpeed());
    SetHitBox();
}

void Player::UpdateAim () {

    Vector2 mouseDelta = GetMouseDelta();
    Vector2 newAimTarget = {GetAimTarget().x + mouseDelta.x,
                            GetAimTarget().y + mouseDelta.y };

    newAimTarget.x += GetDirection().x * GetSpeed();
    newAimTarget.y += GetDirection().y * GetSpeed();
    
    SetAimTarget(newAimTarget);
}

void Player::DrawHitBox(){
    DrawRectangleLinesEx(GetHitBox(), 2.0f, YELLOW);
}

void Player::DrawAim() {
    DrawLineV(GetPosition(), GetAimTarget(), GREEN);
}

void Player::DrawHeathBar () {
    DrawRectangle(GetPosition().x, GetPosition().y - GetHitBox().height, (int)GetLife(), 10, GREEN);                 
}

