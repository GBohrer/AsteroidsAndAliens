#pragma once

struct GTimer {
    std::chrono::high_resolution_clock::time_point startTime; // Hora de início
    std::chrono::high_resolution_clock::duration pausedTime{}; // Tempo acumulado enquanto pausado
    bool isRunning{false}; // Se o timer está rodando
    bool isPaused{false};  // Se o timer está pausado

    // Inicia ou reinicia o timer
    void Start() {
        startTime = std::chrono::high_resolution_clock::now();
        isPaused = false;
        isRunning = true;
        pausedTime = std::chrono::high_resolution_clock::duration::zero();
    }

    // Pausa o timer
    void Pause() {
        if (isRunning && !isPaused) {
            pausedTime = std::chrono::high_resolution_clock::now() - startTime;
            isPaused = true;
        }
    }

    // Retoma o timer
    void Resume() {
        if (isRunning && isPaused) {
            startTime = std::chrono::high_resolution_clock::now() - pausedTime;
            isPaused = false;
        }
    }

    // Para o timer
    void Stop() {
        isRunning = false;
        isPaused = false;
    }

    // Retorna o tempo decorrido em segundos
    double ElapsedSeconds() const {
        if (isRunning) {
            if (isPaused) {
                return std::chrono::duration<double>(pausedTime).count();
            } else {
                return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();
            }
        }
        return 0.0;
    }

    // Retorna o tempo decorrido em milissegundos
    double ElapsedMilliseconds() const {
        if (isRunning) {
            if (isPaused) {
                return std::chrono::duration<double, std::milli>(pausedTime).count();
            } else {
                return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count();
            }
        }
        return 0.0;
    }
};