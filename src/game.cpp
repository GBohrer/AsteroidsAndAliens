#include "../include/master_header.h"


Game::Game() {
    animation_t_now = animation_t_prev = delta_t = 0;
    totalAliens = 5;
    totalBullets = 10;
    timeSinceLastShot = 0.0f;
    this->player = Player("Nickname");
}

// ALIENS
std::vector<Alien> Game::GetCurrentAliens() {
    return aliensInGame;
}

int Game::GetAliensInGame() {
    return (int)aliensInGame.size();
}

void Game::SpawnAliens() {
    while (GetAliensInGame() < totalAliens){
        Alien a_aux = Alien(30,1.0f);
        a_aux.SetAlienToPlayer(GetPlayer(), 500);
        this->aliensInGame.push_back(a_aux);
    }
}

void Game::UpdateAlienInGame(Alien alien, int position){
    this->aliensInGame[position] = alien;
}

void Game::DeleteAlienInGame(int position) {
    this->aliensInGame.erase(aliensInGame.begin() + position);
}

// BULLETS
std::vector<Bullet> Game::GetCurrentBullets() {
    return bulletsInGame;
}

int Game::GetBulletsInGame() {
    if (bulletsInGame.empty()) {return 0; }
    else { return (int)bulletsInGame.size(); }
}

void Game::SpawnBullets() {
    if (GetBulletsInGame() < totalBullets && timeSinceLastShot >= 0.4f){
        this->bulletsInGame.push_back(Bullet(GetPlayer().GetPosition(), 200.0f, 0.4f, 20.0f));
        timeSinceLastShot = 0.0f;
    }
}

void Game::UpdateBulletInGame(Bullet bullet, int position) {
    this->bulletsInGame[position] = bullet;
}

void Game::DeleteBulletInGame(int position) {
    this->bulletsInGame.erase(bulletsInGame.begin() + position);
}

// PLAYER
Player Game::GetPlayer() {
    return player;
}

void Game::SetPlayer(Player p) {
    this->player = player;
}

void Game::PlayerMove() {
    this->player.Move();
}

void Game::UpdateAnimationTime() {
    animation_t_now = (float)GetTime();
    delta_t = animation_t_now - animation_t_prev;
    timeSinceLastShot += delta_t;
    animation_t_prev = animation_t_now;
}

float Game::GetDeltaT() {
    return delta_t;
}
