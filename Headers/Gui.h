#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"

using namespace sf;

class Gui
{
public:

    Gui();

    void update(int modeNode, int modeRope, int status, int modeAction);

    void draw(RenderWindow& window);

    RectangleShape barMode;
    RectangleShape barLink;
    RectangleShape barAction;
    RectangleShape barStatus;
    RectangleShape barClear;
    RectangleShape barDeleteRope;
    RectangleShape barChangeMouse;

    Texture barModeTex;
    Texture barLinkTex;
    Texture barActionTex;
    Texture barStatusTex;
    Texture barClearTex;
    Texture barDeleteRopeTex;
    Texture barChangeMouseTex;

    int modeNode;
    int modeRope;
    int modeAction;
    int status;

    Vector2f sizeBar;
};
