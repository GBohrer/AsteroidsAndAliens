#pragma once
#include "../master.hpp"


// INTERFACE

void Handle_UI(Game& game, std::function<void(TextBox*)> callback);


// GAME

void Handle_START_MENU(Game& game);
void Handle_MAIN_MENU(Game& game);
void Handle_SCORES_MENU(Game& game);
void Handle_OPTIONS_MENU(Game& game);
void Handle_ABOUT_MENU(Game& game);
void Handle_GAME(Game& game);
void Handle_PAUSE(Game& game);
void Handle_GAMEOVER(Game& game);
void Handle_SAVE_MENU(Game& game);
void Handle_LEAVING(Game& game);

extern std::map<State, std::function<void(Game&)>> stateHandlers;


std::unordered_map<std::string, Texture2D> LoadGameImages();
void UnloadGameImages(std::unordered_map<std::string, Texture2D>& gameImages);


// AUDIO