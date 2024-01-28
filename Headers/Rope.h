#pragma once

#include "Node.h"
#include "Texture.h"

using namespace sf;

class Rope
{
public:
	Node* startNode;
	Node* endNode;
	double distance;
	bool activate;
	ConvexShape rope;
	int type;
	double maxSize;
	double minSize;

	Texture ropeFont;
	Texture steelBeamFont;

	Rope();

	Rope(Node* startNode, Node* endNode, double distance, int type);

	bool clickRope(Vector2f mouseCoor);

	void draw(RenderWindow& window);
};