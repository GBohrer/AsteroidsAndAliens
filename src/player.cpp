#include "../include/master_header.h"


Player::Player() {}

Player::Player(std::string nickname){
    SetPosition((float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f);
    SetHitBox();
    this->nickname = nickname;
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

std::string Player::GetName(){
    return nickname;
}

void Player::SetName(std::string nickname){
    this->nickname = nickname;
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

void Player::Move(Vector2 direction){

    SetDirection(direction);

    SetPosition(this->GetPosition().x + this->GetDirection().x * this->GetSpeed(),
                this->GetPosition().y + this->GetDirection().y * this->GetSpeed());
    SetHitBox();

}

void Player::DrawHitBox(){
    DrawRectangleLinesEx(GetHitBox(), 2.0f, YELLOW);
}

void Player::DrawAimDirection() {
    //Vector2 dir = {GetPosition().x + GetDirection().x * -150,
    //               GetPosition().y + GetDirection().y * -150};

    DrawLineV(GetMousePosition(), GetPosition(), GREEN);
}

void Player::DrawHeathBar () {
    DrawRectangle(GetPosition().x, GetPosition().y - GetHitBox().height, (int)GetLife(), 10, GREEN);                 
}

