#include "../include/master_header.h"


Game::Game() {
    animation_t_now = animation_t_prev = delta_t = 0;
    totalAliens = 5;
    totalBullets = 10;
}

std::vector<Alien> Game::GetCurrentAliens() {
    return aliensInGame;
}

int Game::GetAliensInGame() {
    return (int)aliensInGame.size();
}

void Game::SetInitialAliens(Player p1) {
    for(int i = 0; i < totalAliens ; i++){
        this->aliensInGame.push_back(Alien(30, 1.0f));
        this->aliensInGame[i].SetAlienToPlayer(p1, 500);
    }
}

void Game::UpdateAlienInGame(Alien alien, int position){
    this->aliensInGame[position] = alien;
}

std::vector<Bullet> Game::GetCurrentBullets() {
    return bulletsInGame;
}

int Game::GetBulletsInGame() {
    if (bulletsInGame.empty()) {return 0; }
    else { return (int)bulletsInGame.size(); }
}

void Game::UpdateBulletInGame(Bullet bullet, int position) {
    this->bulletsInGame[position] = bullet;
}

void Game::SpawnBullets(Player p1) {
    while (GetBulletsInGame() < totalBullets){
        this->bulletsInGame.push_back(Bullet(p1.GetPosition(), 200.0f, 20.0f));
    }
}

void Game::UpdateAnimationTime() {
    animation_t_now = (float)GetTime();
    delta_t = animation_t_now - animation_t_prev;
    animation_t_prev = animation_t_now;
}

float Game::GetDeltaT() {
    return delta_t;
}
