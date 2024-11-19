#pragma once
#include "../master.hpp"


// GAME

std::unordered_map<State, GameState> GameStateInit();
GameInfo GameInfoInit();
GameTimer GameTimerInit();
std::unique_ptr<ECSManager> GameECSManagerInit();


// MISSION

void CreatePlayer(std::shared_ptr<ECSManager> ecs);
void CreateAsteroids(std::shared_ptr<ECSManager> ecs);
void CreateAliens(std::shared_ptr<ECSManager> ecs);
