module;

#include <iostream>
#include "SFML/Graphics.hpp"

import Logic;
using namespace sf;

export module Node;

export class Node
{
public:
	static struct Neighbor
	{
	private:
		Node* node;
		double distanceTo;
	public:
		Neighbor(Node* node, double distanceTo)
		{
			this->node = node;
			this->distanceTo = distanceTo;
		}

		Node* getNode()
		{
			return node;
		}
		double getDistanceTo()
		{
			return distanceTo;
		}
	};

	Node() = default;

	Node(double x, double y)
	{
		radius = 10;
		mass = 1.0f;
		position = Vector2f(x - radius, y - radius);
		node.setRadius(radius);
		node.setPosition(position);
		node.setPointCount(50);
		isStatic = false;
		activate = false;
	}

	Vector2f getPosition()
	{
		Vector2f centerPos = node.getPosition() + Vector2f(radius, radius);
		return Vector2f(centerPos.x, centerPos.y);
	}

	void draw(RenderWindow& window)
	{
		node.setFillColor(Color::White);
		if (isStatic) node.setFillColor(Color::Red);
		if (activate) node.setFillColor(Color::Green);
		node.setPosition(position);
		window.draw(node);
	}

	bool clickNode(double x, double y)
	{
		Vector2f centerPos = node.getPosition() + Vector2f(radius, radius);
		return (pow(centerPos.x - x, 2) + pow(centerPos.y - y, 2)) <= pow(radius, 2);
	}

	bool operator==(const Node& other) const
	{
		return (radius == other.radius) && (isStatic == other.isStatic) && (activate == other.activate);
	}

	void move(Vector2f vec)
	{
		if (!isStatic) return;
		position += vec;
	}

	float radius;
	float mass;

	Vector2f position;
	Vector2f velocity;
	Vector2f forces;

	bool isStatic;
	bool activate;

private:
	CircleShape node;

};
