#pragma once

#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Tetroid.h"
#include <list>

namespace tetris
{

	class Tetris : public sf::Drawable
	{
	private:

		const float cell_size;
		const int size_x;
		const int size_y;
		const sf::Color default_cell_color;
		unsigned int auto_update_time;
		std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]> board;
		std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]> next_tetroid_board;
		std::unique_ptr<Tetroid> tetroid;
		std::unique_ptr<Tetroid> fake_tetroid;
		std::unique_ptr<Tetroid> next_tetroid;
		std::list<std::pair<sf::Vector2i, sf::Color>> taken_cells;
		std::vector<Tetroid> available_tetroids;

		Tetroid get_random_tetroid() const;
		void colour_cells(const std::vector<sf::Vector2i>& points, const sf::Color& color);
		bool check_if_tetroid_is_colliding(const Tetroid& tetroid) const;
		void update_fake_tetroid() noexcept;
		void paint_board() noexcept;
		void paint_next_tetroid_board() noexcept;
		void destroy_tetroid() noexcept;
		void try_to_clear_lines() noexcept;

		//TETROID MOVE METHODS/////////////////////////////////////////
		bool move_tetroid_left();
		bool move_tetroid_right();
		bool move_next_tetroid_left();
		bool move_next_tetroid_right();
		void drop_tetroid();
		bool rotate_tetroid_left();
		bool rotate_tetroid_right();
		bool move_tetroid_down();
		
		int next_tetroid_shift = 0;
		void shift_next_tetroid();
		///////////////////////////////////////////////////////////////

	public:
		Tetris(const sf::Vector2f& on_screen_pos, int board_x_size, int board_y_size, float cell_size,double auto_update_time, const sf::Color& default_cell_color = sf::Color::White);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void reset() noexcept;
		auto get_board_start_position(void) const noexcept { return board[0][0].getPosition(); }
		void add_new_tetroid(std::vector<std::vector<sf::Vector2i>>&& tetroid_cell_states, const sf::Color& tetroid_color);
		void add_new_tetroid(const std::vector<std::vector<sf::Vector2i>>& tetroid_cell_states, const sf::Color& tetroid_color);
		enum class Action
		{
			move_tetroid_down,
			move_tetroid_left,
			move_tetroid_right,
			rotate_tetroid_left,
			rotate_tetroid_right,
			drop_tetroid,
			move_next_tetroid_left,
			move_next_tetroid_right
		};
		auto get_auto_update_time() const noexcept { return auto_update_time; }
		void update(Action action);
	};
};