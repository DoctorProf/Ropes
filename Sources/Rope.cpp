
#include "../Headers/Rope.h"

Rope::Rope() = default;

Rope::Rope(Node* startNode, Node* endNode, double distance, int type)
{
	this->startNode = startNode;
	this->endNode = endNode;
	this->distance = distance;
	this->type = type;
	rope.setPointCount(4);
	this->maxSize = distance;
	this->minSize = 0;
	if (!type)
	{
		this->ropeFont.loadFromFile(textures::steelBeam);
	}
	else
	{
		this->ropeFont.loadFromFile(textures::rope);
	}
}

bool Rope::clickRope(Vector2f mouseCoor)
{
	FloatRect ropeBounds = rope.getGlobalBounds();
	return ropeBounds.contains(mouseCoor);
}

void Rope::draw(RenderWindow& window)
{
	double halfRadius = startNode->radius / 2.f;

	Vector2<double> vectorEndToStart = startNode->getPosition() - endNode->getPosition();
	Vector2<double> vectorStartToEnd = endNode->getPosition() - startNode->getPosition();

	Vector2<double> normalizedVecEndToStart = vectorEndToStart / std::sqrt(vectorEndToStart.x * vectorEndToStart.x +
		vectorEndToStart.y * vectorEndToStart.y);

	Vector2<double> perpendicularVecEndToStart = { -normalizedVecEndToStart.y, normalizedVecEndToStart.x };

	Vector2<double> normalizedVecStartToEnd = vectorStartToEnd / std::sqrt(vectorStartToEnd.x * vectorStartToEnd.x +
		vectorStartToEnd.y * vectorStartToEnd.y);

	Vector2<double> perpendicularVecStartToEnd = { -normalizedVecStartToEnd.y, normalizedVecStartToEnd.x };

	rope.setPoint(3, Vector2f(startNode->getPosition() + perpendicularVecEndToStart * halfRadius));
	rope.setPoint(1, Vector2f(endNode->getPosition() + perpendicularVecStartToEnd * halfRadius));
	rope.setPoint(2, Vector2f(endNode->getPosition() - perpendicularVecStartToEnd * halfRadius));
	rope.setPoint(0, Vector2f(startNode->getPosition() - perpendicularVecEndToStart * halfRadius));

	rope.setFillColor(Color::White);
	if (activate) rope.setFillColor(Color::Blue);
	rope.setTexture(&ropeFont);
	window.draw(rope);
}