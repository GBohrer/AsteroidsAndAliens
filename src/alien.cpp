#include "../include/master_header.h"


Alien::Alien(){
    this->radius = 15;
    SetSpeed(1);
}

// GETTERS & SETTERS
int Alien::GetRadius(){
    return radius;
}

void Alien::SetRadius(int radius){
    this->radius = radius;
}


// METHODS
void Alien::Draw()
{
    DrawCircle(GetPosition().x, GetPosition().y, GetRadius(), BLACK);
}

void Alien::SetAlienToPlayer(Player player){
    // POSITION
    float Alien_spawn_angle = GetRandomValue(0, 360);

    SetPosition(player.GetPosition().x + 100 * cos(Alien_spawn_angle),
                player.GetPosition().y + 100 * sin(Alien_spawn_angle));
    
    // CAMERA
    SetCamera(this->GetPosition(), player.GetPosition(), 0, 1);
}