#pragma once
#include "../master_header.h"

#include "character.h"

class Player : public Character {

public:
    Player(); 
    Player(std::string nickname);
    
    std::string GetName();
    void SetName(std::string nickname);
    int GetScore();
    void SetScore(int value);
    bool GetIsBuffed();
    void SetIsBuffed(bool value);

    Rectangle GetHitBox();
    void SetHitBox();
    void DrawHitBox();
    void DrawAimDirection();

    void Move(Vector2 direction);

private:
    Rectangle hitbox;
    std::string nickname;
    int score;
    bool isBuffed;


};