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

void Entity::SetVelocity(Vector2 velocity, float max, float min) {
    this->velocity.current = velocity;
    this->velocity.max = max;
    this->velocity.min = min;
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

float Entity::GetMaxSpeed() {
    return speedMax;
}

void Entity::SetMaxSpeed(float speedMax) {
    this->speedMax = speedMax;
}

float Entity::GetCurrentSpeed() {
    return speedCurrent;
}

void Entity::SetCurrentSpeed(float speedCurrent) {
    this->speedCurrent = speedCurrent;
}

Vector2 Entity::GetDirection(){
    return direction;
}

void Entity::SetDirection(Vector2 direction){
    this->direction = direction;
}