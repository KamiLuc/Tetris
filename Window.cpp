#include "Window.h"

void Window::setup(const char* title, const sf::Vector2u& size)
{
	window_title = title;
	window_size = size;
	fullscreen = false;
	done = false;

	create();
}

void Window::create()
{
	auto style = (fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	window.create({ window_size.x, window_size.y, 32 }, window_title, style);
}

void Window::update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			done = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			toggle_fullscreen();
		}
	}
}

void Window::toggle_fullscreen()
{
	fullscreen != fullscreen;
	destroy();
	create();
}

void Window::draw(sf::Drawable& drawable)
{
	window.draw(drawable);
}
