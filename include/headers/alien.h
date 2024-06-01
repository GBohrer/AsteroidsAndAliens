#pragma once
#include "../master_header.h"

#include "player.h"
#include "character.h"

class Alien : public Character {

public:
    Alien();

    int GetRadius();
    void SetRadius(int radius);

    void Draw();
    void SetAlienToPlayer(Player player);


private:
    int radius;
};