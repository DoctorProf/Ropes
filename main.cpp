#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

import Node;
import Data;
import Rope;

int main()
{
	std::vector<Node> nodes;
	std::vector<Rope> ropes;
	bool pause = true;
	bool activeNode = false;
	Node selectedNode;
	RenderWindow window(VideoMode(1920, 1080), "Ropes", Style::Fullscreen);

	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) 
	{
		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
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
						if (!activeNode)
						{
							nodes[i].setActivate(true);
							activeNode = true;
							selectedNode = nodes[i];
							break;
						}
						ropes.push_back(Rope(10 ,10, 100, 1000));
						activeNode = false;
						data::resetActivate(nodes);
					}
				}
			}
		}

		window.clear(Color::Black);

		data::drawRopes(ropes, window);
		data::drawNodes(nodes, window);

		window.display();
	}
}
