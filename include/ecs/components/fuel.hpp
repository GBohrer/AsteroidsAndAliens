#pragma once

enum FuelType {
    Solid,
    Liquid,
    Plasma
};

struct Fuel {
    FuelType type;
    float burningEfficiency;
    float thrustControlEfficiency;
};

const Fuel fuel1 = Fuel{.type = FuelType::Solid,
                        .burningEfficiency = 0.5f,
                        .thrustControlEfficiency = 0.5f};

const Fuel fuel2 = Fuel{.type = FuelType::Liquid,
                        .burningEfficiency = 1.0f,
                        .thrustControlEfficiency = 1.0f};

const Fuel fuel3 = Fuel{.type = FuelType::Plasma,
                        .burningEfficiency = 2.5f,
                        .thrustControlEfficiency = 2.5f};