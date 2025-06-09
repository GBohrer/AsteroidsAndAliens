#pragma once
#include "../../master.hpp"
#include <cmath>

class PlayerControlSystem : public System {
public:
    void Init() {}

    void Update(std::shared_ptr<ECSManager> ecs, float dt) {
        for (auto const& player : mEntities) {
            auto& playerPos = ecs->GetComponent<Transform>(player).translation;
            auto playerRadius = ecs->GetComponent<Transform>(player).scale.x;
            auto& acceleration = ecs->GetComponent<Acceleration>(player);
            auto& fuel = ecs->GetComponent<Fuel>(player);
            auto& input = ecs->GetComponent<Input>(player);
            auto& playerAim = ecs->GetComponent<Aim>(player);

            Vector2 thrust = {0.0f, 0.0f};

            if (input.up)    thrust.y -= 1.0f;
            if (input.down)  thrust.y += 1.0f;
            if (input.left)  thrust.x -= 1.0f;
            if (input.right) thrust.x += 1.0f;

            // Normaliza para evitar aceleração extra na diagonal
            if (thrust.x != 0 && thrust.y != 0) {
                const float invSqrt2 = 0.7071f;
                thrust.x *= invSqrt2;
                thrust.y *= invSqrt2;
            }
            acceleration.current.x += (thrust.x * fuel.thrustControlEfficiency * 50.0f);
            acceleration.current.y += (thrust.y * fuel.thrustControlEfficiency * 50.0f);

            if(acceleration.current.x > acceleration.max) acceleration.current.x = acceleration.max;
            if(acceleration.current.y > acceleration.max) acceleration.current.y = acceleration.max;

            if(acceleration.current.x < acceleration.min) acceleration.current.x = acceleration.min;
            if(acceleration.current.y < acceleration.min) acceleration.current.y = acceleration.min;

            if (!input.setAim) {
                Vector2 mousePos = GetMousePosition();
                Vector2 aim = Vector2Subtract(mousePos, {playerPos.x, playerPos.y});
                
                float aimSize = Vector2Length(aim);
                aimSize = std::min(aimSize, playerAim.maxAssistSize);
                
                playerAim.direction = Vector2Scale(Vector2Normalize(aim), playerRadius * aimSize);
                playerAim.lockPoint = mousePos;     // revisar isso daqui
                playerAim.lastDirection = playerAim.direction;

            } else {
                Vector2 aim = Vector2Subtract(playerAim.lockPoint, {playerPos.x, playerPos.y});
                float aimSize = Vector2Length(aim);
                aimSize = std::min(aimSize, playerAim.maxAssistSize);
                playerAim.direction = Vector2Scale(Vector2Normalize(aim), playerRadius * aimSize);
            }
        }
    }
};