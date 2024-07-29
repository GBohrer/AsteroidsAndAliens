#include "../include/master_header.h"

// PLAYER
bool CheckCollisionPlayerAlien(Player p, Alien a) {
    return CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), p.GetHitBox());
}

bool CheckCollisionPlayerBullet(Player p, Bullet b) {
    return CheckCollisionRecs(b.GetHitBox(), p.GetHitBox());
}

bool CheckCollisionPlayerAsteroid(Player p, Asteroid ast) {
    return CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), p.GetHitBox());
}

// ALIEN
bool CheckCollisionAlienAlien(Alien a1, Alien a2) {
    return CheckCollisionCircles(a1.GetPosition(), static_cast<float>(a1.GetRadius()), a2.GetPosition(), static_cast<float>(a2.GetRadius()));
}

bool CheckCollisionAlienAsteroid(Alien a, Asteroid ast) {
    return CheckCollisionCircles(a.GetPosition(), a.GetRadius(), ast.GetPosition(), ast.GetRadius());
}

bool CheckCollisionAlienBullet(Alien a, Bullet b) {
    return CheckCollisionCircleRec(a.GetPosition(), static_cast<float>(a.GetRadius()), b.GetHitBox());
}

// ASTEROID
bool CheckCollisionAsteroidAsteroid(Asteroid ast1, Asteroid ast2) {
    return CheckCollisionCircles(ast1.GetPosition(), ast1.GetRadius(), ast2.GetPosition(), ast2.GetRadius());
}

bool CheckCollisionAsteroidBullet(Asteroid ast, Bullet b) {
    return CheckCollisionCircleRec(ast.GetPosition(), ast.GetRadius(), b.GetHitBox());
}

// BULLET
bool CheckCollisionBulletBullet(Bullet b1, Bullet b2) {
    return CheckCollisionRecs(b1.GetHitBox(), b2.GetHitBox());
}


void CheckEntityCollisions(float delta_t, LevelMap* l, Player* player) {

    if (l->GetAliensInGame() > 0) {

        // ALIEN-PLAYER
        int a_index = 0;
        for (Alien& a : l->GetCurrentAliens()) {

            if (CheckCollisionPlayerAlien(*player, a)) {
                player->UpdateCurrentLife(player->GetLife().current - a.GetRadius()/100.0f);
            }

            bool alien_collision = false;

            // ALIEN-ASTEROID
            int ast_index = 0;
            for (Asteroid& ast : l->GetCurrentAsteroids()) {
                if (CheckCollisionAlienAsteroid(a, ast)) {
                    alien_collision = true;
                    const auto velocities = CollisionResponse(a.GetVelocity().current, ast.GetVelocity().current,
                                                              a.GetPosition(), ast.GetPosition(),
                                                              a.GetRadius(), ast.GetRadius() + 30.0f);
                    Vector2 new_velocity = std::get<0>(velocities); 
                    a.SetVelocity(new_velocity.x, new_velocity.y);
                    l->UpdateAlienInGame(a, a_index);

                    new_velocity = std::get<1>(velocities); 
                    ast.SetVelocity(new_velocity.x, new_velocity.y);
                    ast.Move(delta_t);
                    l->UpdateAsteroidInGame(ast, ast_index);
                }
                ast_index++;
            }

            // ALIEN-ALIEN
            int aa_index = 0;
            for (Alien& aa : l->GetCurrentAliens()) {
                if (&a != &aa && CheckCollisionAlienAlien(a, aa)) {
                    alien_collision = true;

                    const auto velocities = CollisionResponse(a.GetVelocity().current, aa.GetVelocity().current,
                                                              a.GetPosition(), aa.GetPosition(),
                                                              a.GetRadius(), aa.GetRadius());
                    Vector2 new_velocity = std::get<0>(velocities); 
                    a.SetVelocity(new_velocity.x, new_velocity.y);
                    l->UpdateAlienInGame(a, a_index);

                    new_velocity = std::get<1>(velocities); 
                    aa.SetVelocity(new_velocity.x, new_velocity.y);
                    aa.Move(delta_t);
                    l->UpdateAlienInGame(aa, aa_index);
                    break;
                }
                aa_index++;
            }

            if (!alien_collision) {
                a.Move(delta_t);
                a.UpdateDirection(*player);
                l->UpdateAlienInGame(a, a_index);
            }
            a_index++;
        }
    }

    if (l->GetBulletsInGame() > 0) {

        int b_index = 0;
        for (Bullet& b : l->GetCurrentBullets()) {
            if (b.IsOutOfBounds(player->GetPosition())) {
                l->DeleteBulletInGame(b_index);
                continue;
            }

            if (CheckCollisionPlayerBullet(*player, b)) {
                player->UpdateCurrentLife(player->GetLife().current - (b.GetDamage() / 2.0f));
                l->DeleteBulletInGame(b_index);

            } else {
                b.Move(delta_t);
                l->UpdateBulletInGame(b, b_index);
            }

            int a_index = 0;
            for (Alien& a : l->GetCurrentAliens()) {
                if (CheckCollisionAlienBullet(a, b)) {
                    a.UpdateCurrentLife(a.GetLife().current - b.GetDamage());
                    if (a.GetLife().current <= 0) {
                        l->DeleteAlienInGame(a_index);
                    }
                    l->UpdateAlienInGame(a, a_index);
                    l->DeleteBulletInGame(b_index);
                    break;
                }
                a_index++;
            }
            b_index++;
        }
    }

    if (l->GetAsteroidsInGame() > 0) {

        int ast_index = 0;
        for (Asteroid& ast : l->GetCurrentAsteroids()) {
            bool delete_asteroid = false;

            //if (ast.IsOutOfBounds(l.GetGameLevelMap().GetCurrentLevelBounds())) {
            //    ast.UpdateCurrentLife(ast.GetLife().current - 1.0f);
            //    if (ast.GetLife().current <= 0) delete_asteroid = true;
            //}

            // ASTEROID-BULLET
            int b_index = 0;
            for (Bullet& b : l->GetCurrentBullets()) {
                if (CheckCollisionAsteroidBullet(ast, b)) {
                    ast.UpdateCurrentLife(ast.GetLife().current - b.GetDamage());
                    l->DeleteBulletInGame(b_index);

                    if (ast.GetLife().current <= 0) { delete_asteroid = true; }
                    else { l->UpdateAsteroidInGame(ast, ast_index); }
                }
                b_index++;
            }

            // ASTEROID-PLAYER
            if (CheckCollisionPlayerAsteroid(*player, ast)) {
                const auto velocities = CollisionResponse(ast.GetVelocity().current, player->GetVelocity().current,
                                                          ast.GetPosition(), player->GetPosition(),
                                                          ast.GetRadius(), player->GetHitBox().width);
                Vector2 new_velocity = std::get<0>(velocities);                                          
                ast.SetVelocity(new_velocity.x, new_velocity.y);
                l->UpdateAsteroidInGame(ast, ast_index);

                new_velocity = std::get<1>(velocities);
                player->SetVelocity(new_velocity.x, new_velocity.y);
            }

            // ASTEROID-ASTEROID
            int ast2_index = 0;
            for (Asteroid& ast2 : l->GetCurrentAsteroids()) {
                if (&ast != &ast2 && CheckCollisionAsteroidAsteroid(ast, ast2)) {
                    const auto velocities = CollisionResponse(ast.GetVelocity().current, ast2.GetVelocity().current,
                                                              ast.GetPosition(), ast2.GetPosition(),
                                                              ast.GetRadius(), ast2.GetRadius());
                    Vector2 new_velocity= std::get<0>(velocities);
                    ast.SetVelocity(new_velocity.x, new_velocity.y);
                    l->UpdateAsteroidInGame(ast, ast_index);

                    new_velocity = std::get<1>(velocities);
                    ast2.SetVelocity(new_velocity.x, new_velocity.y);
                    l->UpdateAsteroidInGame(ast2, ast2_index);
                }
                ast2_index++;
            }

            ast.Move(delta_t);
            l->UpdateAsteroidInGame(ast, ast_index);

            if (delete_asteroid) l->DeleteAsteroidInGame(ast_index);
            ast_index++;
        }
    }
}

std::tuple<Vector2, Vector2> CollisionResponse (Vector2 v1, Vector2 v2, Vector2 pos1, Vector2 pos2, float m1, float m2) {

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