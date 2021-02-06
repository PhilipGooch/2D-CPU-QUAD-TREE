#pragma once
#include "input.h"
#include "quad_tree.h"
#include "rectangle.h"
#include "circle.h"
#include "particle.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const float PI = 3.141592653589793239f;	// Max precision.

class Application
{
public:
	Application(RenderWindow* window);
	~Application();

public:
	// Application loop.
	void run();

private:
	void handleInput(); 
	void update();
	void render();		

	RenderWindow* window_;		// SFML object for handling the creation of a window to work in.
	Input input_;				// Input handler class.
	bool running_;				// If false, the application will close.
	int fps_;					// Frames per second.
	int environment_width_;		// Environment refers to the rectangle the particles exist in.
	int environment_height_;		// Environment refers to the rectangle the particles exist in.

	Font fps_font_;		// SFML object that stores a .ttf file describing a font.
	Text fps_text_;		// SFML object for rendering fps string.

	vector<Particle> particles_;		// All particles.
	vector<Vertex> vertices_;		    // A vertex for every particle. 
	vector<Vertex> highlighted_vertices_;
		
	const int number_of_particles_;		// Number of particles in the SPH simulation.

	QuadTree* quad_tree_;

	Rectangle rectangle_;
	Circle circle_;
};

