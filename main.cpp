
#include "Headers/Texture.h"
#include "Headers/Gui.h"
#include "Headers/Simulation.h"

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
	textures::loadTextures();
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	Clock logic;
	Time accumulate = Time::Zero;
	Time deltaTime = seconds(1.0f / 60.0f);	

	std::vector<Node> nodes;
	std::vector<Rope> ropes;

	bool pause = true;

	bool modeMouseLeftClick = true;
	int modeNode = 0;
	int modeRope = 0;
	int modeAction = 0;

	int selectedNode = -1;

	int idNode = 0;
	int countNodes = 2000;
	int radiusNode = 20;

	bool isDragging = false;
	Vector2f lastMousePos;

	Node* moveNode{};

	RenderWindow window(VideoMode(1920, 1080), "Ropes", Style::Fullscreen, settings);

	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	View world;
	world.setSize(Vector2f(window.getSize()));
	world.setCenter(Vector2f(window.getSize().x / 2.0, window.getSize().y / 2.0));

	View guiWindow;
	guiWindow.setSize(Vector2f(window.getSize()));
	guiWindow.setCenter(Vector2f(window.getSize().x / 2.0, window.getSize().y / 2.0));

	Simulation simulate(nodes, ropes, deltaTime.asSeconds(), radiusNode, idNode);
	Gui gui;

	nodes.reserve(countNodes);

	VertexArray grid = createGrid(window, radiusNode);

	CircleShape imaginaryNode;
	RectangleShape deleteNode;
	RectangleShape hand;
	RectangleShape cursor;

	imaginaryNode.setFillColor(Color(255, 255, 255, 100));

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
			else if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) || event.type == sf::Event::Closed)
			{
				ropes.clear();
				nodes.clear();
				window.close();
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				pause = !pause;
				for (Node& node : nodes) 
				{
					node.angle = 0;
				}
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q)
			{
				modeRope = modeRope ? 0 : 1;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::E)
			{
				modeNode += 1;
				if (modeNode > 2) modeNode = 0;
				resetActivateNodes(nodes);
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
			{
				isDragging = false;
				modeAction += 1;
				if (modeAction > 2) modeAction = 0;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::V)
			{
				simulate.saveStruct();
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::L)
			{
				nodes.reserve(countNodes);
				simulate.loadStruct();
				grid = createGrid(window, radiusNode);
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::LAlt)
			{
				modeMouseLeftClick = !modeMouseLeftClick;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::C)
			{
				nodes.clear();
				ropes.clear();

				pause = true;
				modeMouseLeftClick = true;

				modeNode = 0;
				modeRope = 0;
				modeAction = 0;
				idNode = 0;

				nodes.reserve(countNodes);
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Tab)
			{
				for (int i = ropes.size() - 1; i >= 0; i--)
				{
					Vector2i mouseCoor = Mouse::getPosition(window);
					if (ropes[i].activate)
					{

						break;
					}
				}
			}
			else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
				if (modeAction == 0 && modeMouseLeftClick)
				{
					resetActivateNodes(nodes);
					if (nodes.size() == nodes.capacity()) break;
					Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
					nodes.push_back(Node(idNode, imaginaryNode.getPosition().x, imaginaryNode.getPosition().y, radiusNode));
					idNode += 1;
					break;
				}
				for (int i = 0; i < nodes.size(); i++)
				{
					if (nodes[i].clickNode(mouseCoor.x, mouseCoor.y))
					{
						if (!modeMouseLeftClick && modeNode == 1)
						{
							resetActivateNodes(nodes);
							nodes[i].type = nodes[i].type != 1 ? 1 : 0;
							break;
						}
						if (!modeMouseLeftClick && modeNode == 2)
						{
							resetActivateNodes(nodes);
							nodes[i].type = nodes[i].type != 2 ? 2 : 0;
							break;
						}
						if (modeMouseLeftClick && modeAction == 1)
						{
							resetActivateNodes(nodes);
							for (int j = 0; j < ropes.size(); j++)
							{
								if (ropes[j].startNode->id == nodes[i].id || ropes[j].endNode->id == nodes[i].id)
								{
									ropes.erase(ropes.begin() + j);
								}
							}
							nodes.erase(nodes.begin() + i);
							break;
						}
						if (modeMouseLeftClick && modeAction == 2)
						{
							resetActivateNodes(nodes);
							isDragging = true;
							lastMousePos = window.mapPixelToCoords(Mouse::getPosition(window));
							moveNode = &nodes[i];
							break;
						}
						if (!modeMouseLeftClick && selectedNode == -1)
						{
							resetActivateNodes(nodes);
							nodes[i].activate = !nodes[i].activate;
							selectedNode = i;
							break;
						}
						if (!modeMouseLeftClick && nodes[selectedNode] == nodes[i])
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
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				isDragging = false;
			}
		}
		if (!pause && isDragging)
		{
			Vector2f currentMousePos = window.mapPixelToCoords(Mouse::getPosition(window));
			Vector2<double> delta = Vector2<double>(currentMousePos) - moveNode->getPosition();
			double distance = logic::distance(Vector2<double>(moveNode->getPosition()), Vector2<double>(currentMousePos));

			moveNode->forces += delta * distance;

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

		gui.update(modeNode, modeRope, pause, modeAction);
		gui.draw(window);

		Vector2f mouseCoor = window.mapPixelToCoords(Mouse::getPosition(window));
		if (modeAction == 0 && modeMouseLeftClick)
		{
			imaginaryNode.setRadius(radiusNode);
			Vector2f position = Vector2f(std::floor(mouseCoor.x / radiusNode) * radiusNode - radiusNode, std::floor(mouseCoor.y / radiusNode) * radiusNode - radiusNode);
			imaginaryNode.setPosition(position);
			window.draw(imaginaryNode);
		}
		else if (modeAction == 1 && modeMouseLeftClick)
		{
			deleteNode.setSize(Vector2f(2 * radiusNode, 2 * radiusNode));
			deleteNode.setTexture(&textures::cross);
			deleteNode.setPosition(Vector2f(mouseCoor.x - radiusNode, mouseCoor.y - radiusNode));

			window.draw(deleteNode);
		}
		else if (modeAction == 2 && modeMouseLeftClick)
		{
			hand.setSize(Vector2f(2 * radiusNode, 2 * radiusNode));
			hand.setTexture(&textures::hand);
			hand.setPosition(Vector2f(mouseCoor.x - radiusNode, mouseCoor.y - radiusNode));

			window.draw(hand);
		}
		if (!modeMouseLeftClick || ((modeAction == 0 || modeAction == 1) && modeMouseLeftClick))
		{
			cursor.setSize(Vector2f(2 * radiusNode, 2 * radiusNode));
			cursor.setTexture(&textures::cursor);
			cursor.setPosition(Vector2f(mouseCoor.x - radiusNode, mouseCoor.y));

			window.draw(cursor);
		}

		window.display();
	}
}