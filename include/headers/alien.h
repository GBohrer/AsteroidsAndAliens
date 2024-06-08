#pragma once
#include "../master_header.h"

#include "player.h"
#include "character.h"

class Alien : public Character {

public:
    Alien();
    Alien(int radius, float speed);

    int GetRadius();
    void SetRadius(int radius);

    void Draw();
    void SetAlienToPlayer(Player player);
    void Move(Player player, float delta);


private:
    int radius;
};