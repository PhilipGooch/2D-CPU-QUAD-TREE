#include "quad_tree.h"
#include "circle.h"

QuadTree::QuadTree(Rectangle rectangle, int capacity) :
	rectangle_(rectangle),
	capacity_(capacity),
	divided_(false),
	top_left_(nullptr),
	top_right_(nullptr),
	bottom_left_(nullptr),
	bottom_right_(nullptr)
{
}

QuadTree::~QuadTree()
{
}

void QuadTree::insert(Particle* particle)
{
	if (!rectangle_.contains(particle))
	{
		return;
	}
	if (particles_.size() < capacity_)
	{
		particles_.push_back(particle);
	}
	else
	{
		if (!divided_)
		{
			subdivide();
		}
		top_left_->insert(particle);
		top_right_->insert(particle);
		bottom_left_->insert(particle);
		bottom_right_->insert(particle);
	}
}

void QuadTree::subdivide()
{
	int x = rectangle_.position_.x;
	int y = rectangle_.position_.y;
	int w = rectangle_.dimensions_.x;
	int h = rectangle_.dimensions_.y;
	Rectangle top_left    (x,         y,         w / 2, h / 2);
	Rectangle top_right   (x + w / 2, y,         w / 2, h / 2);
	Rectangle bottom_left (x,         y + h / 2, w / 2, h / 2);
	Rectangle bottom_right(x + w / 2, y + h / 2, w / 2, h / 2);
	top_left_ = new QuadTree(top_left, capacity_);
	top_right_ = new QuadTree(top_right, capacity_);
	bottom_left_ = new QuadTree(bottom_left, capacity_);
	bottom_right_ = new QuadTree(bottom_right, capacity_);
	divided_ = true;
}

std::vector<Particle*> QuadTree::query(Circle circle)
{
	std::vector<Particle*> particles;
	if (rectangle_.intersects(circle))
	{
		for (Particle* particle : particles_)
		{
			if (circle.contains(particle))
			{
				particles.push_back(particle);
			}
		}
		if (divided_)
		{
			std::vector<Particle*> top_left_particles = top_left_->query(circle);
			std::vector<Particle*> top_right_particles = top_right_->query(circle);
			std::vector<Particle*> bottom_left_particles = bottom_left_->query(circle);
			std::vector<Particle*> bottom_right_particles = bottom_right_->query(circle);
			particles.insert(particles.end(), top_left_particles.begin(), top_left_particles.end());
			particles.insert(particles.end(), top_right_particles.begin(), top_right_particles.end());
			particles.insert(particles.end(), bottom_left_particles.begin(), bottom_left_particles.end());
			particles.insert(particles.end(), bottom_right_particles.begin(), bottom_right_particles.end());
		}
	}
	return particles;
}

std::vector<Particle*> QuadTree::query(Rectangle rectangle)
{
	std::vector<Particle*> particles;
	if(rectangle_.intersects(rectangle))
	{
		for (Particle* particle : particles_)
		{
			if (rectangle.contains(particle))
			{
				particles.push_back(particle);
			}
		}
		if (divided_)
		{
			std::vector<Particle*> top_left_particles = top_left_->query(rectangle);
			std::vector<Particle*> top_right_particles = top_right_->query(rectangle);
			std::vector<Particle*> bottom_left_particles = bottom_left_->query(rectangle);
			std::vector<Particle*> bottom_right_particles = bottom_right_->query(rectangle);
			particles.insert(particles.end(), top_left_particles.begin(), top_left_particles.end());
			particles.insert(particles.end(), top_right_particles.begin(), top_right_particles.end());
			particles.insert(particles.end(), bottom_left_particles.begin(), bottom_left_particles.end());
			particles.insert(particles.end(), bottom_right_particles.begin(), bottom_right_particles.end());
		}
	}
	return particles;
}

void QuadTree::render(sf::RenderWindow* window)
{
	sf::RectangleShape rectangle;
	rectangle.setOutlineColor(sf::Color(50, 50, 50));
	rectangle.setOutlineThickness(1);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setSize(rectangle_.dimensions_);
	rectangle.setPosition(rectangle_.position_);
	window->draw(rectangle);
	if (divided_)
	{
		top_left_->render(window);
		top_right_->render(window);
		bottom_left_->render(window);
		bottom_right_->render(window);
	}
}

void QuadTree::release()
{
	if (divided_)
	{
		top_left_->release();
		top_right_->release();
		bottom_left_->release();
		bottom_right_->release();
	}
	delete top_left_;
	delete top_right_;
	delete bottom_left_;
	delete bottom_right_;
	particles_.clear();
}
