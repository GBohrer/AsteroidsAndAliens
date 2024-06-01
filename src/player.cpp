#include "../include/master_header.h"


Player::Player() {}

Player::Player(std::string name){
    SetPosition(GetScreenWidth()/2.0f, GetScreenHeight()/2.0f);
    SetCamera(GetPosition(), GetMousePosition(), 0, 1);
    this->name = name;
    this->score = 0;
    this->isBuffed = false;
}

// GETTERS & SETTERS
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

void Player::MouseMove(){
    this->SetPosition(GetMousePosition().x, GetMousePosition().y);
}

void Player::Draw(){
    DrawRectangle(GetPosition().x, GetPosition().y, 10, 10, YELLOW);
}

