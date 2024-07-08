#pragma once
#include "../master_header.h"

typedef struct EntityLife {
    float max;
    float current;
    float regen;

} EntityLife;

typedef struct EntityVelocity {
    Vector2 current;
    float max;
    float min;

} EntityVelocity;

typedef struct EntityAcceleration {
    Vector2 current;
    float max;
    float min;

} EntityAcceleration;


class Entity {

public:
    Entity();

    Vector2 GetPosition();
    void SetPosition(float x, float y);

    EntityVelocity GetVelocity();
    void SetVelocity(EntityVelocity v);
    void SetVelocity(Vector2 velocity, float max, float min);
    void SetVelocity(float x, float y);
   
    EntityAcceleration GetAcceleration();
    void SetAcceleration (EntityAcceleration acc);
    void SetAcceleration(Vector2 acceleration, float max, float min);
    void SetAcceleration(float x, float y);
    
    EntityLife GetLife();
    void SetLife(EntityLife life);
    void SetLife(float max, float current, float regen);
    void UpdateCurrentLife(float value);

    float GetSpeed();
    void SetSpeed(float speed);
    Vector2 GetDirection();
    void SetDirection(Vector2 direction);



    float GetMaxLife();
    void SetMaxLife(float lifeMax);
    float GetCurrentLife();
    void SetCurrentLife(float lifeCurrent);

    float GetCurrentSpeed();
    void SetCurrentSpeed(float speedMax);
    float GetMaxSpeed();
    void SetMaxSpeed(float speedCurrent);
 

private:
    Vector2 pos;
    EntityVelocity velocity;
    EntityAcceleration acceleration;
    EntityLife life;
    float speedModifier;
    Vector2 direction;

};