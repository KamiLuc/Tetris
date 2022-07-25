#pragma once
#include <SFML/Graphics.hpp>

namespace tetris
{

	/*

		0,0 0,1 0,2
		1,0 1,1 1,2
		2,0 2,1 2,2

	*/

	class Tetroid
	{
	private:
		sf::Color color;
		int next_transformation;
		std::vector<std::vector<sf::Vector2i>> transformations;
		std::vector<sf::Vector2i> points;
	public:
		Tetroid(sf::Vector2i board_start_pos, const sf::Color& tetroid_color, const std::vector<std::vector<sf::Vector2i>>& cells_states);
		void move_down() noexcept;
		void move_left() noexcept;
		void move_right() noexcept;
		void rotate_left();
		void rotate_right();
		sf::Color get_color() const noexcept;
		void set_color(const sf::Color& new_color) { color = new_color; }
		std::vector<sf::Vector2i> get_points() const noexcept;
	};

};