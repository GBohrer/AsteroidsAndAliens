#include "../include/master_header.h"


Player::Player() {}

Player::Player(std::string name){
    SetPosition((float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f);
    SetHitBox();
    this->name = name;
    this->score = 0;
    this->isBuffed = false;
    SetSpeed(0.01);
    SetDirection({0,0});
}

// GETTERS & SETTERS
Rectangle Player::GetHitBox() {
    return hitbox;
}

void Player::SetHitBox() {
    this->hitbox.x = GetPosition().x;
    this->hitbox.y = GetPosition().y;
    this->hitbox.width = 20.0f;
    this->hitbox.height = 20.0f;
}

std::string Player::GetName(){
    return name;
}

void Player::SetName(std::string name){
    this->name = name;
}

int Player::GetScore(){
    return score;
}

void Player::SetScore(int value){
    this->score = value;
}

bool Player::GetIsBuffed(){
    return isBuffed;
}

void Player::SetIsBuffed(bool value){
    this->isBuffed = value;
}


//METHODS

void Player::Move(){

    SetDirection(Vector2Subtract(GetMousePosition(), this->GetPosition()));

    SetPosition(this->GetPosition().x + this->GetDirection().x * this->GetSpeed(),
                this->GetPosition().y + this->GetDirection().y * this->GetSpeed());
    SetHitBox();
}

void Player::DrawHitBox(){
    DrawRectangleLinesEx(GetHitBox(), 2.0f, YELLOW);
}

