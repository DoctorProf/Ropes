#pragma once

#include "Node.h"
#include "Texture.h"

using namespace sf;

class Node; 

class Rope
{
public:

	int idStartNode;
	int idEndNode;

	double distance;
	bool activate;

	ConvexShape rope;

	int type;

	double maxSize;
	double minSize;

	Texture ropeFont;
	Texture steelBeamFont;

	Rope(int idStartNode, int idEndNode, double distance, int type);

	bool clickRope(Vector2f mouseCoor);

	void draw(RenderWindow& window, std::vector<Node>& nodes);

	bool operator==(const Rope& other) const;

	Rope& operator=(const Rope& other);
};