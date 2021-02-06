#pragma once
#include "particle.h"
#include <SFML/System/Vector2.hpp>

class Circle
{
public:
	Circle();
	Circle(float x, float y, float r);

	bool contains(Particle* particle);
	bool intersects(Circle circle);

	sf::Vector2f position_;
	float radius_;
};

