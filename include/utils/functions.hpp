#pragma once
#include "../master.hpp"


// GAME

std::unordered_map<State, GameState> GameStateInit();
GameInfo GameInfoInit();
std::unique_ptr<ECSManager> GameECSManagerInit();
Camera2D GameCameraInit();


// MISSION

void SpawnPlayer(std::shared_ptr<ECSManager> ecs, MissionInfo& mInfo);
void SpawnAliens(std::shared_ptr<ECSManager> ecs, MissionInfo& mInfo);
void SpawnAsteroids(std::shared_ptr<ECSManager> ecs, MissionInfo& mInfo);
