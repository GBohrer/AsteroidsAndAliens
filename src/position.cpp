#include "../include/headers/position.h"

Position::Position(){}

Position::Position (int x, int y, int speed){
    this->x = x;
    this->y = y;
    this->speedX = speed;
    this->speedY = speed;
}

//GETTERS & SETTERS
int Position::GetX(){
    return x;
}

int Position::GetY(){
    return y;
}

void Position::SetX(int x){
    this->x = x;
}

void Position::SetY(int y){
    this->y = y;
}

int Position::GetSpeedX(){
    return speedX;
}

int Position::GetSpeedY(){
    return speedY;
}

void Position::SetSpeedX(int speedX){
    this->speedX = speedX;
}

void Position::SetSpeedY(int speedY){
    this->speedY = speedY;
}