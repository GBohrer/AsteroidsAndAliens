#include "../include/master_header.h"


void PrintTextInGame(bool isFloat, float value, Vector2 textPos, int fontSize, Color color){

    std::string str_pos;
    const char *cstr;

    if (isFloat){
        str_pos = std::to_string(value);
    } else {
        str_pos = std::to_string((int)value);
    }

    cstr = str_pos.c_str();
    DrawText(cstr, textPos.x, textPos.y, fontSize, color);
}