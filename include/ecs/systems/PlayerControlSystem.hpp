#pragma once
#include "../../master.hpp"
#include <cmath>

class PlayerControlSystem : public System {
public:
    void Init() {}

    void Update(std::shared_ptr<ECSManager> ecs, float dt) {
        for (auto const& player : mEntities) {
            auto& acceleration = ecs->GetComponent<Acceleration>(player);
            auto& fuel = ecs->GetComponent<Fuel>(player);
            auto& input = ecs->GetComponent<Input>(player);
            auto& transform = ecs->GetComponent<Transform>(player);

            const float rotationSpeed = 50.0f; // rad/s
            float currentAngle = 2.0f * std::acos(transform.rotation.w);
            if (transform.rotation.z < 0) currentAngle = -currentAngle;

            if (input.left)  currentAngle -= rotationSpeed * dt;
            if (input.right) currentAngle += rotationSpeed * dt;

            transform.rotation = QuaternionFromAxisAngle({0, 0, 1}, currentAngle);

            Vector2 forward = {
                std::cos(currentAngle),
                std::sin(currentAngle)
            };

            if (input.up) {
                acceleration.current.x += forward.x * fuel.thrustControlEfficiency;
                acceleration.current.y += forward.y * fuel.thrustControlEfficiency;
            }

            if (input.down) {
                acceleration.current.x -= acceleration.current.x * fuel.thrustControlEfficiency;
                acceleration.current.y -= acceleration.current.y * fuel.thrustControlEfficiency;
            }
        }
    }
};