
#include "../Headers/Gui.h"

Gui::Gui()
{
    sizeBar = { 51, 70 };

    barLink.setSize(sizeBar);
    barLink.setPosition(Vector2f(10, 1000));

    barMode.setSize(sizeBar);
    barMode.setPosition(Vector2f(71, 1000));

    barAction.setSize(sizeBar);
    barAction.setPosition(Vector2f(131, 1000));

    barStatus.setSize(sizeBar);
    barStatus.setPosition(Vector2f(191, 1000));

    barClear.setSize(sizeBar);
    barClear.setPosition(Vector2f(251, 1000));

    barDeleteRope.setSize(sizeBar);
    barDeleteRope.setPosition(Vector2f(311, 1000));

    barChangeMouse.setSize(sizeBar);
    barChangeMouse.setPosition(Vector2f(371, 1000));

    barExportJson.setSize(sizeBar);
    barExportJson.setPosition(Vector2f(431, 1000));

    barImportJson.setSize(sizeBar);
    barImportJson.setPosition(Vector2f(491, 1000));
}

void Gui::update(int modeNode, int modeRope, int status, int modeAction)
{
    this->modeNode = modeNode;
    this->modeRope = modeRope;
    this->modeAction = modeAction;
    this->status = status;
}

void Gui::draw(RenderWindow& window)
{
    barMode.setTexture(&textures::texturesBarMode[modeNode]);
    barLink.setTexture(&textures::texturesBarModeRope[modeRope]);
    barAction.setTexture(&textures::texturesBarAction[modeAction]);
    barStatus.setTexture(&textures::texturesBarStatus[status]);
    barClear.setTexture(&textures::clear);
    barDeleteRope.setTexture(&textures::deleteRope);
    barChangeMouse.setTexture(&textures::changeMouse);
    barExportJson.setTexture(&textures::exportJson);
    barImportJson.setTexture(&textures::importJson);

    window.draw(barMode);
    window.draw(barLink);
    window.draw(barAction);
    window.draw(barStatus);
    window.draw(barClear);
    window.draw(barDeleteRope);
    window.draw(barChangeMouse);
    window.draw(barExportJson);
    window.draw(barImportJson);
}
