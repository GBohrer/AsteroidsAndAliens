/*  EXEMPLO DE ATUALIZAR VALOR NA TELA COM DRAWTEXT()

    std::string str_pos;
    const char *cstr;
    str_pos = std::to_string(ball.GetPosition().GetX());
    cstr = str_pos.c_str();
    DrawText(cstr,100,100,40,BLACK );


/// EXEMPLO DO CHAT GPT DO USO DE ITERADORES NOS VECTORS DE ALIENS E BULLETS:

    // Atualiza todos os alienígenas
    for (auto it_a = game.GetCurrentAliens().begin(); it_a != game.GetCurrentAliens().end();) {
        Alien& a = *it_a;
        bool collision = false;

        // Collision: Alien - Player
        if (CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), game.GetPlayer().GetHitBox())) {
            game_over = true;
            break;
        }

        // Atualiza todas as balas e verifica colisões
        if (game.GetBulletsInGame() > 0) {
            for (auto it_b = game.GetCurrentBullets().begin(); it_b != game.GetCurrentBullets().end();) {
                Bullet& bullet = *it_b;

                if (bullet.IsOutOfBounds(game.GetPlayer().GetPosition())) {
                    it_b = game.DeleteBulletInGame(it_b);
                    continue;
                }

                // Collision: Alien - Bullet
                if (CheckCollisionCircleRec(a.GetPosition(), (float)a.GetRadius(), bullet.GetHitBox())) {
                    collision = true;
                    it_b = game.DeleteBulletInGame(it_b);
                    it_a = game.DeleteAlienInGame(it_a);
                    break;
                } else {
                    bullet.Move(game.GetDeltaT());
                    game.UpdateBulletInGame(bullet);
                    ++it_b;
                }
            }
        }

        if (!collision) {
            for (auto it_aa = game.GetCurrentAliens().begin(); it_aa != game.GetCurrentAliens().end(); ++it_aa) {
                Alien& aa = *it_aa;

                // Collision: Alien - Alien
                if (&a != &aa && CheckCollisionCircles(a.GetPosition(), (float)a.GetRadius(), aa.GetPosition(), (float)aa.GetRadius())) {
                    collision = true;

                    Vector2 new_direction = Vector2Add(a.GetDirection(), aa.GetDirection());

                    a.Move(game.GetPlayer(), game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(a);

                    aa.Move(game.GetPlayer(), game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(aa);
                    break;
                }
            }
        }

        if (!collision) {
            a.Move(game.GetPlayer(), game.GetDeltaT(), a.GetDirection());
            game.UpdateAlienInGame(a);
        }

        if (!collision || it_a == game.GetCurrentAliens().end()) {
            ++it_a;
        }
    }

}

/// CODIGO PARA MOVER A CAMERA ATRAVES DO MOUSE NOS LIMITES DA TELA
    Vector2 mouse = GetMousePosition();
    if (mouse.x > screenWidth - 15) camera.offset.x -= 5;
    if (mouse.x < 15) camera.offset.x += 5;
    if (mouse.y > screenHeight - 15) camera.offset.y -= 5;
    if (mouse.y < 15) camera.offset.y += 5;


*/
