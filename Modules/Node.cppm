module;

#include <iostream>
#include "SFML/Graphics.hpp"
using namespace sf;

export module Node;

export class Node 
{
private:
	CircleShape node;
	double x;
	double y;
	double radius;
	bool block;
	bool activate;
public:
	Node();
	Node(double x, double y);
	Vector2f getPosition();
	void move();
	void draw(RenderWindow& window);
	bool clickNode(double x, double y);
	void setActivate(bool activate);
	bool getActivate();
};
Node::Node()
{

}
Node::Node(double x, double y)
{
	this->x = x;
	this->y = y;
	this->radius = 20;
	this->node.setRadius(this->radius);
	this->node.setPosition(Vector2f(x - radius, y - radius));
	this->node.setPointCount(100);
	this->block = false;
	this->activate = false;
}
Vector2f Node::getPosition() 
{
	return Vector2f(this->x, this->y);
}
void Node::move()
{
	this->node.move(Vector2f(1, 0));
}
void Node::draw(RenderWindow& window) 
{
	this->node.setFillColor(Color::White);
	if (this->block) this->node.setFillColor(Color::Red);
	if (this->activate) this->node.setFillColor(Color::Green);
	window.draw(this->node);
}
bool Node::clickNode(double x, double y)
{
	return (pow(this->x - x, 2) + pow(this->y - y, 2)) <= pow(this->radius, 2);
}
void Node::setActivate(bool activate)
{
	this->activate = activate;
}
bool Node::getActivate() 
{
	return this->activate;
}
