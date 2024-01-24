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
		position = Vector2<double>(x - radius, y - radius);
		node.setRadius(radius);
		node.setPosition(Vector2f(position));
		node.setPointCount(50);
		isStatic = false;
		activate = false;
	}

	Vector2<double> getPosition()
	{
		return position + Vector2<double>(radius, radius);
	}

	void draw(RenderWindow& window)
	{
		node.setFillColor(Color::White);
		if (isStatic) node.setFillColor(Color::Red);
		if (activate) node.setFillColor(Color::Green);
		node.setPosition(Vector2f(position));
		window.draw(node);
	}

	bool clickNode(double x, double y)
	{
		Vector2<double> centerPos = getPosition();
		return (pow(centerPos.x - x, 2) + pow(centerPos.y - y, 2)) <= pow(radius, 2);
	}

	bool operator==(const Node& other) const
	{
		return (radius == other.radius) && (isStatic == other.isStatic) && (activate == other.activate);
	}
	void update(double dt)
	{
		if (isStatic) return;
		position_old = position;
		velocity += forces * dt;
		position += velocity * dt;
	}

	void updateDerivatives(double dt)
	{
		velocity = (position - position_old) / dt;
		forces = {};
	}

	void move(Vector2<double> vec)
	{
		if (isStatic) return;
		position += vec;
	}
	float radius;
	float mass;

	Vector2<double> position;
	Vector2<double> position_old;
	Vector2<double> velocity;
	Vector2<double> forces;

	bool isStatic;
	bool activate;

private:
	CircleShape node;
};
