#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>

using namespace sf;

namespace logic
{
	double dot(Vector2<double> firstVec, Vector2<double> seconfVec);

	double distance(Vector2<double> vec1, Vector2<double> vec2);
}