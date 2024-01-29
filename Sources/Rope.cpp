
#include "../Headers/Rope.h"

Rope::Rope(int idStartNode, int idEndNode, double distance, int type)
{
	this->idStartNode = idStartNode;
	this->idEndNode = idEndNode;
	this->distance = distance;
	this->type = type;

	rope.setPointCount(4);

	this->maxSize = distance;
	this->minSize = 0;

	if (!type)
	{
		this->ropeFont = textures::steelBeam;
	}
	else
	{
		this->ropeFont = textures::rope;	
	}
}

bool Rope::clickRope(Vector2f mouseCoor)
{
	FloatRect ropeBounds = rope.getGlobalBounds();
	return ropeBounds.contains(mouseCoor);
}

void Rope::draw(RenderWindow& window, std::vector<Node>& nodes)
{
	int idStart = this->idStartNode;
	auto start = std::find_if(nodes.begin(), nodes.end(), [idStart](Node& node)
		{
			return node.id == idStart;
		});
	Node& startNode = *start;

	int idEnd = this->idEndNode;
	auto end = std::find_if(nodes.begin(), nodes.end(), [idEnd](Node& node)
		{
			return node.id == idEnd;
		});
	Node& endNode = *end;

	double halfRadius = startNode.radius / 2.f;

	Vector2<double> vectorEndToStart = startNode.getPosition() - endNode.getPosition();
	Vector2<double> vectorStartToEnd = endNode.getPosition() - startNode.getPosition();

	Vector2<double> normalizedVecEndToStart = vectorEndToStart / std::sqrt(vectorEndToStart.x * vectorEndToStart.x +
		vectorEndToStart.y * vectorEndToStart.y);

	Vector2<double> perpendicularVecEndToStart = { -normalizedVecEndToStart.y, normalizedVecEndToStart.x };

	Vector2<double> normalizedVecStartToEnd = vectorStartToEnd / std::sqrt(vectorStartToEnd.x * vectorStartToEnd.x +
		vectorStartToEnd.y * vectorStartToEnd.y);

	Vector2<double> perpendicularVecStartToEnd = { -normalizedVecStartToEnd.y, normalizedVecStartToEnd.x };

	rope.setPoint(3, Vector2f(startNode.getPosition() + perpendicularVecEndToStart * halfRadius));
	rope.setPoint(1, Vector2f(endNode.getPosition() + perpendicularVecStartToEnd * halfRadius));
	rope.setPoint(2, Vector2f(endNode.getPosition() - perpendicularVecStartToEnd * halfRadius));
	rope.setPoint(0, Vector2f(startNode.getPosition() - perpendicularVecEndToStart * halfRadius));

	rope.setFillColor(Color::White);
	if (activate) rope.setFillColor(Color::Blue);
	rope.setTexture(&ropeFont);
	window.draw(rope);
}
bool Rope::operator==(const Rope& other) const
{
	return (idStartNode == other.idStartNode) &&
		(idEndNode == other.idEndNode) &&
		(distance == other.distance) &&
		(type == other.type);
}

Rope& Rope::operator=(const Rope& other) {
	if (this != &other)
	{
		distance = other.distance;
		type = other.type;
		minSize = other.minSize;
		maxSize = other.maxSize;
	}
	return *this;
}