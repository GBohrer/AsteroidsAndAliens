#include "../include/headers/alien.h"
#include <raylib.h>

Alien::Alien() {}

Alien::Alien(float posX, float posY, int radius, float speed){
    this->pos = (Vector2) {posX, posY};
    this->camera = (Camera2D) { 0 };
    this->radius = radius;
    this->speed = speed;
}

// GETTERS & SETTERS
int Alien::GetRadius(){
    return radius;
}

void Alien::SetRadius(int radius){
    this->radius = radius;
}

float Alien::GetSpeed(){
    return speed;
}

void Alien::SetSpeed(float speed){
    this->speed = speed;
}

Vector2 Alien::GetPosition() {
    return pos;
}

void Alien::SetPosition(float x, float y){
    this->pos.x  = x;
    this->pos.y = y;
}

Camera2D Alien::GetCamera() {
    return camera;
}

void Alien::SetCamera(Vector2 offset, Vector2 target, float rotation, float zoom){
    this->camera.offset = offset;
    this->camera.target = target;
    this->camera.rotation = rotation;
    this->camera.zoom = zoom;
}


// METHODS
void Alien::Draw()
{
    DrawCircle(pos.x, pos.y, GetRadius(), BLACK);
}
