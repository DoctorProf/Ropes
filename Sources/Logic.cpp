

#include "../Headers/Logic.h"


double logic::dot(Vector2<double> firstVec, Vector2<double> seconfVec)
{
	return firstVec.x * seconfVec.x + firstVec.y * seconfVec.y;
}

double logic::distance(Vector2<double> vec1, Vector2<double> vec2)
{
	double dx = vec1.x - vec2.x;
	double dy = vec1.y - vec2.y;
	return std::sqrt(dx * dx + dy * dy);
}