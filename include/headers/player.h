#pragma once
#include "position.h"
#include <string>

class Player
{
public:
    Player(); 
    Player(std::string name);
    std::string GetName();
    void SetName(std::string name);
    int GetScore();
    void SetScore(int value);
    bool GetIsBuffed();
    void SetIsBuffed(bool value);
    Position GetPosition();
    void SetPosition(Position pos);

private:
    std::string name;
    int score;
    bool isBuffed;
    Position pos;

};