#pragma once
#include <string>
#include <raylib.h>

class Player
{
public:
    Player(); 
    Player(std::string name);
    std::string GetName();
    void SetName(std::string name);
    int GetScore();
    void SetScore(int value);
    bool GetIsBuffed();
    void SetIsBuffed(bool value);

    Vector2 GetPosition();
    void SetPosition(float x, float y);
    Camera2D GetCamera();
    void SetCamera(Vector2 offset, Vector2 lookat, float rotation, float zoom);

    void Draw();
    void MouseMove();

private:
    Vector2 pos;
    Camera2D camera;
    std::string name;
    int score;
    bool isBuffed;


};