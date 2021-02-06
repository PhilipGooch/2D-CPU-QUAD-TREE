#include "particle.h"
#include <random>

Particle::Particle(float x, float y)
{
	position_.x = x;
	position_.y = y;
	velocity_.x = (float)(rand() % 200 - 100) / 100;
	velocity_.y = (float)(rand() % 200 - 100) / 100;
	radius_ = 1;
}

void Particle::update()
{
	//velocity_.x = (float)(rand() % 200 - 100) / 100;
	//velocity_.y = (float)(rand() % 200 - 100) / 100;

	position_ += velocity_;

	if (position_.x < 0)
	{
		position_.x += WINDOW_WIDTH;
	}
	if (position_.x > WINDOW_WIDTH)
	{
		position_.x -= WINDOW_WIDTH;
	}
	if (position_.y < 0)
	{
		position_.y += WINDOW_HEIGHT;
	}
	if (position_.y > WINDOW_HEIGHT)
	{
		position_.y -= WINDOW_HEIGHT;
	}
}

bool Particle::intersects(Particle& other)
{
	return (pow((other.position_.x - position_.x), 2) + pow((other.position_.y - position_.y), 2) <= pow(radius_ + other.radius_, 2));
}
