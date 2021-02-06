#pragma once
#include "particle.h"
#include "circle.h"
#include <SFML/System/Vector2.hpp>

class Rectangle
{
public:
	Rectangle();
	Rectangle(float x, float y, float w, float h);

	bool contains(Particle* particle);
	bool intersects(Rectangle rectangle);
	bool intersects(Circle circle);

	sf::Vector2f position_;
	sf::Vector2f dimensions_;
};

