#include <iostream>
#include "SFML/Graphics.hpp"

import Node;
import Rope;
import Simulation;
import Logic;
import Gui;

using namespace sf;

void resetActivateNodes(std::vector<Node>& nodes) 
{
	for (int i = 0; i < nodes.size(); i++) 
	{
		nodes[i].activate = false;
	}
}
void resetActivateRopes(std::vector<Rope>& ropes)
{
	for (int i = 0; i < ropes.size(); i++)
	{
		ropes[i].activate = false;
	}
}

VertexArray createGrid(RenderWindow& window, int radius)
{
	VertexArray grid;
	grid.setPrimitiveType(Lines);

	int windowX = window.getSize().x;
	int windowY = window.getSize().y;
	int radiusCell = radius * 2;

	for (int i = 0; i <= windowX; i += radiusCell)
	{
		Vertex point;
		point.color = Color::Color(40, 40, 40);

		point.position = Vector2f(i, 0);

		grid.append(point);

		point.position = Vector2f(i, windowY);

		grid.append(point);
	}
	for (int i = 0; i <= windowY; i += radiusCell)
	{
		Vertex point;
		point.color = Color::Color(40, 40, 40);

		point.position = Vector2f(0, i);

		grid.append(point);

		point.position = Vector2f(windowX, i);

		grid.append(point);
	}
	return grid;

}
int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	Clock logic;
	Time accumulate = Time::Zero;
	Time deltaTime = seconds(1.0f / 60.0f);	

	std::vector<Node> nodes;
	std::vector<Rope> ropes;

	bool pause = true;
	int mode{};
	bool selRope = false;

	int modeRope = 0;

	int selectedNode = -1;
	int numberNode = 0;
	int countNodes = 200;
	int radiusNode = 20;

	RenderWindow window(VideoMode(1920, 1080), "Ropes", Style::Fullscreen, settings);
	window.setVerticalSyncEnabled(true);

	View world;
	world.setSize(Vector2f(window.getSize()));
	world.setCenter(Vector2f(window.getSize().x / 2.0, window.getSize().y / 2.0));

	View guiWindow;
	guiWindow.setSize(Vector2f(window.getSize()));
	guiWindow.setCenter(Vector2f(window.getSize().x / 2.0, window.getSize().y / 2.0));

	Simulation simulate(nodes, ropes, deltaTime.asSeconds());
	Gui gui;

	nodes.resize(countNodes);

	VertexArray grid = createGrid(window, radiusNode);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::MouseMoved)
			{
				Vector2i mouseCoor = Mouse::getPosition(window);
				resetActivateRopes(ropes);
				for (int i = 0; i < ropes.size(); i++)
				{
					ropes[i].activate = ropes[i].clickRope(Vector2f(mouseCoor.x, mouseCoor.y));
					if(ropes[i].activate) break;
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				nodes.clear();
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				pause = !pause;

			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q)
			{
				if (modeRope) modeRope = 0;
				else modeRope = 1;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::E)
			{
				mode += 1;
				if (mode > 2) mode = 0;
				resetActivateNodes(nodes);
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::C)
			{
				nodes.clear();
				ropes.clear();
				pause = true;
				numberNode = 0;
				nodes.resize(countNodes);
				window.clear(Color::Black);
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Tab)
			{
				for (int i = 0; i < ropes.size(); i++) 
				{
					Vector2i mouseCoor = Mouse::getPosition(window);
					if (ropes[i].activate && ropes[i].clickRope(Vector2f(mouseCoor.x, mouseCoor.y)))
					{
						ropes.erase(ropes.begin() + i);
						break;
					}
				}
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
			{
				if (numberNode == nodes.size()) break;
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				nodes[numberNode++] = Node(mouseCoor.x, mouseCoor.y, radiusNode);
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));

				for (int i = 0; i < nodes.size(); i++)
				{
					if (nodes[i].clickNode(mouseCoor.x, mouseCoor.y))
					{
						if (mode == 1)
						{
							resetActivateNodes(nodes);
							nodes[i].isStatic = !nodes[i].isStatic;
							break;
						}
						if (mode == 2)
						{
							resetActivateNodes(nodes);
							for (int j = 0; j < ropes.size(); j++)
							{
								if (ropes[j].startNode == &nodes[i] || ropes[j].endNode == &nodes[i])
								{
									ropes.erase(ropes.begin() + j);
								}
							}
							nodes[i] = Node();
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
						ropes.push_back(Rope(&nodes[selectedNode], &nodes[i], distance, modeRope));
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
				simulate.update();
			}
		}
		window.clear(Color::Black);

		window.setView(world);

		window.draw(grid);

		simulate.render(nodes, ropes, window);

		window.setView(guiWindow);

		gui.update(mode, modeRope, pause);
		gui.draw(window);


		window.display();
	}
}