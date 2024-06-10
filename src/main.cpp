
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{

    Game game = Game();

    const int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    SetTargetFPS(60);

    std::string str_pos;
    const char *cstr;
    bool show_text = true;

    Player p1 = Player("Gabriel");
    game.SetInitialAliens(p1);

    while (!WindowShouldClose())
    {
    /// UPDATES
        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_T)) show_text = !show_text;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) p1.Move();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) game.SpawnBullets(p1);

        game.UpdateAnimationTime();

        int index1 = 0;
        for (Alien& a : game.GetCurrentAliens()) {
            bool collision = false;

            if (CheckCollisionCircleRec(a.GetPosition(), a.GetRadius(), {p1.GetPosition().x,
                                                                         p1.GetPosition().y,
                                                                         p1.GetHitBox().x,
                                                                         p1.GetHitBox().y})){
                p1.SetPosition((float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f);
            }

            if(game.GetBulletsInGame() > 0) {

                int index2 = 0;
                for (Character& bullet : game.GetCurrentBullets()){
                    if (CheckCollisionCircleRec(a.GetPosition(), (float)a.GetRadius(), {bullet.GetPosition().x,
                                                                                        bullet.GetPosition().y,
                                                                                        2,
                                                                                        10,})){
                        collision = true;
                        bullet.SetDirection(Vector2Invert(bullet.GetDirection()));
                    }
                    bullet.Move();
                    game.UpdateBulletsInGame(bullet, index2);
                    index2++;
                }
            }

            int index2 = 0;
            for (Alien& aa : game.GetCurrentAliens()) {
                if (&a != &aa && CheckCollisionCircles(a.GetPosition(), (float)a.GetRadius(), aa.GetPosition(), (float)aa.GetRadius())) {
                    collision = true;
                    
                    Vector2 new_direction = Vector2Add(a.GetDirection(), aa.GetDirection());

                    a.Move(p1, game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(a, index1);

                    aa.Move(p1, game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(aa, index2);
                    break;
                }
                index2++;
            }
            if (!collision) {
                a.Move(p1, game.GetDeltaT(), a.GetDirection());
                game.UpdateAlienInGame(a, index1);
            }
            index1++;
        }

    /// RENDERS
        BeginDrawing();
        ClearBackground(color_space_background);
    
        p1.DrawHitBox();

        for (Alien& a : game.GetCurrentAliens()){ a.DrawHitBox(); }
        for (Character& b : game.GetCurrentBullets()){ b.DrawHitBox(); }

        if (show_text){
            str_pos = std::to_string((int)p1.GetPosition().x);
            cstr = str_pos.c_str();
            DrawText(cstr,200,200,60, WHITE);
            str_pos = std::to_string((int)p1.GetPosition().y);
            cstr = str_pos.c_str();
            DrawText(cstr,200,260,60, WHITE);

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