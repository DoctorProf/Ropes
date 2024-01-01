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
	Node* startNode;
	Node* endNode;
public:
	Rope();
	Rope(Node* startNode, Node* endNode);
	ConvexShape updatePosition();
	void draw(RenderWindow& window);
};
Rope::Rope() 
{

}
Rope::Rope(Node* startNode, Node* endNode)
{
	this->startNode = startNode;
	this->endNode = endNode;
	this->rope = updatePosition();
}
ConvexShape Rope::updatePosition()
{
	ConvexShape rope;
	double radius = startNode->getRadius();
	Vector2f diff = endNode->getPosition() - startNode->getPosition();
	double angleDegrees = std::atan2(diff.y, diff.x) * 180 / 3.141592;

	rope.setPointCount(4);
	rope.setFillColor(Color::White);
	if (abs(angleDegrees) > 80 && abs(angleDegrees) < 100)
	{
		rope.setPoint(0, Vector2f(startNode->getPosition().x - radius / 2, startNode->getPosition().y));
		rope.setPoint(1, Vector2f(startNode->getPosition().x + radius / 2, startNode->getPosition().y));
		rope.setPoint(2, Vector2f(endNode->getPosition().x + radius / 2, endNode->getPosition().y));
		rope.setPoint(3, Vector2f(endNode->getPosition().x - radius / 2, endNode->getPosition().y));
	}
	else
	{
		rope.setPoint(0, Vector2f(startNode->getPosition().x, startNode->getPosition().y - radius / 2));
		rope.setPoint(1, Vector2f(startNode->getPosition().x, startNode->getPosition().y + radius / 2));
		rope.setPoint(2, Vector2f(endNode->getPosition().x, endNode->getPosition().y + radius / 2));
		rope.setPoint(3, Vector2f(endNode->getPosition().x, endNode->getPosition().y - radius / 2));
	}
	return rope;
}
void Rope::draw(RenderWindow& window) 
{
	this->rope = updatePosition();
	window.draw(this->rope);
}