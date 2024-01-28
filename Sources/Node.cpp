
#include "../Headers/Node.h"

Node::Node() = default;

Node::Node(int id, double x, double y, int radius)
{
	this->id = id;
	this->radius = radius;
	position = Vector2<double>(x, y);
	node.setRadius(radius);
	node.setPosition(Vector2f(position));
	node.setPointCount(50);
	activate = false;
	angle = 0;
	type = 0;
}

Vector2<double> Node::getPosition()
{
	return position + Vector2<double>(radius, radius);
}

void Node::draw(RenderWindow& window)
{
	node.setFillColor(Color::White);
	if (type == 1) node.setFillColor(Color::Red);
	if (type == 2) node.setFillColor(Color::Blue);
	if (activate) node.setFillColor(Color::Green);

	node.setPosition(Vector2f(position));
	window.draw(node);
}

bool Node::clickNode(double x, double y)
{
	Vector2<double> centerPos = getPosition();
	return (pow(centerPos.x - x, 2) + pow(centerPos.y - y, 2)) <= pow(radius, 2);
}

bool Node::operator==(const Node& other) const
{
	return (radius == other.radius) && (type == other.type) && (activate == other.activate) && (id == other.id);
}

void Node::update(double dt)
{
	if (type == 1) return;
	position_old = position;
	velocity += forces * dt;
	position += velocity * dt;
	angle = angle > 6.28 ? 0 : angle;
}

void Node::updateDerivatives(double dt)
{
	velocity = (position - position_old) / dt;
	forces = {};
}

void Node::move(Vector2<double> vec)
{
	if (type == 1) return;
	position += vec;
}