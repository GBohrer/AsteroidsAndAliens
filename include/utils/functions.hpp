#pragma once
#include "../master.hpp"


// GAME

std::unordered_map<State, GameState> GameStateInit();
GameInfo GameInfoInit();
GameTimer GameTimerInit();
std::unique_ptr<ECSManager> GameECSManagerInit();


// MISSION

void CreatePlayer(std::shared_ptr<ECSManager> ecs);
void SpawnAliens(std::shared_ptr<ECSManager> ecs, MissionInfo& mInfo);
void SpawnAsteroids(std::shared_ptr<ECSManager> ecs, MissionInfo& mInfo);
