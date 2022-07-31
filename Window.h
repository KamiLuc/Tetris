#pragma once
#include <SFML/Graphics.hpp>

class Window
{
private:
	sf::RenderWindow window;
	void setup(const char* title, const sf::Vector2u& size);
	void destroy() { window.close(); }
	void create();

	sf::Vector2u window_size;
	std::string window_title;
	bool b_done;
	bool b_fullscreen;
public:
	Window() { setup("Window", { 640,480 }); }
	Window(const char* title, const sf::Vector2u& size) { setup(title, size); }
	~Window() { window.close(); };
	void begin_draw() { window.clear(sf::Color::Black); };
	void end_draw() { window.display(); };

	void update();
	bool is_done() noexcept { return b_done; } 
	bool is_fullscreen() noexcept { return b_fullscreen; }
	sf::Vector2u get_window_size() const noexcept { return window.getSize(); }
	void toggle_fullscreen();
	void draw(sf::Drawable& drawable);
};