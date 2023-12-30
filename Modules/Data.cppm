module;

#include <iostream>
#include "SFML/Graphics.hpp"
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
}