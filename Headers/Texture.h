#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

namespace textures
{
    extern Texture rope;
    extern Texture steelBeam;
    extern Texture clear;
    extern Texture cross;
    extern Texture hand;
    extern Texture cursor;
    extern Texture deleteRope;
    extern Texture changeMouse;

    extern Texture modeConnect;
    extern Texture modeBlock;
    extern Texture modeAccelerator;

    extern std::vector<Texture> texturesBarMode;

    extern Texture modeAdd;
    extern Texture modeDelete;
    extern Texture modeMove;

    extern std::vector<Texture> texturesBarAction;

    extern Texture modeSteelBeam;
    extern Texture modeRope;

    extern std::vector<Texture> texturesBarModeRope;

    extern Texture modeStart;
    extern Texture modePause;

    extern std::vector<Texture> texturesBarStatus;

    void loadTextures();
}
