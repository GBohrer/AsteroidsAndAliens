#pragma once
#include "../../master.hpp"


// ECS
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 10;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 1;

using Signature = std::bitset<MAX_COMPONENTS>;

class System {
    public:
	std::set<Entity> mEntities;
};
