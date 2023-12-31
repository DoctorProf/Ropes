module;

#include <iostream>
#include "SFML/Graphics.hpp"
import Node;
using namespace sf;

export module Rope;

export class Rope 
{
private:
	RectangleShape rope;
public:
	Rope();
	Rope(RectangleShape rope);
	void draw(RenderWindow& window);
};
Rope::Rope() 
{

}
Rope::Rope(RectangleShape rope)
{
	this->rope = rope;
}
void Rope::draw(RenderWindow& window) 
{
	window.draw(this->rope);
}