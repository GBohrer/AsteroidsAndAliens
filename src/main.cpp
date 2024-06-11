
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{
    bool game_over = false;

    const int screenWidth  = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    SetTargetFPS(60);

    std::string str_pos;
    const char *cstr;
    bool show_text = true;

    Game game = Game();


    while (!WindowShouldClose())
    {
    /// UPDATES
        if (game_over) { break; }

        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_T)) show_text = !show_text;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) game.PlayerMove();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) game.SpawnBullets();

        game.UpdateAnimationTime();
        game.SpawnAliens();

        //std::cout << game.GetBulletsInGame() << "\n";

        int index1 = 0;
        for (Alien& a : game.GetCurrentAliens()) {
            bool collision = false;

            // Collision: Alien - Player
            if (CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), game.GetPlayer().GetHitBox())){
                game_over = true;
                break;
            }

            if(game.GetBulletsInGame() > 0) {

                int index2 = 0;
                for (Bullet& bullet : game.GetCurrentBullets()){

                    if (bullet.IsOutOfBounds(game.GetPlayer().GetPosition())) {
                        game.DeleteBulletInGame(index2);
                        continue;
                    }

                    // Collision: Alien - Bullet
                    if (CheckCollisionCircleRec(a.GetPosition(), (float)a.GetRadius(), bullet.GetHitBox())){
                        collision = true;
                        game.DeleteBulletInGame(index2);
                        game.DeleteAlienInGame(index1);
                    }
                    bullet.Move(game.GetDeltaT());
                    game.UpdateBulletInGame(bullet, index2);
                    index2++;
                }
            }

            int index2 = 0;
            for (Alien& aa : game.GetCurrentAliens()) {

                // Collision: Alien - Alien
                if (&a != &aa && CheckCollisionCircles(a.GetPosition(), (float)a.GetRadius(), aa.GetPosition(), (float)aa.GetRadius())) {
                    collision = true;
                    
                    Vector2 new_direction = Vector2Add(a.GetDirection(), aa.GetDirection());

                    a.Move(game.GetPlayer(), game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(a, index1);

                    aa.Move(game.GetPlayer(), game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(aa, index2);
                    break;
                }
                index2++;
            }
            if (!collision) {
                a.Move(game.GetPlayer(), game.GetDeltaT(), a.GetDirection());
                game.UpdateAlienInGame(a, index1);
            }
            index1++;
        }

    /// RENDERS
        BeginDrawing();
        ClearBackground(color_space_background);
    
        game.GetPlayer().DrawHitBox();

        for (Alien& a : game.GetCurrentAliens()){ a.DrawHitBox(); }
        for (Bullet& b : game.GetCurrentBullets()){
            b.DrawHitBox();

            if (show_text){
                str_pos = std::to_string((int)b.GetPosition().x);
                cstr = str_pos.c_str();
                DrawText(cstr,200,200,60, WHITE);  

                str_pos = std::to_string((int)b.GetPosition().y);
                cstr = str_pos.c_str();
                DrawText(cstr,200,260,60, WHITE);
            }
        }

        if (show_text) {
            for (int i = 0; i < game.GetAliensInGame(); i++){
                    str_pos = std::to_string(i);
                    cstr = str_pos.c_str();
                    DrawText(cstr,game.GetCurrentAliens()[i].GetPosition().x,
                                  game.GetCurrentAliens()[i].GetPosition().y -50 ,30, WHITE);
            }
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}