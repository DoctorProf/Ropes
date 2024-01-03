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
	export void move(std::vector<Node>& nodes, std::vector<Rope>& ropes, Clock& deltaTime, double& gravity)
	{
		std::vector<Node> currentNode;
		for (int i = 0; i < nodes.size(); i++) 
		{
			for (int j = 0; j < ropes.size(); j++) 
			{
				if (ropes[j].getStartNode() == nodes[i] ||
					ropes[j].getEndNode() == nodes[i]) 
				{
					nodes[i] == ropes[j].getStartNode() ? currentNode.push_back(ropes[j].getEndNode()) : currentNode.push_back(ropes[j].getStartNode());
				}
			}

			for (int j = 0; j < currentNode.size(); j++) 
			{
				Vector2f force = currentNode[j].getPosition() - nodes[i].getPosition();
				float mass = 10000;
				Vector2f acceleration = force / mass;
				Vector2f deltaVelocity = acceleration * deltaTime.getElapsedTime().asSeconds();

				nodes[i].updateSpeed(deltaVelocity);
			}
			nodes[i].move(deltaTime, gravity);
			currentNode.clear();
		}
	}
	export double distance(Vector2f vec1, Vector2f vec2)
	{
		double dx = vec1.x - vec2.x;
		double dy = vec1.y - vec2.y;
		return std::sqrt(dx * dx + dy * dy);
	}
}