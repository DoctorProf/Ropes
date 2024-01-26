module;

#include <iostream>
#include "SFML/Graphics.hpp"

import Texture;

using namespace sf;

export module Gui;

export class Gui
{
public:
	RectangleShape barMode;
	RectangleShape barLink;
	RectangleShape barStatus;

	Texture barModeTex;
	Texture barLinkTex;
	Texture barStatusTex;

	int mode;
	int modeRope;
	bool status;

	Vector2f sizeBar = { 51, 70 };

	Gui() 
	{
		barMode.setSize(sizeBar);
		barMode.setPosition(Vector2f(10, 1000));

		barLink.setSize(sizeBar);
		barLink.setPosition(Vector2f(71, 1000));

		barStatus.setSize(sizeBar);
		barStatus.setPosition(Vector2f(131, 1000));
	}
	void update(int mode, int modeRope, int status)
	{
		this->mode = mode;
		this->modeRope = modeRope;
		this->status = status;

		barModeTex.loadFromFile(textures::texturesBarMode[mode]);
		barLinkTex.loadFromFile(textures::texturesBarModeRope[modeRope]);
		barStatusTex.loadFromFile(textures::texturesBarStatus[status]);
	}
	void draw(RenderWindow& window)
	{
		barMode.setTexture(&barModeTex);
		barLink.setTexture(&barLinkTex);
		barStatus.setTexture(&barStatusTex);

		window.draw(barMode);
		window.draw(barLink);
		window.draw(barStatus);
	}
};