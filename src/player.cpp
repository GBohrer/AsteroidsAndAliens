#include "../include/master_header.h"


Player::Player() {}

Player::Player(std::string name){
    this->pos = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    this->camera = (Camera2D) { 0 };
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

Vector2 Player::GetPosition() {
    return pos;
}

void Player::SetPosition(float x, float y){
    this->pos.x  = x;
    this->pos.y = y;
}

Camera2D Player::GetCamera() {
    return camera;
}

void Player::SetCamera(Vector2 offset, Vector2 target, float rotation, float zoom){
    this->camera.offset = offset;
    this->camera.target = target;
    this->camera.rotation = rotation;
    this->camera.zoom = zoom;
}


//METHODS

void Player::MouseMove(){
    this->pos.x = GetMousePosition().x;
    this->pos.y = GetMousePosition().y;
}

void Player::Draw(){
    DrawRectangle(this->pos.x, this->pos.y, 10, 10, YELLOW);
}

