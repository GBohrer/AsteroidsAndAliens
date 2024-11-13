#pragma once
#include "../../master.hpp"


class MovementSystem : public System {
    public:
        void Init();
        void Update(ECSManager ecs, float dt);

};