#include "../include/master_header.h"


Player::Player() {}

Player::Player(Vector2 pos) {
    SetPosition(pos.x, pos.y);
    SetVelocity({0.0f, 0.0f}, 200.0f, -200.0f, 200.0f, -200.0f);
    SetAcceleration({0.0f, 0.0f}, 2.0f, -2.0f);
    SetSpeed(10.0f);
    SetLife(100.0f, 100.0f, 0.0f);
    SetIsOutOfBounds(false);
    SetAimTarget(pos);
    SetHitBox();
    SetSpaceship();
}

// GETTERS & SETTERS
Rectangle Player::GetHitBox() {
    return hitbox;
}

void Player::SetHitBox() {
    this->hitbox.width = 20.0f;
    this->hitbox.height = 20.0f;
    this->hitbox.x = GetPosition().x - hitbox.width/2.0f;
    this->hitbox.y = GetPosition().y - hitbox.height/2.0f;
}

Vector2 Player::GetAimTarget() {
    return aimTarget;
}

void Player::SetAimTarget(Vector2 target) {
    this->aimTarget = target;
}

Spaceship Player::GetSpaceshipStats() {
    return shipStats;
}

void Player::SetSpaceshipStats(Spaceship s) {
    this->shipStats = s;
}

void Player::UpdateSpaceshipCurrentFuel(float value) {
    this->shipStats.currentFuel = value;
}

void Player::SetSpaceship() {
    Fuel fuel(FuelType::Liquid, 2.0f, 2.0f);
    Spaceship s(fuel, 500.0f, 500.0f, GetVelocity().max);
    SetSpaceshipStats(s);
}

//METHODS
void Player::Move(float delta_t) {

    Vector2 force = GetVelocity().current;
    float min = GetVelocity().current_min;
    float max = GetVelocity().current_max;
    float speed = GetSpeed();
    Spaceship s = GetSpaceshipStats();

    if (IsKeyDown(KEY_W)) { force.y -= speed * s.fuelInfo.thrustControlEfficiency; }
    if (IsKeyDown(KEY_A)) { force.x -= speed * s.fuelInfo.thrustControlEfficiency; }
    if (IsKeyDown(KEY_S)) { force.y += speed * s.fuelInfo.thrustControlEfficiency; }
    if (IsKeyDown(KEY_D)) { force.x += speed * s.fuelInfo.thrustControlEfficiency; }

    if (force.x > max) { force.x = max; }
    else if (force.x < min) { force.x = min; }

    if (force.y > max) { force.y = max; }
    else if (force.y < min) { force.y = min; }

    SetVelocity(force.x + GetAcceleration().current.x * delta_t,
                force.y + GetAcceleration().current.y * delta_t);

    SetPosition(GetPosition().x + GetVelocity().current.x * delta_t,
                GetPosition().y + GetVelocity().current.y * delta_t);

    SetHitBox();
}

void Player::UpdateAim(float delta_t) {

    Vector2 mouseDelta = GetMouseDelta();
    Vector2 dir = GetVelocity().current;
    Vector2 newAimTarget = {GetAimTarget().x + mouseDelta.x + dir.x * delta_t,
                            GetAimTarget().y + mouseDelta.y + dir.y * delta_t};
    
    SetAimTarget(newAimTarget);
}

void Player::UpdateSpaceship() {

    // Fuel
    EntityVelocity v = GetVelocity();
    if (v.current.x != 0.0f || v.current.y != 0.0f) {
        Spaceship s = GetSpaceshipStats();
        float new_current_fuel = s.currentFuel - ((0.0001f * (abs(v.current.x) + abs(v.current.y))) / s.fuelInfo.burningEfficiency);
        //PrintValueInGame(true, s.currentFuel - new_current_fuel, {(int)GetScreenWidth()/2.0f, (int)GetScreenHeight() - 220.0f}, 20, WHITE);
        UpdateSpaceshipCurrentFuel(new_current_fuel);
    }
}

void Player::Update(float delta_t) {

    UpdateSpaceship();
    Move(delta_t);
    UpdateAim(delta_t);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) SetVelocity(0.0f, 0.0f);
}

void Player::DrawHitBox(){
    DrawRectangleLinesEx(GetHitBox(), 2.0f, YELLOW);
}

void Player::DrawAimDirection() {
    Vector2 dir = {GetPosition().x - Vector2Normalize(Vector2Subtract(GetPosition(), GetAimTarget())).x * 100.0f,
                   GetPosition().y - Vector2Normalize(Vector2Subtract(GetPosition(), GetAimTarget())).y * 100.0f};

    DrawLineEx(dir, GetPosition(), 3, GREEN);
}

void Player::DrawAimTarget() {
    DrawCircleV(GetAimTarget(), 15.0f, YELLOW);
}

void Player::DrawHealthBar() {
    DrawRectangle(GetPosition().x - (int)GetLife().max/2.0f, GetPosition().y - GetHitBox().height * 1.2f, (int)GetLife().max, 10, RED);                 
    DrawRectangle(GetPosition().x - (int)GetLife().max/2.0f, GetPosition().y - GetHitBox().height * 1.2f, (int)GetLife().current, 10, GREEN);                 

}

void Player::DrawSpacechipFuelBar() {    
    Spaceship s = GetSpaceshipStats();
    DrawRectangle((int)GetScreenWidth()/2.0f - (int)s.tankMaxCapacity/2.0f, (int)GetScreenHeight() - 200.0f, (int)s.tankMaxCapacity, 20, BLACK);                 
    DrawRectangle((int)GetScreenWidth()/2.0f - (int)s.tankMaxCapacity/2.0f, (int)GetScreenHeight() - 200.0f, (int)s.currentFuel, 20, ORANGE);                 

}

