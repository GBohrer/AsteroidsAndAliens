#pragma once
#include "../../master.hpp"


// ECS
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 200;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 10;

using Signature = std::bitset<MAX_COMPONENTS>;

class ECSManager;
class System {
    public:
	    std::set<Entity> mEntities;
        virtual void Update(std::shared_ptr<ECSManager> ecs, float dt) = 0;
};
