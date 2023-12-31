#include <iostream>
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
	bool activeNode = false;
	bool mode = false;
	Node selectedNode;
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
				nodes.clear();
				ropes.clear();
				pause = true;
				activeNode = false;
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) 
			{
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				nodes.push_back(Node(mouseCoor.x, mouseCoor.y));
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				
				for (int i = 0; i < nodes.size(); i++)
				{
					if (nodes[i].clickNode(mouseCoor.x, mouseCoor.y))
					{
						if (!activeNode && !mode)
						{
							nodes[i].setActivate(!nodes[i].getActivate());
							activeNode = !activeNode;
							selectedNode = nodes[i];
							break;
						}
						else if (!activeNode && mode) 
						{
							nodes[i].setBlock(!nodes[i].getBlock());
							break;
						}
						ropes.push_back(Rope(data::createRope(selectedNode, nodes[i])));
						activeNode = false;
						data::resetActivate(nodes);
					}
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
