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
