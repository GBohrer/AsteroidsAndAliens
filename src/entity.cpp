#include "../include/master_header.h"

Entity::Entity() {};


// GETTERS & SETTERS
Vector2 Entity::GetPosition() {
    return pos;
}

void Entity::SetPosition(float x, float y) {
    this->pos.x = x;
    this->pos.y = y;
}

EntityVelocity Entity::GetVelocity() {
    return velocity;
}

void Entity::SetVelocity(EntityVelocity v) {
    this->velocity = v;
}

void Entity::SetVelocity(Vector2 velocity, float current_max, float current_min, float max, float min) {
    this->velocity.current = velocity;
    this->velocity.current_max = current_max;
    this->velocity.current_min = current_min;
    this->velocity.max = max;
    this->velocity.min = min;
}
    

void Entity::SetVelocity(Vector2 velocity, float max, float min) {
    this->velocity.current = velocity;
    this->velocity.current_max = max;
    this->velocity.current_min = min;
}

void Entity::SetVelocity(float x, float y) {
    this->velocity.current = {x,y};
}

EntityAcceleration Entity::GetAcceleration() {
    return acceleration;
}

void Entity::SetAcceleration(EntityAcceleration acc) {
    this->acceleration = acc;
}

void Entity::SetAcceleration(Vector2 acceleration, float max, float min) {
    this->acceleration.current = acceleration;
    this->acceleration.max = max;
    this->acceleration.min = min;
}

void Entity::SetAcceleration(float x, float y) {
    this->acceleration.current = {x,y};
}

EntityLife Entity::GetLife() {
    return life;
}

void Entity::SetLife(EntityLife life) {
    this->life = life;
}

void Entity::SetLife(float max, float current, float regen) {
    this->life.max = max;
    this->life.current = current;
    this->life.regen = regen;
}

void Entity::UpdateCurrentLife(float value) {
    this->life.current = value;
}

float Entity::GetSpeed() {
    return speedModifier;
}

void Entity::SetSpeed(float speed) {
    this->speedModifier = speed;
}

Vector2 Entity::GetDirection(){
    return direction;
}

void Entity::SetDirection(Vector2 direction){
    this->direction = direction;
}

bool Entity::GetIsOutOfBounds() {
    return isOutOfBounds;
}

void Entity::SetIsOutOfBounds(bool b) {
    this->isOutOfBounds = b;
}

float Entity::GetIsOutBoundsTime() {
    return isOutOfBoundsTime;
}

void Entity::SetIsOutOfBoundsTime(float value) {
    this->isOutOfBoundsTime = value;
}

bool Entity::CheckIsOutOfBounds(std::vector<Vector2> bounds) {

    Vector2 min = bounds.front();
    Vector2 max = bounds.back();
    Vector2 pos = GetPosition();

    if (pos.x < min.x || pos.y < min.y || pos.x > max.x || pos.y > max.y) {
        return true;
    } else {
        return false;
    }
}