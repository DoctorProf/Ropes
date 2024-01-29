
#include "../Headers/Gui.h"

Gui::Gui()
{
    sizeBar = { 51, 70 };

    barLink.setSize(sizeBar);
    barLink.setPosition(sf::Vector2f(10, 1000));

    barMode.setSize(sizeBar);
    barMode.setPosition(sf::Vector2f(71, 1000));

    barAction.setSize(sizeBar);
    barAction.setPosition(sf::Vector2f(131, 1000));

    barStatus.setSize(sizeBar);
    barStatus.setPosition(sf::Vector2f(191, 1000));

    barClear.setSize(sizeBar);
    barClear.setPosition(sf::Vector2f(251, 1000));

    barDeleteRope.setSize(sizeBar);
    barDeleteRope.setPosition(sf::Vector2f(311, 1000));

    barChangeMouse.setSize(sizeBar);
    barChangeMouse.setPosition(sf::Vector2f(371, 1000));
}

void Gui::update(int modeNode, int modeRope, int status, int modeAction)
{
    this->modeNode = modeNode;
    this->modeRope = modeRope;
    this->modeAction = modeAction;
    this->status = status;
}

void Gui::draw(sf::RenderWindow& window)
{
    barMode.setTexture(&textures::texturesBarMode[modeNode]);
    barLink.setTexture(&textures::texturesBarModeRope[modeRope]);
    barAction.setTexture(&textures::texturesBarAction[modeAction]);
    barStatus.setTexture(&textures::texturesBarStatus[status]);
    barClear.setTexture(&textures::clear);
    barDeleteRope.setTexture(&textures::deleteRope);
    barChangeMouse.setTexture(&textures::changeMouse);

    window.draw(barMode);
    window.draw(barLink);
    window.draw(barAction);
    window.draw(barStatus);
    window.draw(barClear);
    window.draw(barDeleteRope);
    window.draw(barChangeMouse);
}
