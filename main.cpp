#include <iostream>
#include "SFML/Graphics.hpp"

import Node;
import Rope;
import Simulation;
import Logic;

using namespace sf;

void resetActivateNodes(std::vector<Node>& nodes) 
{
	for (int i = 0; i < nodes.size(); i++) 
	{
		nodes[i].activate = false;
	}
}
int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	Clock logic;
	Time accumulate = Time::Zero;
	Time deltaTime = seconds(1.0f / 60.0f);

	Simulation simulate;

	std::vector<Node> nodes;
	std::vector<Rope> ropes;

	bool pause = true;
	bool mode = false;
	bool selRope = false;

	int selectedNode = -1;
	int selectedRope = -1;
	int numberNode = 0;
	int countNodes = 100;
	double gravity = 9.81;

	RenderWindow window(VideoMode(1920, 1080), "Ropes", Style::Fullscreen, settings);

	nodes.resize(countNodes);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
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
				resetActivateNodes(nodes);
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
			{
				nodes.clear();
				ropes.clear();
				pause = true;
				numberNode = 0;
				nodes.resize(countNodes);
				window.clear(Color::Black);
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
			{
				if (numberNode == nodes.size()) break;
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				nodes[numberNode++] = Node(mouseCoor.x, mouseCoor.y);
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
							nodes[i].isStatic = !nodes[i].isStatic;
							break;
						}
						if (selectedNode == -1)
						{
							resetActivateNodes(nodes);
							nodes[i].activate = !nodes[i].activate;
							selectedNode = i;
							break;
						}
						if (nodes[selectedNode] == nodes[i])
						{
							resetActivateNodes(nodes);
							selectedNode = -1;
							break;
						}
						resetActivateNodes(nodes);
						double distance = logic::distance(nodes[selectedNode].getPosition(), nodes[i].getPosition());
						ropes.push_back(Rope(&nodes[selectedNode], &nodes[i], distance));
						selectedNode = -1;
					}
				}
			}
		}
		accumulate += logic.restart();
		while (accumulate >= deltaTime)
		{
			accumulate -= deltaTime;
			if (!pause)
			{
				simulate.update(nodes, ropes, deltaTime.asSeconds(), gravity);
			}
			window.clear(Color::Black);

			simulate.render(nodes, ropes, window);

			window.display();
		}
	}
}