#pragma once
#include "../master_header.h"

#include "character.h"

class Player : public Character {

public:
    Player(); 
    Player(std::string name);
    
    Vector2 GetHitBox();
    void SetHitBox(float width, float height);
    std::string GetName();
    void SetName(std::string name);
    int GetScore();
    void SetScore(int value);
    bool GetIsBuffed();
    void SetIsBuffed(bool value);

    void DrawHitBox();
    void Move();

private:
    Vector2 hitbox;
    std::string name;
    int score;
    bool isBuffed;


};