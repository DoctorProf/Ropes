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
	export void resetActivateNodes(std::vector<Node>& nodes) 
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			nodes[i].setActivate(false);
		}
	}
	export void resetActivateRopes(std::vector<Rope>& ropes)
	{
		for (int i = 0; i < ropes.size(); i++)
		{
			ropes[i].setActivate(false);
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
}