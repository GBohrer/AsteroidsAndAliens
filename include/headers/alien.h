#pragma once
#include "../master_header.h"

#include "player.h"
#include "character.h"

class Alien : public Character {

public:
    Alien();
    Alien(int radius, float speed, float life);

    int GetRadius();
    void SetRadius(int radius);

    void DrawHitBox();
    void DrawDirectionVector();
    
    void SetAlienToPlayer(Player player, int Player_distance);
    void Move(Player player, float delta, Vector2 direction);


private:
    int radius;
};