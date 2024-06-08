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
void Alien::Draw()
{
    DrawCircle(this->GetPosition().x, this->GetPosition().y, GetRadius(), LIGHTGRAY);
}

void Alien::SetAlienToPlayer(Player player){
    
    float Alien_spawn_angle = GetRandomValue(0, 360);
    SetPosition(player.GetPosition().x + 1000 * cos(Alien_spawn_angle),
                player.GetPosition().y + 1000 * sin(Alien_spawn_angle));
}

void Alien::Move(Player player, float delta) {
    
    //SetDirection(Vector2Subtract(player.GetPosition(), this->GetPosition()));
    Vector2 normal_direction = Vector2Normalize(Vector2Subtract(player.GetPosition(),GetPosition()));
    SetDirection(normal_direction);

    float alien_desloc = this->GetSpeed() * delta;
    SetPosition(this->GetPosition().x + normal_direction.x * alien_desloc,
                this->GetPosition().y + normal_direction.y * alien_desloc);
}