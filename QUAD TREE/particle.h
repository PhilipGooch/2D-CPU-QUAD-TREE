#pragma once
#include <SFML/System/Vector2.hpp>

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

class Particle
{
public:
	Particle(float x, float y);

	void update();
	bool intersects(Particle& other);

	sf::Vector2f position_;
	sf::Vector2f velocity_;
	float radius_;

};

