#pragma once

enum class EttState {
    IDLE,
    MOVING,
    ATTACKING,
    DEAD
};

struct EState {
    EttState ettState;
};
