#pragma once
#include "../master.hpp"

#define SCREEN_WIDTH                1920
#define SCREEN_HEIGHT               1080

#define TEXTBOX_WIDTH               260
#define TEXTBOX_HEIGHT              70
#define PROMPTBOX_WIDTH             600
#define TEXTBOX_FONTSIZE            40
#define TEXTBOX_THICKNESS           5
#define TITLE_FONTSIZE              100
#define DEBUG_FONTSIZE              20

#define COLOR_BACKGROUND            (Color){10, 10, 40, 255}
#define COLOR_SIMPLETEXT            (Color){LIGHTGRAY}

const Vector2 SCREEN_POS_CENTER_1            = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 - 100};
const Vector2 SCREEN_POS_CENTER_LEFT_1       = {(float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 - 100};
const Vector2 SCREEN_POS_CENTER_2            = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
const Vector2 SCREEN_POS_CENTER_LEFT_2       = {(float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2};
const Vector2 SCREEN_POS_CENTER_3            = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 + 100};
const Vector2 SCREEN_POS_CENTER_LEFT_3       = {(float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 + 100};
const Vector2 SCREEN_POS_CENTER_4            = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 + 200};
const Vector2 SCREEN_POS_CENTER_LEFT_4       = {(float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 + 200};
const Vector2 SCREEN_POS_CENTER_5            = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 + 300};
const Vector2 SCREEN_POS_CENTER_TOP          = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3};
const Vector2 SCREEN_POS_CENTER              = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
const Vector2 SCREEN_POS_CENTER_BOTTOM       = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3};
const Vector2 SCREEN_POS_CENTER_BOTTOM_LEFT  = {(float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3};
const Vector2 SCREEN_POS_CENTER_BOTTOM_RIGHT = {(float)SCREEN_WIDTH / 2 + 300, (float)SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3};
const Vector2 SCREEN_POS_RIGHT_TOP           = {(float)SCREEN_WIDTH / 2 + SCREEN_WIDTH / 3, (float)SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3};
const Vector2 SCREEN_POS_RIGHT               = {(float)SCREEN_WIDTH / 2 + SCREEN_WIDTH / 3, (float)SCREEN_HEIGHT / 2};
const Vector2 SCREEN_POS_RIGHT_BOTTOM        = {(float)SCREEN_WIDTH / 2 + SCREEN_WIDTH / 3, (float)SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3};
const Vector2 SCREEN_POS_LEFT_TOP            = {(float)SCREEN_WIDTH / 2 - SCREEN_WIDTH / 3, (float)SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3};
const Vector2 SCREEN_POS_LEFT                = {(float)SCREEN_WIDTH / 2 - SCREEN_WIDTH / 3, (float)SCREEN_HEIGHT / 2};
const Vector2 SCREEN_POS_LEFT_BOTTOM         = {(float)SCREEN_WIDTH / 2 - SCREEN_WIDTH / 3, (float)SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3};


enum BoxID {
    PLAY,
    LEADERBOARD,
    OPTIONS,
    ABOUT,
    EXIT,
    BACK,
    SCREEN_MODE,
    PROMPT,
    SEE,
    ABORT,
    RESUME,
    YES,
    NO
};

class UIObject {
    public:
        virtual ~UIObject() {}

        // Método virtual puro para garantir que todas as subclasses implementem Draw
        virtual void Draw(float time) = 0;

        bool ShouldBlink(float time);

        Vector2 pos;
        bool isClickable;
        bool isCursorOn;
        bool isBlinkable;
};

class SimpleText : public UIObject {
    public:
        SimpleText() = default;
        SimpleText(std::string text, int fontSize, Vector2 pos, bool b, bool c);

        void Draw(float time);

        std::string text;
        int fontSize;
        int textWidth;
};

class Box : public UIObject {
    public:
        Rectangle GetBox();
        BoxID GetID();
        void SetIsCursorOn(bool b);

        BoxID id;
        int width;
        int height;
};

class TextBox : public Box {
    public:
        TextBox(BoxID id, std::vector<std::string> strings, Vector2 pos, bool b, bool c);

        void SetNextText();
        void SetIsCursorOn(bool b);
        void Draw(float time);

    private:
        std::vector<SimpleText> texts;
        int currentTextIndex;
};

class PromptBox : public Box {
    public:
        PromptBox(std::string input, Vector2 pos);

        void SetText(std::string text);
        void Draw(float time);

    private:
        SimpleText text;

};


// FUNCTIONS
template<typename T>
void PrintValueInGame(std::string name, T value, Vector2 textPos, int fontSize, Color color) {
    std::string valueInGame;

    if constexpr (std::is_floating_point<T>::value) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3) << value;
        valueInGame = ss.str();
    } else if constexpr (std::is_integral<T>::value) {
        valueInGame = std::to_string(value);
    } else if constexpr (std::is_same<T, std::string>::value) {
        valueInGame = value;
    }

    valueInGame = name + ": " + valueInGame;
    DrawText(valueInGame.c_str(), textPos.x, textPos.y, fontSize, color);
}

void PrintTimerInGame(float totalTime, float currentTime, Vector2 textPos, int fontSize);