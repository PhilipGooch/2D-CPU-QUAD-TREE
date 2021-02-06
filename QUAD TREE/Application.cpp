#include "Application.h"
#include <random>

Application::Application(RenderWindow* window) :
	window_(window),
	running_(true),
	fps_(-1),
	environment_width_(WINDOW_WIDTH),
	environment_height_(WINDOW_HEIGHT),
	number_of_particles_(10000)
{
	window->setFramerateLimit(60);

	// Setting up fps text for rendering.
	fps_font_.loadFromFile("arial.ttf");
	fps_text_.setString(to_string(fps_));
	fps_text_.setCharacterSize(30);
	fps_text_.setPosition(environment_width_ - 80, 20);
	fps_text_.setFillColor(sf::Color::White);
	fps_text_.setFont(fps_font_);

	quad_tree_ = new QuadTree(Rectangle(0, 0, 512, 512), 4);

	rectangle_.dimensions_ = sf::Vector2f(100, 100);
	circle_.radius_ = 2;


	srand(0);
	//srand(time(nullptr));

	particles_.reserve(number_of_particles_);
	for (int i = 0; i < number_of_particles_; i++)
	{
		int x = rand() % environment_width_;
		int y = rand() % environment_height_;
		particles_.push_back(Particle(x, y));
		vertices_.push_back(Vertex(Vector2f(x, y), sf::Color::Red));
	}
}

Application::~Application()
{
}

void Application::run()
{
	// Variables for calculating frames per second.
	Clock clock;
	Time fps_timer = Time::Zero;	
	int frames = 0;				

	// Application loop.
	while (running_)
	{
		// Queery relevant Windows input messages.
		Event event;
		while (window_->pollEvent(event))
		{
			switch (event.type)
			{
			// If the X symbol in top right is clicked, exit application.
			case Event::Closed:
				running_ = false;
				break;
			// If a key is pressed, tell input manager what key has been pressed.
			case Event::KeyPressed:
				input_.setKeyDown(event.key.code);
				break;
			// If a key is released, tell input manager what key has been released.
			case Event::KeyReleased:
				input_.setKeyUp(event.key.code);
				break;
			// If a mouse button is pressed, tell input manager what mouse button has been pressed.
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input_.setMouseLeftDown(true);
				}
				break;
			// If a mouse button is released, tell input manager what mouse button has been released.
			case Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input_.setMouseLeftDown(false);
				}
				break;
			// If the mouse is moved, tell input manager the new coordinates of the mouse.
			case Event::MouseMoved:
				input_.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			default:
				break;
			}
		}
		// Calculate frames per second.
		Time delta_time = clock.restart();
		fps_timer += delta_time;
		frames++;
		if (fps_timer > sf::seconds(0.2f))
		{
			fps_ = frames * 5;
			frames = 0;
			fps_timer -= sf::seconds(0.2f);
		}
		handleInput();
		update();
		render();
	}
	window_->close();
}

void Application::handleInput()
{
	// If ESCAPE is pressed, exit the application.
	if (input_.getKeyDown(Keyboard::Escape))
	{
		running_ = false;
	}
}

void Application::update()
{
	quad_tree_->release();
	delete quad_tree_;
	quad_tree_ = new QuadTree(Rectangle(0, 0, 512, 512), 4);
	for (Particle& particle : particles_)
	{
		particle.update();
		quad_tree_->insert(&particle);
	}
	for (int i = 0; i < vertices_.size(); i++)
	{
		vertices_[i].position = particles_[i].position_;
	}
	/*sf::Vector2i mouse_position = input_.getMousePosition();
	rectangle_.position_ = sf::Vector2f(mouse_position.x, mouse_position.y);
	circle_.position_ = sf::Vector2f(mouse_position.x, mouse_position.y);
	std::vector<Particle*> particles = quad_tree_->query(circle_);
	highlighted_vertices_.clear();
	for (Particle* particle : particles)
	{
		highlighted_vertices_.push_back(Vertex(Vector2f(particle->position_.x, particle->position_.y), sf::Color::Green));
	}*/
	highlighted_vertices_.clear();
	for (Particle& particle : particles_)
	{
		circle_.position_ = particle.position_;
		std::vector<Particle*> other_particles = quad_tree_->query(circle_);

		for (Particle* other : other_particles)
		{
			if (&particle != other)
			{
				if (particle.intersects(*other))
				{
					highlighted_vertices_.push_back(Vertex(Vector2f(particle.position_.x, particle.position_.y), sf::Color::Green));
				}
			}
		}
	}
}

void Application::render()
{
	window_->clear(Color::Black);

	//quad_tree_->render(window_);

	//sf::RectangleShape rectangle;
	//rectangle.setOutlineColor(sf::Color(100, 100, 100));
	//rectangle.setOutlineThickness(1);
	//rectangle.setFillColor(sf::Color::Transparent);
	//rectangle.setSize(rectangle_.dimensions_);
	//rectangle.setPosition(rectangle_.position_);
	//window_->draw(rectangle);

	window_->draw(&vertices_[0], vertices_.size(), sf::Points);
	if (highlighted_vertices_.size() > 0)
	{
		window_->draw(&highlighted_vertices_[0], highlighted_vertices_.size(), sf::Points);
	}

	/*sf::CircleShape circle;
	circle.setFillColor(sf::Color::White);
	circle.setRadius(2.5);
	for (sf::Vertex vertex : vertices_)
	{
		circle.setPosition(vertex.position);
		window_->draw(circle);
	}
	circle.setFillColor(sf::Color::Green);
	for (sf::Vertex vertex : highlighted_vertices_)
	{
		circle.setPosition(vertex.position);
		window_->draw(circle);
	}*/


	


	// fps is not calculated until 0.2 seconds in so dont display it until then.
	if (fps_ >= 0)
	{
		fps_text_.setFillColor(sf::Color::Blue);
		fps_text_.setString(to_string(fps_));
		window_->draw(fps_text_);
	}

	window_->display();
}
