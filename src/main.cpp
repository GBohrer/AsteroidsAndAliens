
#include "../include/master_header.h"

// COMMON-VARIABLES
Color Background_Color = Color{200, 200, 245, 255};


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
    Alien alien = Alien();
    alien.SetAlienToPlayer(p1);

    while (!WindowShouldClose())
    {
    /// UPDATES
        if (IsKeyPressed(KEY_P))
            ToggleFullscreen();

        if (IsKeyPressed(KEY_T)){ show_text = !show_text;}

    /// RENDERS
        BeginDrawing();
        ClearBackground(Background_Color);
    
        p1.Draw();
        alien.Draw();

        if (show_text){
            str_pos = std::to_string(GetMonitorWidth(GetCurrentMonitor()));
            cstr = str_pos.c_str();
            DrawText(cstr,200,200,60,BLACK );
            str_pos = std::to_string(GetMonitorHeight(GetCurrentMonitor()));
            cstr = str_pos.c_str();
            DrawText(cstr,200,260,60,BLACK );
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}