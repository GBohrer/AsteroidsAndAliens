
#include "../include/master_header.h"

// COMMON-VARIABLES
Color color_space_background = Color{10, 10, 40, 255};


int main()
{
    bool game_over = false;
    bool show_text = true;

    int score = 0;

    const int screenWidth  = 700; //GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = 700; //GetMonitorHeight(GetCurrentMonitor());

    InitWindow(screenWidth, screenHeight, "Galactic Adventures");

    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
    /// UPDATES
        if (game_over) { break; }

        if (IsKeyPressed(KEY_P)) ToggleFullscreen();
        if (IsKeyPressed(KEY_T)) show_text = !show_text;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) game.PlayerMove();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) game.SpawnBullets();

        if (game.CheckDifficultyIncrease(score)){ game.IncreaseDifficulty();}

        game.UpdateAnimationTime();
        game.SpawnAliens();

        //std::cout << game.GetBulletsInGame() << "\n";

        if (game.GetAliensInGame() == 0) {continue;}

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

                        score++;
                    } else {
                        bullet.Move(game.GetDeltaT());
                        game.UpdateBulletInGame(bullet, index2);
                    }
                    index2++;
                }
            }

            int index2 = 0;
            for (Alien& aa : game.GetCurrentAliens()) {

                // Collision: Alien - Alien
                if (&a != &aa && CheckCollisionCircles(a.GetPosition(), (float)a.GetRadius(), aa.GetPosition(), (float)aa.GetRadius())) {
                    collision = true;
                    
                    Vector2 new_direction = Vector2Add(a.GetDirection(), aa.GetDirection());

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
        PrintTextInGame(false, score, {GetScreenWidth()/2.0f, 70}, 50, WHITE);

        for (Alien& a : game.GetCurrentAliens()){ a.DrawHitBox(); }
        for (Bullet& b : game.GetCurrentBullets()){b.DrawHitBox(); }

        if (show_text) {
            for (int i = 0; i < game.GetAliensInGame(); i++){
                PrintTextInGame(false, i, game.GetCurrentAliens()[i].GetPosition(), 20, WHITE);
            }
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}