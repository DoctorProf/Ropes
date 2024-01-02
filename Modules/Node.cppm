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
	double getRadius();
	void move();
	void draw(RenderWindow& window);
	bool clickNode(double x, double y);
	void setActivate(bool activate);
	bool getActivate();
	void setBlock(bool block);
	bool getBlock();
	bool operator==(const Node& other) const;
};
Node::Node()
{

}
Node::Node(double x, double y)
{
	this->x = x;
	this->y = y;
	radius = 20;
	node.setRadius(radius);
	node.setPosition(Vector2f(x - radius, y - radius));
	node.setPointCount(100);
	block = false;
	activate = false;
}
Vector2f Node::getPosition() 
{
	return Vector2f(x, y);
}
double Node::getRadius() 
{
	return radius;
}
void Node::move()
{
	if (block) return;
}
void Node::draw(RenderWindow& window) 
{
	node.setFillColor(Color::White);
	if (block) node.setFillColor(Color::Red);
	if (activate) node.setFillColor(Color::Green);
	window.draw(node);
}
bool Node::clickNode(double x, double y)
{
	return (pow(this->x - x, 2) + pow(this->y - y, 2)) <= pow(radius, 2);
}
void Node::setActivate(bool activate)
{
	this->activate = activate;
}
bool Node::getActivate() 
{
	return activate;
}
void Node::setBlock(bool block) 
{
	this->block = block;
}
bool Node::getBlock() 
{
	return block;
}
bool Node::operator==(const Node& other) const 
{
	return (x == other.x) && (y == other.y) && (radius == other.radius) &&
		(block == other.block) && (activate == other.activate);
}
