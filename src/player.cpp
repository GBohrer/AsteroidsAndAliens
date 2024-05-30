#include "../include/headers/player.h"

Player::Player() {}

Player::Player(std::string name){
    this->name = name;
    this->score = 0;
    this->isBuffed = false;
    this->pos = Position(100, 100, 5);
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

Position Player::GetPosition(){
    return this->pos;
}

void Player::SetPosition(Position pos){
    this->pos = pos;
}