#pragma once
#include "../master_header.h"


enum FuelType {
    Solid,
    Liquid
};

typedef struct Fuel {
    FuelType type;
    float burningEfficiency;
    float thrustControl;

    Fuel() : type(), burningEfficiency(0.0f), thrustControl(0.0f) {}
    Fuel(FuelType t, float e, float c) : type(t), burningEfficiency(e), thrustControl(c) {}

} Fuel;

typedef struct Spaceship {
    Fuel fuelInfo;
    float tankMaxCapacity;
    float currentFuel;
    float VelocityMax;

    Spaceship() : fuelInfo(), tankMaxCapacity(0.0f), currentFuel(0.0f), VelocityMax(100.0f) {}
    Spaceship(Fuel f, float t, float c, float v) : fuelInfo(f), tankMaxCapacity(t), currentFuel(c), VelocityMax(v) {}

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
        void DrawAim();
        void DrawHealthBar();
        void DrawSpacechipFuelBar();

        void Move(float delta);
        void UpdateAim(float delta);

    private:
        Rectangle hitbox;
        Vector2 aimTarget;
        Spaceship shipStats;
};