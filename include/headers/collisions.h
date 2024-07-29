#pragma once
#include "../master_header.h"

bool CheckCollisionPlayerAlien(Player p, Alien a);
bool CheckCollisionPlayerBullet(Player p, Bullet b);
bool CheckCollisionPlayerAsteroid(Player p, Asteroid ast);
bool CheckCollisionAlienAlien(Alien a1, Alien a2);
bool CheckCollisionAlienAsteroid(Alien a, Asteroid ast);
bool CheckCollisionAlienBullet(Alien a, Bullet b);
bool CheckCollisionAsteroidAsteroid(Asteroid ast1, Asteroid ast2);
bool CheckCollisionAsteroidBullet(Asteroid ast, Bullet b);
bool CheckCollisionBulletBullet(Bullet b1, Bullet b2);

void CheckEntityCollisions(float delta_t, LevelMap* l, Player* player);
void UpdateEntityVelocities();
std::tuple<Vector2, Vector2> CollisionResponse(Vector2 v1, Vector2 v2, Vector2 pos1, Vector2 pos2, float m1, float m2);


