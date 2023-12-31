module;

#include <iostream>
#include "SFML/Graphics.hpp"
import Node;
using namespace sf;

export module Rope;

export class Rope 
{
private:
	ConvexShape rope;
public:
	Rope();
	Rope(ConvexShape rope);
	void draw(RenderWindow& window);
};
Rope::Rope() 
{

}
Rope::Rope(ConvexShape rope)
{
	this->rope = rope;
}
void Rope::draw(RenderWindow& window) 
{
	window.draw(this->rope);
}