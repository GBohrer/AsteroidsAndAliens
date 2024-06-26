#pragma once
#include "../master_header.h"

#include "character.h"

class Player : public Character {

public:
    Player(); 
    Player(Vector2 pos);
    
    Rectangle GetHitBox();
    void SetHitBox();
    int GetScore();
    void SetScore(int value);
    bool GetIsBuffed();
    void SetIsBuffed(bool value);
    Vector2 GetAimTarget();
    void SetAimTarget(Vector2 target);

    void DrawHitBox();
    void DrawAim();
    void DrawHeathBar();

    void Move(Vector2 direction);
    void UpdateAim();

private:
    Rectangle hitbox;
    int score;
    bool isBuffed;
    Vector2 aimTarget;

};