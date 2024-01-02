﻿#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

import Node;
import Data;
import Rope;

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	std::vector<Node> nodes;
	std::vector<Rope> ropes;
	bool pause = true;
	bool mode = false;
	int selectedNode = -1;
	int selectedRope = -1;
	bool selRope = false;
	RenderWindow window(VideoMode(1920, 1080), "Ropes", Style::Fullscreen, settings);

	window.setVerticalSyncEnabled(true);

	Clock logic;
	Time accumulate = Time::Zero;
	Time timePerFrame = seconds(1.0f / 200.0f);
	while (window.isOpen()) 
	{
		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				ropes.clear();
				nodes.clear();
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				pause = !pause;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::E)
			{
				mode = !mode;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
			{
				ropes.clear();
				nodes.clear();
				pause = true;
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) 
			{
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				nodes.push_back(Node(mouseCoor.x, mouseCoor.y));
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Tab && selRope)
			{
				ropes.erase(ropes.begin() + selectedRope);
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				
				for (int i = 0; i < nodes.size(); i++)
				{
					if (nodes[i].clickNode(mouseCoor.x, mouseCoor.y))
					{
						if (mode)
						{
							nodes[i].setBlock(!nodes[i].getBlock());
							break;
						}
						if (selectedNode == -1)
						{
							nodes[i].setActivate(!nodes[i].getActivate());
							selectedNode = i;
							break;
						}
						if (nodes[selectedNode] == nodes[i])
						{
							data::resetActivateNodes(nodes);
							selectedNode = -1;
							break;
						}
						ropes.push_back(Rope(&nodes[selectedNode], &nodes[i]));
						selectedNode = -1;
						data::resetActivateNodes(nodes);
					}
				}
			}
			else if (event.type == Event::MouseMoved)
			{
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				bool mouseOnAnyRopes = false;
				for (int i = 0; i < ropes.size(); i++)
				{
					if (ropes[i].clickRope(mouseCoor))
					{
						ropes[i].setActivate(true);
						mouseOnAnyRopes = true;
						selectedRope = i;
						selRope = true;
					}
					else
					{
						ropes[i].setActivate(false);
					}
				}
				if (!mouseOnAnyRopes) 
				{
					data::resetActivateRopes(ropes);
					selectedRope = -1;
					selRope = false;
				}
			}
		}
		accumulate += logic.restart();
		while (accumulate >= timePerFrame) 
		{
			accumulate -= timePerFrame;
			if (!pause) data::move(nodes);
		}
		window.clear(Color::Black);

		data::drawRopes(ropes, window);
		data::drawNodes(nodes, window);

		window.display();
	}
}
