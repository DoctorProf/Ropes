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
	Rope(double x, double y, double width, double height);
	void draw(RenderWindow& window);
};
Rope::Rope() 
{

}
Rope::Rope(double x, double y, double width, double height) 
{
	this->rope.setFillColor(Color::White);
	this->rope.setPosition(x, y);
	this->rope.setSize(Vector2f(width, height));
}
void Rope::draw(RenderWindow& window) 
{
	window.draw(this->rope);
}