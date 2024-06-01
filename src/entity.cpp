#include "../include/master_header.h"

Entity::Entity() {};

Entity::Entity(Vector2 pos, float life, Image sprite) {
    SetPosition(pos.x, pos.y);
    SetLife(life);
    SetImage(sprite);
}

// GETTERS & SETTERS
Vector2 Entity::GetPosition() {
    return pos;
}

void Entity::SetPosition(int x, int y) {
    this->pos.x = x;
    this->pos.y = y;
}

float Entity::GetLife() {
    return life;
}

void Entity::SetLife(float life) {
    this->life = life;
}

Image Entity::GetImage() {
    return sprite;
}

void Entity::SetImage(Image sprite) {
    this->sprite = sprite;
}