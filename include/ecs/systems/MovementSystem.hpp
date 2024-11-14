#pragma once
#include "../../master.hpp"

#include "../components/velocity.hpp"
#include "../components/acceleration.hpp"


class MovementSystem : public System {
    public:
        void Init() {}

        void Update(std::shared_ptr<ECSManager> ecs, float dt) {
            for (auto const& entity : mEntities) {

                auto& transform = ecs->GetComponent<Transform>(entity);
                auto& velocity = ecs->GetComponent<Velocity>(entity);
                auto& acceleration = ecs->GetComponent<Acceleration>(entity);

            }
        }

};