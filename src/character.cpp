#include "../include/master_header.h"


Character::Character(){}


// GETTERS & SETTERS
float Character::GetMaxSpeed() {
    return speedMax;
}

void Character::SetMaxSpeed(float speedMax) {
    this->speedMax = speedMax;
}

float Character::GetCurrentSpeed() {
    return speedCurrent;
}

void Character::SetCurrentSpeed(float speedCurrent) {
    this->speedCurrent = speedCurrent;
}

Vector2 Character::GetDirection(){
    return direction;
}

void Character::SetDirection(Vector2 direction){
    this->direction = direction;
}
