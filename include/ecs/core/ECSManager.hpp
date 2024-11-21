#pragma once

#include "entityManager.hpp"
#include "componentManager.hpp"
#include "systemManager.hpp"

class ECSManager {
    public:
	    void Init() {
	    	mComponentManager = std::make_unique<ComponentManager>();
	    	mEntityManager = std::make_unique<EntityManager>();
	    	mSystemManager = std::make_unique<SystemManager>();
	    }


	    // Entity methods
	    Entity CreateEntity() {
	    	return mEntityManager->CreateEntity();
	    }

	    void DestroyEntity(Entity entity) {
	    	mEntityManager->DestroyEntity(entity);

	    	mComponentManager->EntityDestroyed(entity);

	    	mSystemManager->EntityDestroyed(entity);
	    }

		bool CheckSignature(Entity entity) {
			return mEntityManager->GetSignature(entity).any() ? true : false;
		}

		void DestroyAllEntities() {

			for (Entity ett = 0; ett < MAX_ENTITIES; ett++) {
				if (CheckSignature(ett))
					DestroyEntity(ett);
			}
		}

	    // Component methods
	    template<typename T>
	    void RegisterComponent() {
	    	mComponentManager->RegisterComponent<T>();
	    }

	    template<typename T>
	    void AddComponent(Entity entity, T component) {
	    	mComponentManager->AddComponent<T>(entity, component);

	    	auto signature = mEntityManager->GetSignature(entity);
	    	signature.set(mComponentManager->GetComponentType<T>(), true);
	    	mEntityManager->SetSignature(entity, signature);

	    	mSystemManager->EntitySignatureChanged(entity, signature);
	    }

	    template<typename T>
	    void RemoveComponent(Entity entity) {
	    	mComponentManager->RemoveComponent<T>(entity);

	    	auto signature = mEntityManager->GetSignature(entity);
	    	signature.set(mComponentManager->GetComponentType<T>(), false);
	    	mEntityManager->SetSignature(entity, signature);

	    	mSystemManager->EntitySignatureChanged(entity, signature);
	    }

	    template<typename T>
	    T& GetComponent(Entity entity) {
	    	return mComponentManager->GetComponent<T>(entity);
	    }

	    template<typename T>
	    ComponentType GetComponentType() {
	    	return mComponentManager->GetComponentType<T>();
	    }

	    template<typename T>
		bool HasComponent(Entity entity) {
			//assert(entity < MAX_ENTITIES && "Entity out of range.");

			auto componentType = GetComponentType<T>();
			auto signature = mEntityManager->GetSignature(entity);
			return signature.test(componentType);
		}


	    // System methods
	    template<typename T>
	    std::shared_ptr<T> RegisterSystem() {
	    	return mSystemManager->RegisterSystem<T>();
	    }

	    template<typename T>
	    void SetSystemSignature(Signature signature) {
	    	mSystemManager->SetSignature<T>(signature);
	    }

		std::vector<std::shared_ptr<System>> GetSystems() {
			return mSystemManager->GetSystems();
		}

    private:
	    std::unique_ptr<ComponentManager> mComponentManager;
	    std::unique_ptr<EntityManager> mEntityManager;
	    std::unique_ptr<SystemManager> mSystemManager;
};