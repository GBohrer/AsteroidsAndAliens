#include "../include/master_header.h"

Alien::Alien(){}

Alien::Alien(int radius, float speed){
    this->radius = radius;
    SetSpeed(speed);
}

// GETTERS & SETTERS
int Alien::GetRadius(){
    return radius;
}

void Alien::SetRadius(int radius){
    this->radius = radius;
}


// METHODS
void Alien::DrawHitBox()
{
    DrawCircleLines(this->GetPosition().x, this->GetPosition().y, GetRadius(), LIGHTGRAY);
}

void Alien::SetAlienToPlayer(Player player, int Player_distance){
    
    float Alien_spawn_angle = GetRandomValue(0, 360);
    SetPosition((float)player.GetPosition().x + (Player_distance) * cos(Alien_spawn_angle),
                (float)player.GetPosition().y + Player_distance * sin(Alien_spawn_angle));

    SetDirection(Vector2Normalize(Vector2Subtract(player.GetPosition(),this->GetPosition())));
}

void Alien::Move(Player player, float delta, Vector2 direction) {

    float alien_desloc = GetSpeed();
    SetPosition(this->GetPosition().x + direction.x * alien_desloc,
                this->GetPosition().y + direction.y * alien_desloc);

    SetDirection(Vector2Normalize(Vector2Subtract(player.GetPosition(),this->GetPosition())));
}