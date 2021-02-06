#include "rectangle.h"
#include <math.h>

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(float x, float y, float w, float h)
{
	position_.x = x;
	position_.y = y;
	dimensions_.x = w;
	dimensions_.y = h;
}

bool Rectangle::contains(Particle* particle)
{
	return (particle->position_.x >= position_.x &&
		    particle->position_.x < position_.x + dimensions_.x &&
		    particle->position_.y >= position_.y &&
		    particle->position_.y < position_.y + dimensions_.y);
}

bool Rectangle::intersects(Rectangle rectangle)
{
	return !(rectangle.position_.x >= position_.x + dimensions_.x ||
		     rectangle.position_.x + rectangle.dimensions_.x < position_.x ||
		     rectangle.position_.y >= position_.y + dimensions_.y ||
		     rectangle.position_.y + rectangle.dimensions_.y < position_.y);
}

bool Rectangle::intersects(Circle circle)
{
	sf::Vector2f r = sf::Vector2f(dimensions_.x / 2, dimensions_.y / 2);
	sf::Vector2f p = circle.position_ - (position_ + r);

	float d = pow(fmax(fabsf(p.x) - r.x, 0), 2) + pow(fmax(fabsf(p.y) - r.y, 0), 2);

	return d <= circle.radius_ * circle.radius_;
}