#ifndef TEXT_FUNCTIONS_H
#define TEXT_FUNCTIONS_H

#include "../master_header.h"

typedef struct TextBox {
    std::string text;
    Rectangle box;
    bool isMouseOn;

    TextBox(std::string t, Rectangle b, bool m) : text(t), box(b), isMouseOn(m) {}

} TextBox;

const char * ConvertText (std::string string);
void PrintTextInGame(bool isFloat, float value, Vector2 textPos, int fontSize, Color color);

#endif