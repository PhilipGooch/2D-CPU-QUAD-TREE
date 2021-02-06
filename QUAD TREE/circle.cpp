#include "circle.h"
#include <math.h>

Circle::Circle()
{
}

Circle::Circle(float x, float y, float r)
{
	position_.x = x;
	position_.y = y;
	radius_ = r;
}

bool Circle::contains(Particle* particle)
{
	return (pow((particle->position_.x - position_.x), 2) + pow((particle->position_.y - position_.y), 2) <= pow(radius_, 2));
}

bool Circle::intersects(Circle circle)
{
	return (pow((circle.position_.x - position_.x), 2) + pow((circle.position_.y - position_.y), 2) <= pow(radius_ + circle.radius_, 2));
}
