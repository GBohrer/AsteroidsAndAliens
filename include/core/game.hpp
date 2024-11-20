#pragma once
#include "../master.hpp"

const static std::string GAME_VERSION = "v.0.0.1";

typedef struct GameTimer {

    std::chrono::high_resolution_clock::time_point start_time;    // Tempo de início total do jogo
    std::chrono::high_resolution_clock::time_point prev_time;     // Tempo da atualização anterior
    std::chrono::duration<double> run_time;                       // Tempo total de execução
    double delta_t;

    void Start() {
        start_time = std::chrono::high_resolution_clock::now();
        prev_time = start_time;
    }

    void Update() {
        auto current_time =  std::chrono::high_resolution_clock::now();

        run_time = current_time - start_time;
        delta_t =  std::chrono::duration_cast< std::chrono::duration<double>>(current_time - prev_time).count();
        prev_time = current_time;
    }

    double GetRunTime() const {
        return  std::chrono::duration_cast< std::chrono::duration<double>>(run_time).count();
    }

    double GetDeltaT() const {
        return delta_t;
    }
    
}GameTimer;

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
    bool isGameRunning;
    bool debugMode;
    GameState currentGameState;

} GameInfo;

typedef struct MissionInfo {
    GTimer timer;
    int maxAliens;
    std::vector<Entity> aliens;
    int maxAsteroids;
    std::vector<Entity> asteroids;
    int waveCount;

    void Init() {
        timer.Start();
        maxAliens = 10;
        aliens.resize(maxAliens);
        maxAsteroids = 50;
        asteroids.resize(maxAsteroids);
        waveCount = 0;
    }

    void Reset() {
        timer.Stop();
        aliens.clear();
        asteroids.clear();
        waveCount = 0;
    }

} MissionInfo;

class Game {

    public:
        static Game& GetGame() {
            static Game instance;
            return instance;
        }

        bool Running();
        void Start();
        void Pause();
        void Resume();
        void Reset();
        void Update();
        void Render();
        void Close();

        GameState& GetCurrentGameState();
        void SetCurrentGameState(State state);

        GameTimer GetTimer();

        std::vector<std::shared_ptr<UIObject>>& GetUIObjects();

        void UpdateSystems();
        void UpdateFileName(PromptBox* pb);
        void RenderDebugScreen();

    private:
        Game();
        GameInfo info;
        MissionInfo mInfo;
        GameTimer timer;
        std::shared_ptr<ECSManager> ECSManager;

        //SaveFile SaveFile;
};
