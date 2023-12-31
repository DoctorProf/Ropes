module;

#include <iostream>
#include "SFML/Graphics.hpp"
#include <cmath>

import Node;
import Rope;
using namespace sf;

export module Data;

namespace data 
{
	export void drawNodes(std::vector<Node>& nodes, RenderWindow& window) 
	{
		for(int i = 0; i < nodes.size(); i++)
		{
			nodes[i].draw(window);
		}
	}
	export void drawRopes(std::vector<Rope>& ropes, RenderWindow& window)
	{
		for (int i = 0; i < ropes.size(); i++)
		{
			ropes[i].draw(window);
		}
	}
	export void resetActivate(std::vector<Node>& nodes) 
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			nodes[i].setActivate(false);
		}
	}
	export void move(std::vector<Node>& nodes) 
	{
		for (int i = 0; i < nodes.size(); i++) 
		{
			nodes[i].move();
		}
	}
	export double distance(Vector2f vec1, Vector2f vec2)
	{
		double dx = vec1.x - vec2.x;
		double dy = vec1.y - vec2.y;
		return std::sqrt(dx * dx + dy * dy);
	}
	export ConvexShape createRope(Node& firstNode, Node& secondNode) 
	{
		ConvexShape rope;
		double radius = firstNode.getRadius();
		Vector2f diff = secondNode.getPosition() - firstNode.getPosition();
		double angleDegrees = std::atan2(diff.y, diff.x) * 180 / 3.141592;

		rope.setPointCount(4);
		rope.setFillColor(Color::White);
		if (abs(angleDegrees) > 80 && abs(angleDegrees) < 100)
		{
			rope.setPoint(0, Vector2f(firstNode.getPosition().x - radius / 2, firstNode.getPosition().y));
			rope.setPoint(1, Vector2f(firstNode.getPosition().x + radius / 2, firstNode.getPosition().y));
			rope.setPoint(2, Vector2f(secondNode.getPosition().x + radius / 2, secondNode.getPosition().y));
			rope.setPoint(3, Vector2f(secondNode.getPosition().x - radius / 2, secondNode.getPosition().y));
		}
		else 
		{
			rope.setPoint(0, Vector2f(firstNode.getPosition().x, firstNode.getPosition().y - radius / 2));
			rope.setPoint(1, Vector2f(firstNode.getPosition().x, firstNode.getPosition().y + radius / 2));
			rope.setPoint(2, Vector2f(secondNode.getPosition().x, secondNode.getPosition().y + radius / 2));
			rope.setPoint(3, Vector2f(secondNode.getPosition().x, secondNode.getPosition().y - radius / 2));
		}
		return rope;
	}
}