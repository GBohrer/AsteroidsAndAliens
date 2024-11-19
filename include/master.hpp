#ifndef MASTER_HEADER_H
#define MASTER_HEADER_H

// COMMON-LIBS
#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <memory>
#include <bitset>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
#include <map>
#include <functional>
#include <cassert>
#include <chrono>

// HEADERS
#include "ecs/core/types.hpp"
#include "ecs/core/ECSManager.hpp"

#include "ecs/components/velocity.hpp"
#include "ecs/components/acceleration.hpp"
#include "ecs/components/vitality.hpp"
#include "ecs/components/input.hpp"
#include "ecs/components/state.hpp"

#include "ecs/systems/MovementSystem.hpp"
#include "ecs/systems/PlayerInputSystem.hpp"

#include "core/interface.hpp"
#include "core/game.hpp"
#include "core/audio.hpp"
#include "core/control.hpp"

#include "utils/savefile.hpp"
#include "utils/functions.hpp"
#include "utils/logger.hpp"



#endif