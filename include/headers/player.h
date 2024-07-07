#pragma once
#include "../master_header.h"


class Player : public Entity {

    public:
        Player(); 
        Player(Vector2 pos);

        Rectangle GetHitBox();
        void SetHitBox();
        Vector2 GetAimTarget();
        void SetAimTarget(Vector2 target);

        void DrawHitBox();
        void DrawAim();
        void DrawHealthBar();

        void Move(float delta);
        void UpdateAim(float delta);

    private:
        Rectangle hitbox;
        Vector2 aimTarget;

};