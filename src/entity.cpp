#include "../include/master_header.h"

Entity::Entity() {};

Entity::Entity(Vector2 pos, Image sprite) {
    SetPosition(pos.x, pos.y);
    SetImage(sprite);
}

// GETTERS & SETTERS
Vector2 Entity::GetPosition() {
    return pos;
}

void Entity::SetPosition(float x, float y) {
    this->pos.x = x;
    this->pos.y = y;
}

float Entity::GetMaxLife() {
    return lifeMax;
}

void Entity::SetMaxLife(float lifeMax) {
    this->lifeMax = lifeMax;
}

float Entity::GetCurrentLife() {
    return lifeCurrent;
}

void Entity::SetCurrentLife(float lifeCurrent) {
    this->lifeCurrent = lifeCurrent;
}

Image Entity::GetImage() {
    return sprite;
}

void Entity::SetImage(Image sprite) {
    this->sprite = sprite;
}