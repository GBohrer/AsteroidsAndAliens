#include "../include/master_header.h"

Character::Character() {}

// GETTERS & SETTERS
Camera2D Character::GetCamera() {
    return camera;
}

void Character::SetCamera(Vector2 offset, Vector2 target, float rotation, float zoom){
    this->camera.offset = offset;
    this->camera.target = target;
    this->camera.rotation = rotation;
    this->camera.zoom = zoom;
}

float Character::GetSpeed() {
    return speed;
}

void Character::SetSpeed(float speed) {
    this->speed = speed;
}