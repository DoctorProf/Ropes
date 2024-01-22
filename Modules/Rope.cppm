module;

#include <iostream>
#include "SFML/Graphics.hpp"

import Node;

using namespace sf;

export module Rope;

export class Rope 
{
public:
	Node* startNode;
	Node* endNode;
	float distance;

	Rope(Node* startNode, Node* endNode, float distance) 
	{
		this->startNode = startNode;
		this->endNode = endNode;
		this->distance = distance;
	}
	void draw(RenderWindow& window)
	{
		VertexArray line;
		line.setPrimitiveType(Lines);

		Vertex startPoint;
		Vertex endPoint;

		startPoint.color = Color::White;
		endPoint.color = Color::White;

		startPoint.position = startNode->getPosition();
		endPoint.position = endNode->getPosition();

		line.append(startPoint);
		line.append(endPoint);

		window.draw(line);
	}
};
