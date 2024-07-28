#include "../include/master_header.h"

// PLAYER
bool CollisionPlayerAlien(Player p, Alien a) {
    return CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), p.GetHitBox());
}

bool CollisionPlayerBullet(Player p, Bullet b) {
    return CheckCollisionRecs(b.GetHitBox(), p.GetHitBox());
}

bool CollisionPlayerAsteroid(Player p, Asteroid ast) {
    return CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), p.GetHitBox());
}

// ALIEN
bool CollisionAlienAlien(Alien a1, Alien a2) {
    return CheckCollisionCircles(a1.GetPosition(), static_cast<float>(a1.GetRadius()), a2.GetPosition(), static_cast<float>(a2.GetRadius()));
}

bool CollisionAlienAsteroid(Alien a, Asteroid ast) {
    return CheckCollisionCircles(a.GetPosition(), a.GetRadius(), ast.GetPosition(), ast.GetRadius());
}

bool Game::CollisionAlienBullet(Alien a, Bullet b) {
    return CheckCollisionCircleRec(a.GetPosition(), static_cast<float>(a.GetRadius()), b.GetHitBox());
}

// ASTEROID
bool CollisionAsteroidAsteroid(Asteroid ast1, Asteroid ast2) {
    return CheckCollisionCircles(ast1.GetPosition(), ast1.GetRadius(), ast2.GetPosition(), ast2.GetRadius());
}

bool CollisionAsteroidBullet(Asteroid ast, Bullet b) {
    return CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), b.GetHitBox());
}

// BULLET
bool CollisionBulletBullet(Bullet b1, Bullet b2) {
    return CheckCollisionRecs(b1.GetHitBox(), b2.GetHitBox());
}


void Game::CheckAlienCollisions() {
    if (GetAliensInGame() == 0) return;

    // ALIEN-PLAYER
    int a_index = 0;
    for (Alien& a : GetCurrentAliens()) {
        if (CollisionAlienPlayer(a)) {
            isGameOver = true;
            return;
        }

        bool alien_collision = false;

        // ALIEN-ASTEROID
        int ast_index = 0;
        for (Asteroid& ast : GetCurrentAsteroids()) {
            if (CollisionAlienAsteroid(a, ast)) {
                alien_collision = true;
                const auto velocities = CollisionResponse(a.GetVelocity().current, ast.GetVelocity().current,
                                                          a.GetPosition(), ast.GetPosition(),
                                                          a.GetRadius(), ast.GetRadius() + 30.0f);
                Vector2 new_velocity = std::get<0>(velocities); 
                a.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAlienInGame(a, a_index);

                new_velocity = std::get<1>(velocities); 
                ast.SetVelocity(new_velocity.x, new_velocity.y);
                ast.Move(GetGameLevelMap().GetDeltaT());
                UpdateAsteroidInGame(ast, ast_index);
            }
            ast_index++;
        }

        // ALIEN-ALIEN
        int aa_index = 0;
        for (Alien& aa : GetCurrentAliens()) {
            if (&a != &aa && CollisionAlienAlien(a, aa)) {
                alien_collision = true;

                const auto velocities = CollisionResponse(a.GetVelocity().current, aa.GetVelocity().current,
                                                          a.GetPosition(), aa.GetPosition(),
                                                          a.GetRadius(), aa.GetRadius());
                Vector2 new_velocity = std::get<0>(velocities); 
                a.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAlienInGame(a, a_index);

                new_velocity = std::get<1>(velocities); 
                aa.SetVelocity(new_velocity.x, new_velocity.y);
                aa.Move(GetGameLevelMap().GetDeltaT());
                UpdateAlienInGame(aa, aa_index);
                break;
            }
            aa_index++;
        }

        if (!alien_collision) {
            a.Move(GetGameLevelMap().GetDeltaT());
            a.UpdateDirection(GetPlayer());
            UpdateAlienInGame(a, a_index);
        }
        a_index++;
    }
}

// BULLETS
void Game::CheckBulletCollisions() {
    if (GetBulletsInGame() == 0) return;

    int b_index = 0;
    for (Bullet& b : GetCurrentBullets()) {
        if (b.IsOutOfBounds(GetPlayer().GetPosition())) {
            DeleteBulletInGame(b_index);
            continue;
        }

        if (CollisionBulletPlayer(b)) {
            GetPlayer().UpdateCurrentLife(GetPlayer().GetLife().current - (b.GetDamage() / 2.0f));
            DeleteBulletInGame(b_index);

            if (GetPlayer().GetLife().current <= 0) {
                isGameOver = true;
            }
        } else {
            b.Move(GetGameLevelMap().GetDeltaT());
            UpdateBulletInGame(b, b_index);
        }

        int a_index = 0;
        for (Alien& a : GetCurrentAliens()) {
            if (CollisionBulletAlien(b, a)) {
                a.UpdateCurrentLife(a.GetLife().current - b.GetDamage());
                if (a.GetLife().current <= 0) {
                    DeleteAlienInGame(a_index);
                }
                DeleteBulletInGame(b_index);
                break;
            }
            a_index++;
        }
        b_index++;
    }
}

// ASTEROIDS
void Game::CheckAsteroidCollisions() {
    if (GetAsteroidsInGame() == 0) return;

    int ast_index = 0;
    for (Asteroid& ast : GetCurrentAsteroids()) {
        bool delete_asteroid = false;

        //if (ast.IsOutOfBounds(GetGameLevelMap().GetCurrentLevelBounds())) {
        //    ast.UpdateCurrentLife(ast.GetLife().current - 1.0f);
        //    if (ast.GetLife().current <= 0) delete_asteroid = true;
        //}

        // ASTEROID-BULLET
        int b_index = 0;
        for (Bullet& b : GetCurrentBullets()) {
            if (CollisionAsteroidBullet(ast, b)) {
                ast.UpdateCurrentLife(ast.GetLife().current - b.GetDamage());
                DeleteBulletInGame(b_index);
                if (ast.GetLife().current <= 0) delete_asteroid = true;
            }
            b_index++;
        }

        // ASTEROID-PLAYER
        if (CollisionAsteroidPlayer(ast)) {
            const auto velocities = CollisionResponse(ast.GetVelocity().current, GetPlayer().GetVelocity().current,
                                                      ast.GetPosition(), GetPlayer().GetPosition(),
                                                      ast.GetRadius(), GetPlayer().GetHitBox().width);
            Vector2 new_velocity = std::get<0>(velocities);                                          
            ast.SetVelocity(new_velocity.x, new_velocity.y);
            UpdateAsteroidInGame(ast, ast_index);

            new_velocity = std::get<1>(velocities);
            GetPlayer().SetVelocity(new_velocity.x, new_velocity.y);
        }

        // ASTEROID-ASTEROID
        int ast2_index = 0;
        for (Asteroid& ast2 : GetCurrentAsteroids()) {
            if (&ast != &ast2 && CollisionAsteroidAsteroid(ast, ast2)) {
                const auto velocities = CollisionResponse(ast.GetVelocity().current, ast2.GetVelocity().current,
                                                          ast.GetPosition(), ast2.GetPosition(),
                                                          ast.GetRadius(), ast2.GetRadius());
                Vector2 new_velocity= std::get<0>(velocities);
                ast.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAsteroidInGame(ast, ast_index);

                new_velocity = std::get<1>(velocities);
                ast2.SetVelocity(new_velocity.x, new_velocity.y);
                UpdateAsteroidInGame(ast2, ast2_index);
            }
            ast2_index++;
        }

        ast.Move(GetGameLevelMap().GetDeltaT());
        UpdateAsteroidInGame(ast, ast_index);

        if (delete_asteroid) DeleteAsteroidInGame(ast_index);
        ast_index++;
    }
}


std::tuple<Vector2, Vector2> Game::CollisionResponse (Vector2 v1, Vector2 v2, Vector2 pos1, Vector2 pos2, float m1, float m2) {

    Vector2 C1 = Vector2Subtract(pos1,pos2);
    Vector2 C2 = Vector2Subtract(pos2,pos1);

    float value1 = (2 * m2) / (m1 + m2);
    float value2 = Vector2DotProduct(v1,C1) - Vector2DotProduct(v2,C1);
    float value3 = Vector2LengthSqr(C1);

    Vector2 new_velocity1 = Vector2Subtract(v1, (Vector2Scale(C1,(value1 * value2 / value3))));

    value1 = (2 * m1) / (m1 + m2);
    value2 = Vector2DotProduct(v2,C2) - Vector2DotProduct(v1,C2);
    value3 = Vector2LengthSqr(C2);

    Vector2 new_velocity2 = Vector2Subtract(v2, (Vector2Scale(C2,(value1 * value2 / value3))));

    return {new_velocity1, new_velocity2};

}