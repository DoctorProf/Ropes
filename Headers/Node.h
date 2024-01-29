#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

class Rope;

class Node
{
public:

	//Node();

	Node(int id, double x, double y, int radius);

	Vector2<double> getPosition();

	void draw(RenderWindow& window);

	bool clickNode(double x, double y);

	bool operator==(const Node& other) const;

	void update(double dt);

	void updateDerivatives(double dt);

	void move(Vector2<double> vec);

	int id;

	float radius;
	double angle;

	Vector2<double> position;
	Vector2<double> position_old;
	Vector2<double> velocity;
	Vector2<double> forces;

	bool activate;
	int type;

private:

	CircleShape node;
};