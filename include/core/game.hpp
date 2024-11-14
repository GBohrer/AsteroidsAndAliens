#pragma once
#include "../master.hpp"

const static std::string GAME_VERSION = "v.0.0.1";

// ============================== TIMER STRUCTS
typedef struct GameTimer {
    double run_time;

    double animation_t_now;
    double animation_t_prev;
    double delta_t;
    
}GameTimer;

// ============================== GAMESTATE
enum State {
    START_MENU,
    MAIN_MENU,
    SCORES_MENU,
    OPTIONS_MENU,
    ABOUT_MENU,
    GAME,
    PAUSE,
    GAMEOVER,
    SAVE_MENU,
    LEAVING
};

typedef struct GameState {
    State state;
    std::vector<std::shared_ptr<UIObject>> gameScreen;

    GameState() = default;
    GameState(State s, std::vector<std::shared_ptr<UIObject>> gs)
        : state(s), gameScreen(std::move(gs)) {}

} GameState;

typedef struct GameInfo {
    std::unordered_map<State, GameState> gameStates;
    std::unordered_map<std::string, Texture2D> gameImages;

} GameInfo;


class Game {

    public:
        static Game& GetGame() {
            static Game instance;
            return instance;
        }

        bool Running();
        void Update();
        void Draw();
        void Close();

        GameState& GetCurrentGameState();
        void SetCurrentGameState(State state);

        void MissionInit();
        void ClearCurrentMission();

        std::vector<std::shared_ptr<UIObject>>& GetUIObjects();

        double GetRunTime();
        double GetDeltaT();

        void UpdateFileName(PromptBox* pb);

    protected:
        void UpdateGameTimer();
        

    private:
        Game();
        GameInfo gameInfo;
        bool isGameRunning;
        GameState currentGameState;
        GameTimer t;
        SaveFile SaveFile;
        std::unique_ptr<ECSManager> ECSManager;
};
