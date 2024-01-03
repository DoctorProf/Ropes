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
	bool activate;
public:
	Rope();
	Rope(Node* startNode, Node* endNode);
	ConvexShape updatePosition();
	void draw(RenderWindow& window);
	void setActivate(bool activate);
	bool getActivate();
	bool clickRope(Vector2f mousePos);
	Node getStartNode();
	Node getEndNode();
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

	if (abs(angleDegrees) > 60 && abs(angleDegrees) < 120)
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
	rope.setFillColor(Color::White);
	rope = updatePosition();
	if (activate) rope.setFillColor(Color::Blue);
	window.draw(rope);
}
void Rope::setActivate(bool activate)
{
	this->activate = activate;
}
bool Rope::getActivate()
{
	return activate;
}
bool Rope::clickRope(Vector2f mousePos) 
{
	Transform transform = rope.getTransform().getInverse();
	Vector2f localClick = transform.transformPoint(mousePos);

	return rope.getGlobalBounds().contains(localClick);
}
Node Rope::getStartNode() 
{
	return *startNode;
}
Node Rope::getEndNode() 
{
	return *endNode;
}
