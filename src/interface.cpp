#include "../include/master.hpp"

// UIObject

bool UIObject::ShouldBlink(float time) {
    if (!isBlinkable || ((fmod(time, 1.0f) < 0.5f) && time >= 3.0f)) {
        return true;
    } else {
        return false;
    }
}


// SIMPLETEXT

SimpleText::SimpleText(std::string text, int fontSize, Vector2 pos, bool b, bool c) {
    this->isBlinkable = b;
    this->isClickable = c;
    this->isCursorOn = false;
    this->text = text;
    this->fontSize = fontSize;
    this->textWidth = MeasureText(text.c_str(), fontSize);
    this->pos = {pos.x - textWidth/2, pos.y};
}

void SimpleText::Draw(float time) {
    if (ShouldBlink(time)) {
        Color color;
        if (isCursorOn) { color = YELLOW; } else { color = LIGHTGRAY; }
        DrawText(text.c_str(), pos.x, pos.y, fontSize, color);
    }
}

// BOX

Rectangle Box::GetBox() {
    Rectangle r = {pos.x, pos.y, (float)width, (float)height};
    return r;
}

BoxID Box::GetID() {
    return this->id;
}

void Box::SetIsCursorOn(bool b) {
    this->isCursorOn = b;
}

// TEXTBOX

TextBox::TextBox(BoxID id, std::vector<std::string> strings, Vector2 pos, bool b, bool c) {
    this->id = id;
    this->width = TEXTBOX_WIDTH;
    this->height = TEXTBOX_HEIGHT;
    this->isCursorOn = false;
    this-> isBlinkable = b;
    this->isClickable = c;
    this->pos = {pos.x - width/2, pos.y};
    this->currentTextIndex = 0;
    
    texts.reserve(strings.size());

    for(const std::string& s : strings) {
        int new_fontsize = TEXTBOX_FONTSIZE;
        int text_width = MeasureText(s.c_str(), new_fontsize);

        while( text_width >= TEXTBOX_WIDTH) {
            new_fontsize -= 2;
            text_width = MeasureText(s.c_str(), new_fontsize);
        }

        Vector2 t_pos;
        if (id == BoxID::PROMPT) {
            b = true;
            t_pos = {pos.x + 5, pos.y + (height - new_fontsize)/2};
        } else {
            t_pos = {pos.x, pos.y + (height - new_fontsize)/2};
        }
        texts.emplace_back(SimpleText(s, new_fontsize, t_pos, b, c));
    }
}

void TextBox::SetNextText() {
    this->currentTextIndex = (currentTextIndex + 1) % texts.size();
}

void TextBox::SetIsCursorOn(bool b) {
    this->isCursorOn = b;
    texts[currentTextIndex].isCursorOn = b;
}

void TextBox::Draw(float time) {
    if (ShouldBlink(time)) {
        Color color;
        if (isCursorOn) { color = YELLOW; } else { color = LIGHTGRAY; }
        DrawRectangleLinesEx({pos.x, pos.y, (float)width, (float)height}, TEXTBOX_THICKNESS, color);
        texts[currentTextIndex].Draw(time);
    }
}


// PROMPTBOX

PromptBox::PromptBox(std::string input, Vector2 pos) {  
    this->id = BoxID::PROMPT;
    this->width = TEXTBOX_WIDTH;
    this->height = TEXTBOX_HEIGHT;
    this->isCursorOn = false;
    this->isBlinkable = false;
    this->isClickable = true;
    this->pos = {pos.x - width/2, pos.y};
    
    Vector2 t_pos = {pos.x - width/2 + 20, pos.y + (height - TEXTBOX_FONTSIZE)/2};
    this->text = SimpleText(input, TEXTBOX_FONTSIZE, t_pos, false, true);
}

void PromptBox::SetText(std::string text) {
    this->text.text = text;
}

void PromptBox::Draw(float time) {
    DrawRectangleLinesEx({pos.x, pos.y, (float)width, (float)height}, TEXTBOX_THICKNESS, COLOR_SIMPLETEXT);
    text.Draw(time);
}
