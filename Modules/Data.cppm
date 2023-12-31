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
	export RectangleShape createRope(Node& firstNode, Node& secondNode) 
	{
		RectangleShape rope;

		double radius = firstNode.getRadius();
		Vector2f position = Vector2f(firstNode.getPosition().x - radius / 2, firstNode.getPosition().y - radius / 2);
		double width = data::distance(firstNode.getPosition(), secondNode.getPosition());
		double height = radius / 2;

		Vector2f diff = secondNode.getPosition() - firstNode.getPosition();
		double angleDegrees = std::atan2(diff.y, diff.x) * 180 / 3.141592;

		rope.setFillColor(Color::White);
		rope.setPosition(position);
		rope.setSize(Vector2f(width, height));
		rope.setRotation(angleDegrees);

		return rope;
	}
}