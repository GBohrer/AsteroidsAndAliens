#include "../include/master_header.h"


const char * ConvertText (std::string string) {
    std::string str;
    const char *cstr;

    str = string;
    cstr = str.c_str();

    return cstr;
}

void PrintTextInGame(bool isFloat, float value, Vector2 textPos, int fontSize, Color color){

    std::string str_pos;
    if (isFloat){
        str_pos = std::to_string(value);
    } else {
        str_pos = std::to_string((int)value);
    }
    DrawText(ConvertText(str_pos), textPos.x, textPos.y, fontSize, color);
}