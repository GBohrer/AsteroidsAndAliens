#pragma once
#include "../../master.hpp"


class PlayerControlSystem : public System {
    public:
    void Init() {}

    void Update(std::shared_ptr<ECSManager> ecs, float dt) {

        for (auto const& player : mEntities) {
        
            auto& velocity = ecs->GetComponent<Velocity>(player);
            auto& acceleration = ecs->GetComponent<Acceleration>(player);
            auto& fuel = ecs->GetComponent<Fuel>(player);
            auto& input = ecs->GetComponent<Input>(player);

            if (input.up)   { velocity.current.y -= acceleration.current.y * fuel.thrustControlEfficiency; }
            if (input.left) { velocity.current.x -= acceleration.current.x * fuel.thrustControlEfficiency; }
            if (input.down) { velocity.current.y += acceleration.current.y * fuel.thrustControlEfficiency; }
            if (input.right){ velocity.current.x += acceleration.current.x * fuel.thrustControlEfficiency; }

        }
    
    }
};