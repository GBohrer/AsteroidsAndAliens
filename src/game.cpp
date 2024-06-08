#include "../include/master_header.h"


Game::Game() {
    animation_t_now = animation_t_prev = delta_t = 0;
    totalAliens = 5;
}

std::vector<Alien> Game::GetCurrentAliens() {
    return aliensInGame;
}

int Game::GetAliensInGame() {
    return (int)aliensInGame.size();
}

void Game::SetInitialAliens(Player p1) {
    for(int i = 0; i < totalAliens ; i++){
        this->aliensInGame.push_back(Alien(20, 200));
        this->aliensInGame[i].SetAlienToPlayer(p1);
    }
}

void Game::UpdateAliensInGame(Alien alien, int position){
    this->aliensInGame[position] = alien;
}

void Game::UpdateAnimationTime() {
    animation_t_now = (float)GetTime();
    delta_t = animation_t_now - animation_t_prev;
    animation_t_prev = animation_t_now;
}

float Game::GetDeltaT() {
    return delta_t;
}