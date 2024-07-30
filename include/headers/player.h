#pragma once
#include "../master_header.h"


enum FuelType {
    Solid,
    Liquid
};

typedef struct Fuel {
    FuelType type;
    float burningEfficiency;
    float thrustControlEfficiency;

    Fuel() : type(), burningEfficiency(0.0f), thrustControlEfficiency(0.0f) {}
    Fuel(FuelType t, float e, float c) : type(t), burningEfficiency(e), thrustControlEfficiency(c) {}

} Fuel;

typedef struct Spaceship {
    Fuel fuelInfo;
    float tankMaxCapacity;
    double currentFuel;
    float VelocityMax;

    Spaceship() : fuelInfo(), tankMaxCapacity(0.0f), currentFuel(0.0f), VelocityMax(100.0f) {}
    Spaceship(Fuel f, float t, double c, float v) : fuelInfo(f), tankMaxCapacity(t), currentFuel(c), VelocityMax(v) {}

} Spaceship;


class Player : public Entity {

    public:
        Player(); 
        Player(Vector2 pos);
        void SetSpaceship();

        Rectangle GetHitBox();
        void SetHitBox();
        Vector2 GetAimTarget();
        void SetAimTarget(Vector2 target);
        Spaceship GetSpaceshipStats();
        void SetSpaceshipStats(Spaceship s);
        void UpdateSpaceshipCurrentFuel(float value);

        void DrawHitBox();
        void DrawAimDirection();
        void DrawAimTarget();
        void DrawHealthBar();
        void DrawSpacechipFuelBar();

        void Move(float delta_t);
        void UpdateAim(float delta_t);
        void UpdateSpaceship();
        void Update(float delta_t);

    private:
        Rectangle hitbox;
        Vector2 aimTarget;
        Spaceship shipStats;
};