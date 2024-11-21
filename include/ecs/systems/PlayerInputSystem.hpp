#pragma once
#include "../../master.hpp"


class PlayerInputSystem : public System {
    public:
    void Init() {}

    void Update(std::shared_ptr<ECSManager> ecs, float dt) {

        for (auto const& player : mEntities) {

            auto& p_state = ecs->GetComponent<EState>(player);
            if (p_state.ettState == EttState::DEAD)
                continue;

            auto& input = ecs->GetComponent<Input>(player);

            input.up = IsKeyDown(KEY_W);
            input.down = IsKeyDown(KEY_S);
            input.left = IsKeyDown(KEY_A);
            input.right = IsKeyDown(KEY_D);

            input.shoot = IsKeyPressed(KEY_SPACE); 
            input.changeBullet = IsKeyPressed(KEY_LEFT_SHIFT);
            input.setAim = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        }
    }
};