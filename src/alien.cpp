#include "../include/master_header.h"

Alien::Alien(){}

Alien::Alien(int radius, float speed, float life){
    SetRadius(radius);
    SetCurrentSpeed(speed);
    SetMaxSpeed(speed);
    SetMaxLife(life);
    SetCurrentLife(life);
}

// GETTERS & SETTERS
int Alien::GetRadius(){
    return radius;
}

void Alien::SetRadius(int radius){
    this->radius = radius;
}


// METHODS
void Alien::SetAlienToPlayer(Player player, int Player_distance){

    float Alien_spawn_angle = GetRandomValue(0, 360) / 57.2957795;
    SetPosition((float) player.GetPosition().x + Player_distance * cos(Alien_spawn_angle),
                (float) player.GetPosition().y + Player_distance * sin(Alien_spawn_angle));

    SetDirection(Vector2Normalize(Vector2Subtract(player.GetPosition(),this->GetPosition())));
}

void Alien::Move(Player player, float delta, Vector2 direction) {

    float alien_desloc = GetCurrentSpeed();
    SetPosition((float)this->GetPosition().x + direction.x * alien_desloc,
                (float)this->GetPosition().y + direction.y * alien_desloc);

    SetDirection(Vector2Normalize(Vector2Subtract(player.GetPosition(),this->GetPosition())));
}

void Alien::DrawHitBox(){
    DrawCircleLines(this->GetPosition().x, this->GetPosition().y, GetRadius(), LIGHTGRAY);
}

void Alien::DrawDirectionVector() {
    float mag = GetCurrentSpeed() * 100.0f;
    Vector2 dir = {GetPosition().x + GetDirection().x * mag,
                   GetPosition().y + GetDirection().y * mag};

    DrawLineEx(GetPosition(), dir, 2, GREEN);
}

void Alien::DrawHealthBar () {
    DrawRectangle(GetPosition().x - GetMaxLife()/2.0f, GetPosition().y - GetRadius() - 20, (int)GetMaxLife()*2, 10, RED);
    DrawRectangle(GetPosition().x - GetMaxLife()/2.0f, GetPosition().y - GetRadius() - 20, (int)GetCurrentLife()*2, 10, GREEN);
                    
}
