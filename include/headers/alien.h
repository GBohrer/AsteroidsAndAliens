#pragma once
#include <raylib.h>

class Alien
{
public:
    Alien();
    Alien(float posX, float posY, int radius, float speed);

    int GetRadius();
    void SetRadius(int radius);
    float GetSpeed();
    void SetSpeed(float speed);
    
    Vector2 GetPosition();
    void SetPosition(float x, float y);
    Camera2D GetCamera();
    void SetCamera(Vector2 offset, Vector2 lookat, float rotation, float zoom);

    void Draw();


private:
    Vector2 pos;
    Camera2D camera; 
    int radius;
    float speed;
};