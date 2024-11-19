#pragma once
#include "../../master.hpp"

#include "../components/velocity.hpp"
#include "../components/acceleration.hpp"
#include "../components/state.hpp"


class MovementSystem : public System {
    public:
        void Init() {}

        void Update(std::shared_ptr<ECSManager> ecs, float dt) {
            for (auto const& entity : mEntities) {

                auto& transform = ecs->GetComponent<Transform>(entity);
                auto& velocity = ecs->GetComponent<Velocity>(entity);
                auto& acceleration = ecs->GetComponent<Acceleration>(entity);
                auto& state = ecs->GetComponent<EState>(entity);

                if(state.ettState == EttState::MOVING) {

                    velocity.current.x += acceleration.current.x * dt;
                    velocity.current.y += acceleration.current.y * dt;
    
                    if (velocity.current.x > velocity.max) { velocity.current.x = velocity.max; 
                    }else if (velocity.current.x < velocity.min) { velocity.current.x = velocity.min; }
    
                    if (velocity.current.y > velocity.max) { velocity.current.y = velocity.max; 
                    }else if (velocity.current.y < velocity.min) { velocity.current.y = velocity.min; }
    
                    transform.translation.x += velocity.current.x * dt;
                    transform.translation.y += velocity.current.y * dt;
                }
            }
        }

};