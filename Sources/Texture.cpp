#include "../Headers/Texture.h"

std::vector<Texture> textures::texturesBarMode;
std::vector<Texture> textures::texturesBarAction;
std::vector<Texture> textures::texturesBarModeRope;
std::vector<Texture> textures::texturesBarStatus;

Texture textures::rope;
Texture textures::steelBeam;
Texture textures::clear;
Texture textures::cross;
Texture textures::hand;
Texture textures::cursor;
Texture textures::deleteRope;
Texture textures::changeMouse;

Texture textures::modeAccelerator;
Texture textures::modeConnect;
Texture textures::modeBlock;

Texture textures::modeAdd;
Texture textures::modeDelete;
Texture textures::modeMove;

Texture textures::modeSteelBeam;
Texture textures::modeRope;

Texture textures::modeStart;
Texture textures::modePause;

void textures::loadTextures()
{
    rope.loadFromFile("Resources/rope.png");
    steelBeam.loadFromFile("Resources/steelBeam.jpg");
    clear.loadFromFile("Resources/clear.png");
    cross.loadFromFile("Resources/cross.png");
    hand.loadFromFile("Resources/hand.png");
    cursor.loadFromFile("Resources/cursor.png");
    deleteRope.loadFromFile("Resources/deleteRope.png");
    changeMouse.loadFromFile("Resources/changeMouse.png");

    modeConnect.loadFromFile("Resources/modeConnect.png");
    modeBlock.loadFromFile("Resources/modeBlock.png");
    modeAccelerator.loadFromFile("Resources/modeAccelerator.png");

    texturesBarMode =
    {
        modeConnect,
        modeBlock,
        modeAccelerator
    };

    modeAdd.loadFromFile("Resources/modeAdd.png");
    modeDelete.loadFromFile("Resources/modeDelete.png");
    modeMove.loadFromFile("Resources/modeMove.png");

    texturesBarAction =
    {
        modeAdd,
        modeDelete,
        modeMove
    };

    modeSteelBeam.loadFromFile("Resources/modeSteelBeam.png");
    modeRope.loadFromFile("Resources/modeRope.png");

    texturesBarModeRope =
    {
        modeSteelBeam,
        modeRope
    };

    modeStart.loadFromFile("Resources/modeStart.png");
    modePause.loadFromFile("Resources/modePause.png");

    texturesBarStatus =
    {
        modeStart,
        modePause
    };
}
