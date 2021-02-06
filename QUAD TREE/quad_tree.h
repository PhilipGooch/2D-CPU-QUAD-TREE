#pragma once
#include "rectangle.h"
#include "particle.h"
#include <vector>
#include <SFML/Graphics.hpp>

class QuadTree
{
public:
	QuadTree(Rectangle rectangle, int capacity);
	~QuadTree();

	void insert(Particle* particle);
	void subdivide();
	std::vector<Particle*> query(Circle circle);
	std::vector<Particle*> query(Rectangle rectangle);
	void render(sf::RenderWindow* window);
	void release();

	Rectangle rectangle_;
	int capacity_;
	bool divided_;
	std::vector<Particle*> particles_;
	QuadTree* top_left_;
	QuadTree* top_right_;
	QuadTree* bottom_left_;
	QuadTree* bottom_right_;
};

