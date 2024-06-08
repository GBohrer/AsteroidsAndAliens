
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};

float animation_t_prev = 0;
float animation_t_now = 0;
float delta_t = 0;

const int total_aliens = 10;
std::vector<Alien> aliens_in_game;


int main()
{

    const int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    SetTargetFPS(60);

    std::string str_pos;
    const char *cstr;
    bool show_text = true;

    Player p1 = Player("Gabriel");

    // Instanciando primeiros aliens
    for(int i = 0; i < total_aliens; i++){
        aliens_in_game.push_back(Alien(20, 200));
        aliens_in_game[i].SetAlienToPlayer(p1);
    }

    while (!WindowShouldClose())
    {
    /// UPDATES
        if (IsKeyPressed(KEY_P))
            ToggleFullscreen();

        if (IsKeyPressed(KEY_I))
            printf("%f", aliens_in_game.front().GetPosition().x);

        if (IsKeyPressed(KEY_T)){ show_text = !show_text;}

        // Calculo do tempo de animacao
        animation_t_now = (float)GetTime();
        delta_t = animation_t_now - animation_t_prev;
        animation_t_prev = animation_t_now;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            p1.Move();
        };

        for (Alien& a : aliens_in_game){
            a.Move(p1, delta_t);
        };

    /// RENDERS
        BeginDrawing();
        ClearBackground(color_space_background);
    
        p1.Draw();

        for (Alien& a : aliens_in_game){ a.Draw(); }

        if (show_text){
            str_pos = std::to_string((int)p1.GetPosition().x);
            cstr = str_pos.c_str();
            DrawText(cstr,200,200,60, WHITE);
            str_pos = std::to_string((int)p1.GetPosition().y);
            cstr = str_pos.c_str();
            DrawText(cstr,200,260,60, WHITE);

            str_pos = std::to_string((float)aliens_in_game.front().GetDirection().x);
            cstr = str_pos.c_str();
            DrawText(cstr,360,200,60, WHITE);
            str_pos = std::to_string((float)aliens_in_game.front().GetDirection().y);
            cstr = str_pos.c_str();
            DrawText(cstr,360,260,60, WHITE);

            for (int i = 0; i < aliens_in_game.size(); i++){
                str_pos = std::to_string(i);
                cstr = str_pos.c_str();
                DrawText(cstr,aliens_in_game[i].GetPosition().x, aliens_in_game[i].GetPosition().y -15 ,60, WHITE);
            }

        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}