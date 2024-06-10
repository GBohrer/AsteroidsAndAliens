
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

        game.UpdateAnimationTime();

        int index1 = 0;
        for (Alien& a : game.GetCurrentAliens()) {
            bool collisionDetected = false;
            int index2 = 0;
            for (Alien& aa : game.GetCurrentAliens()) {
                if (&a != &aa && CheckCollisionCircles(a.GetPosition(), (float)a.GetRadius(), aa.GetPosition(), (float)aa.GetRadius())) {
                    collisionDetected = true;
                    
                    Vector2 new_direction = Vector2Add(a.GetDirection(), aa.GetDirection());

                    a.Move(p1, game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(a, index1);

                    aa.Move(p1, game.GetDeltaT(), new_direction);
                    game.UpdateAlienInGame(aa, index2);
                    break;
                }
                index2++;
            }
            if (!collisionDetected) {
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