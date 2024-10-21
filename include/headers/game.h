#pragma once
#include "../master_header.h"

#include "bullet.h"
#include "asteroid.h"

enum State {
    InMenu,
    InGame,
    GameOver,
    Paused,
    IsLoading
};

typedef struct GameStateInfo {
    State state;
    std::vector<TextBox> text_boxes;

    GameStateInfo() {}
    GameStateInfo(State s, std::vector<TextBox> v) : state(s), text_boxes(v) {}

} GameStateInfo;

class Game {

    public:
        Game();

        void Start();
        void Reset();

        LevelMap& GetGameLevelMap();

        //GAME STATE
        std::unordered_map<State, GameStateInfo>& GetGameStates();
        void SetInitialGameStates();
        GameStateInfo GetCurrentGameState();
        void SetCurrentGameState (GameStateInfo gameStateInfo);
        void UpdateCurrentGameStateTextBox (TextBox tb, int position);

        Vector2 GetLastMousePosition();
        void SetLastMousePosition(Vector2 mouse);

        //PLAYER
        Player& GetPlayer();
        void SetPlayer(Player p);
        void UpdatePlayer();

        //CAMERA
        Camera2D& GetCamera();
        void SetCamera();
        void SetCameraZoom(float zoom);
        void UpdateCamera(int screenWidth, int screenHeight);
        
        bool isGameOver();
        void Update();
        void Render();

        void UpdateTime();
        float GetDeltaT();

    protected:
        Vector2 LastMousePosition;

    // Timestamps
        float animation_t_prev;
        float animation_t_now;
        float delta_t;
        float timeSinceLastShot;
        float timeSinceLastAlienSpawn;

    private:
        std::unordered_map<State, GameStateInfo> gameStates;
        GameStateInfo currentGameState;
        LevelMap level;

        Player player;
        Camera2D camera;

};

