#include "../include/master_header.h"


const char * ConvertText (std::string string) {
    std::string str;
    const char *cstr;

    str = string;
    cstr = str.c_str();

    return cstr;
}

void PrintValueInGame(bool isFloat, float value, Vector2 textPos, int fontSize, Color color) {

    std::string str_pos;
    if (isFloat){
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << value;
        str_pos = ss.str();
    } else {
        str_pos = std::to_string((int)value);
    }
    DrawText(ConvertText(str_pos), textPos.x, textPos.y, fontSize, color);
}

void PrintTimerInGame(float totalTime, float currentTime, Vector2 textPos, int fontSize) {
    int min = static_cast<int>(currentTime) / 60;
    int sec = static_cast<int>(currentTime) % 60;
    int c_sec = static_cast<int>((currentTime - static_cast<int>(currentTime)) * 100);

    std::ostringstream formattedTime;

    if (min > 0) {
        formattedTime   << std::setw(2) << std::setfill('0') << min << ":"
                        << std::setw(2) << std::setfill('0') << sec;
    } else {
        formattedTime   << std::setw(2) << std::setfill('0') << sec << ":"
                        << std::setw(2) << std::setfill('0') << c_sec;
    }
    std::string text = formattedTime.str();

    if (currentTime >= 0.6 * totalTime ) {
        DrawText(ConvertText(text), textPos.x, textPos.y, fontSize, WHITE);
    } else if (currentTime >= 0.3 * totalTime) {
        DrawText(ConvertText(text), textPos.x, textPos.y, fontSize, YELLOW);
    } else if (currentTime >= 0.15 * totalTime) {
        DrawText(ConvertText(text), textPos.x, textPos.y, fontSize, ORANGE);
    } else {
        DrawText(ConvertText(text), textPos.x, textPos.y, fontSize, RED);
    }
}

void PrintDifficultyInGame(LevelDifficulty ld, Vector2 textPos, int fontSize) {

    std::string str_pos;
    switch (ld) {
        case LevelDifficulty::VERY_EASY:
            str_pos = "Very Easy";
            break;
        case LevelDifficulty::EASY:
            str_pos = "Easy";
            break;
        case LevelDifficulty::MEDIUM: 
            str_pos = "Medium";
            break;
        case LevelDifficulty::HARD:
            str_pos = "Hard";
            break;
        case LevelDifficulty::VERY_HARD:
            str_pos = "Very Hard";
            break;
    }

    DrawText(ConvertText(str_pos), textPos.x, textPos.y, fontSize, WHITE);
}
