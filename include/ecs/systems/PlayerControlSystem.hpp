#pragma once
#include "../../master.hpp"


class PlayerControlSystem : public System {
    public:
    void Init() {}

    void Update(std::shared_ptr<ECSManager> ecs, float dt) {
        for (auto const& player : mEntities) {
        
            auto& acceleration = ecs->GetComponent<Acceleration>(player);
            auto& fuel = ecs->GetComponent<Fuel>(player);
            auto& input = ecs->GetComponent<Input>(player);

            Vector2 thrust = {0.0f, 0.0f};

            if (input.up)    thrust.y -= 1.0f;
            if (input.down)  thrust.y += 1.0f;
            if (input.left)  thrust.x -= 1.0f;
            if (input.right) thrust.x += 1.0f;

            // Normaliza o thrust se houver diagonal
            if (thrust.x != 0 && thrust.y != 0) {
                thrust.x *= 0.7071f; // 1/sqrt(2)
                thrust.y *= 0.7071f;
            }

            acceleration.current.x = acceleration.current.x >= acceleration.max ? acceleration.max : acceleration.current.x + thrust.x * fuel.thrustControlEfficiency;
            acceleration.current.y = acceleration.current.y >= acceleration.max ? acceleration.max : acceleration.current.y + thrust.y * fuel.thrustControlEfficiency;
        }
    }
};