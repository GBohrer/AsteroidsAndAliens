#pragma once

typedef struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    bool shoot;
    bool changeBullet;
    bool setAim;

    Input() : up(false), down(false), left(false), right(false),
              shoot(false), changeBullet(false), setAim(false) {}

} Input;