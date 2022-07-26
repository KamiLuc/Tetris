#include "Tetris.h"
#include "Tetroid.h"
#include <SFML/Graphics.hpp>
#include <ranges>
#include <set>
#include <iostream>

using namespace tetris;

Tetris::Tetris(const sf::Vector2f& on_screen_pos, int board_x_size, int board_y_size, float cell_size, Level_delay_score_calculator* calculator, const sf::Color& default_cell_color, const std::string& font_name) :
	cell_size(cell_size),
	size_x(board_x_size),
	size_y(board_y_size),
	default_cell_color(default_cell_color),
	calculator(calculator)
{
	using rectangle_array = std::unique_ptr<sf::RectangleShape[]>;

	board = std::make_unique<rectangle_array[]>(board_x_size);
	next_tetroid_board = std::make_unique<rectangle_array[]>(board_x_size);

	for (int i = 0; i < board_x_size; i++)
	{
		board[i] = std::make_unique<sf::RectangleShape[]>(board_y_size);
		next_tetroid_board[i] = std::make_unique<sf::RectangleShape[]>(board_y_size/3);

		for (int j = 0; j < board_y_size; j++)
		{
			board[i][j].setPosition({ i * cell_size + on_screen_pos.x, j * cell_size + on_screen_pos.y });
			board[i][j].setFillColor(default_cell_color);
			board[i][j].setOrigin({ 0.f,0.f });
			board[i][j].setOutlineColor(sf::Color::Black);
			board[i][j].setOutlineThickness(5.f);
			board[i][j].setSize({ cell_size, cell_size });
		}

		auto adjustment = on_screen_pos.x + (board_x_size + 2) * cell_size;

		for (int j = 0; j < board_y_size/3; j++)
		{
			next_tetroid_board[i][j].setPosition({ i * cell_size + adjustment, j * cell_size + on_screen_pos.y });
			next_tetroid_board[i][j].setFillColor(default_cell_color);
			next_tetroid_board[i][j].setOrigin({ 0.f,0.f });
			next_tetroid_board[i][j].setOutlineColor(sf::Color::Black);
			next_tetroid_board[i][j].setOutlineThickness(5.f);
			next_tetroid_board[i][j].setSize({ cell_size, cell_size });
		}
	}

	if (!text_font.loadFromFile(font_name))
	{
		throw std::exception("FONT NOT LOADED");
	}

	game_info.setFont(text_font);
	game_info.setCharacterSize(55);
	game_info.setPosition(365.f, 200.f);
	game_info.setFillColor(sf::Color::Magenta);
	game_info.setOutlineColor(sf::Color::White);
	game_info.setLetterSpacing(3.f);
	srand(time(NULL));
}

Tetroid Tetris::get_random_tetroid() const 
{
	auto size = available_tetroids.size();
	if (size == 0)
	{
		throw std::runtime_error("There is no available tetroid");
	}

	return available_tetroids[rand() % size];
}

void Tetris::colour_cells(const std::vector<sf::Vector2i>& points, const sf::Color& color)
{
	for (const auto& point : points)
	{
		board[point.x][point.y].setFillColor(color);
	}
}

bool Tetris::check_if_tetroid_is_colliding(const Tetroid& tetroid) const
{
	for (const auto& point : tetroid.get_points())
	{
		for (const auto& cell : taken_cells)
		{
			if (cell.first == point)
			{
				return true;
			}
		}
		if (point.x < 0 || point.y < 0 || point.x >= size_x || point.y >= size_y)
		{
			return true;
		}
	}
	return false;
}

void Tetris::reset() noexcept
{
	tetroid = nullptr;
	fake_tetroid = nullptr;
	next_tetroid = nullptr;
	level = 1;
	lines_completed = 0;
	score = 0;
	free_fall = 0;
	fall_iteration = 0.5;
	next_tetroid_shift = 0;
	for (const auto& point : taken_cells)
	{
		board[point.first.x][point.first.y].setFillColor(default_cell_color);
	}	
	taken_cells.clear();
}

void Tetris::update_fake_tetroid() noexcept
{
	if (fake_tetroid != nullptr)
	{
		auto temp = tetroid->get_points();
		for (const auto& point : fake_tetroid->get_points())
		{
			if (std::find(temp.begin(), temp.end(), point) != temp.end())
			{
				board[point.x][point.y].setFillColor(default_cell_color);
			}
		}
	}

	fake_tetroid = std::make_unique<Tetroid>(*tetroid);
	auto color = tetroid->get_color();
	color.a = 45;
	fake_tetroid->set_color(color);

	auto previous_state = *fake_tetroid;

	while (!check_if_tetroid_is_colliding(*fake_tetroid))
	{
		previous_state = *fake_tetroid;
		fake_tetroid->move_down();
	}
	
	fake_tetroid = std::make_unique<Tetroid>(previous_state);
	colour_cells(previous_state.get_points(), previous_state.get_color());
}

void tetris::Tetris::paint_board() noexcept
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			board[i][j].setFillColor(default_cell_color);
		}
	}

	if (tetroid != nullptr)
	{
		update_fake_tetroid();
		for (const auto& point : tetroid->get_points())
		{
			board[point.x][point.y].setFillColor(tetroid->get_color());
		}
	}

	for (const auto& cell : taken_cells)
	{
		board[cell.first.x][cell.first.y].setFillColor(cell.second);
	}
}

void tetris::Tetris::paint_next_tetroid_board() noexcept
{
	sf::Color color;
	if (check_if_tetroid_is_colliding(*next_tetroid))
	{
		color = sf::Color::White;
	}
	else
	{
		color = next_tetroid->get_color();
	}

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y/3; j++)
		{
			next_tetroid_board[i][j].setFillColor(default_cell_color);
		}
	}

	for (const auto& point : next_tetroid->get_points())
	{
		next_tetroid_board[point.x][point.y].setFillColor(color);
	}

	for (const auto& cell : taken_cells)
	{
		if (cell.first.y < size_y / 3)
		{
			next_tetroid_board[cell.first.x][cell.first.y].setFillColor(sf::Color::White);
		}
	}
}

void tetris::Tetris::destroy_tetroid() noexcept
{
	auto points = tetroid->get_points();
	auto color = tetroid->get_color();
	for (const auto& point : points)
	{
		taken_cells.push_back({ point, color });
		colour_cells(tetroid->get_points(), tetroid->get_color());
	}
	tetroid = nullptr;
}

unsigned int tetris::Tetris::try_to_clear_lines() noexcept
{
	if (taken_cells.empty())
	{
		return 0;
	}

	taken_cells.sort([](std::pair<sf::Vector2i, sf::Color> a,
		std::pair<sf::Vector2i, sf::Color> b)
		{
			return a.first.y > b.first.y;
		});

	//count taken cells in horizontal line
	int counter = 0;
	auto iterator = taken_cells.cbegin();
	int now_counting = (*iterator).first.y;

	unsigned int lines_cleared = 0;

	while (iterator != taken_cells.cend())
	{
		if ((*iterator).first.y != now_counting)
		{
			now_counting = (*iterator).first.y;
			counter = 1;
		}
		else
		{
			counter++;
		}

		if (counter == size_x)
		{
			taken_cells.remove_if([now_counting](const std::pair<sf::Vector2i, sf::Color>& a) 
				{ return a.first.y == now_counting; });

			for (auto& cell : taken_cells)
			{
				if (cell.first.y < now_counting)
				{
					cell.first.y++;
				}
			}

			if (!taken_cells.empty())
			{
				iterator = taken_cells.begin();
				now_counting = (*iterator).first.y;
				counter = 1;
			}

			lines_cleared++;
		}
		iterator++;
	}

	return lines_cleared;
}

void tetris::Tetris::update_game_info() noexcept
{
	std::string temp{ "SCORE\n" };
	temp += std::to_string(score);
	temp += "\nLINES\nCLEARED\n";
	temp += std::to_string(lines_completed);
	temp += "\nLEVEL\n";
	temp += std::to_string(level);

	game_info.setString(temp);
}

bool Tetris::move_tetroid_down()
{
	auto copy = *tetroid;
	copy.move_down();

	if (check_if_tetroid_is_colliding(copy))
	{
		return false;
	}

	tetroid->move_down();
	return true;
}

void tetris::Tetris::shift_next_tetroid()
{
	int shift = next_tetroid_shift;

	if (shift < 0)
	{
		shift = std::abs(shift);
		for (int i = 0; i < shift; i++)
		{
			move_next_tetroid_left();
		}
	}
	else
	{
		for (int i = 0; i < shift; i++)
		{
			move_next_tetroid_right();
		}
	}
}

void tetris::Tetris::update_level_iteration_score() noexcept
{
	level = calculator->calculate_level(lines_completed);
	fall_iteration = calculator->calculate_iteration_time(level);
	score += calculator->calculate_point_award(level, free_fall);
}

void Tetris::add_new_tetroid(std::vector<std::vector<sf::Vector2i>>&& tetroid_cell_states, const sf::Color& tetroid_color)
{
	available_tetroids.push_back(std::move(Tetroid({ size_x / 2 - 1,0}, tetroid_color, std::move(tetroid_cell_states))));
}

void Tetris::add_new_tetroid(const std::vector<std::vector<sf::Vector2i>>& tetroid_cell_states, const sf::Color& tetroid_color)
{
	available_tetroids.push_back(std::move(Tetroid({ size_x / 2 - 1,0}, tetroid_color, tetroid_cell_states)));
}

bool Tetris::move_tetroid_left()
{
	auto copy = *tetroid;
	copy.move_left();

	if (check_if_tetroid_is_colliding(copy))
	{
		return false;
	}

	tetroid->move_left();
	return true;
}

bool Tetris::move_tetroid_right()
{
	auto copy = *tetroid;
	copy.move_right();

	if (check_if_tetroid_is_colliding(copy))
	{
		return false;
	}

	tetroid->move_right();
	return true;
}

bool tetris::Tetris::move_next_tetroid_left()
{
	auto copy = *next_tetroid;
	copy.move_left();

	for (const auto& point : copy.get_points())
	{
		if (point.x < 0)
		{
			return false;
		}
	}

	next_tetroid->move_left();
	return true;
}

bool tetris::Tetris::move_next_tetroid_right()
{
	auto copy = *next_tetroid;
	copy.move_right();

	for (const auto& point : copy.get_points())
	{
		if (point.x >= size_x)
		{
			return false;
		}
	}

	next_tetroid->move_right();
	return true;
}

void Tetris::drop_tetroid()
{
	while (move_tetroid_down())
	{
		//that's all, it works
	}
}

bool Tetris::rotate_tetroid_left()
{
	auto copy = *tetroid;
	copy.rotate_left();

	if (check_if_tetroid_is_colliding(copy))
	{
		return false;
	}

	tetroid->rotate_left();
	return true;
}

bool Tetris::rotate_tetroid_right() 
{
	auto copy = *tetroid;
	copy.rotate_right();

	if (check_if_tetroid_is_colliding(copy))
	{
		return false;
	}

	tetroid->rotate_right();
	return true;
}

void tetris::Tetris::update(Action action)
{
	//this is true only at first update
	if (next_tetroid == nullptr)
	{
		update_game_info();
		next_tetroid = std::make_unique<Tetroid>(get_random_tetroid());
		shift_next_tetroid();
	}

	//if there is no falling tetroid, creates one
	if (tetroid == nullptr)
	{
		auto temp_tetroid = *next_tetroid;
		tetroid = std::make_unique<Tetroid>(temp_tetroid);
		free_fall = 0;
		next_tetroid = std::make_unique<Tetroid>(get_random_tetroid());
		shift_next_tetroid();
		if (check_if_tetroid_is_colliding(*tetroid))
		{
			reset();
			return;
		}
	}

	else
	{
		if (action == Action::move_tetroid_down or action == Action::drop_tetroid)
		{
			if (action == Action::move_tetroid_down)
			{
				move_tetroid_down();
				free_fall++;
			}
			else
			{
				drop_tetroid();
			}

			//check if ater move down, tetroid will collide
			auto copy = *tetroid;
			copy.move_down();
			if (check_if_tetroid_is_colliding(copy))
			{
				destroy_tetroid();
				update_level_iteration_score();
				lines_completed += try_to_clear_lines();
				update_game_info();
				tetroid = nullptr;
			}
		}
		else if (action == Action::move_tetroid_left)
		{
			move_tetroid_left();
		}
		else if (action == Action::move_tetroid_right)
		{
			move_tetroid_right();
		}
		else if (action == Action::rotate_tetroid_left)
		{
			rotate_tetroid_left();
		}
		else if (action == Action::rotate_tetroid_right)
		{
			rotate_tetroid_right();
		}
		else if (action == Action::move_next_tetroid_left)
		{
			if (move_next_tetroid_left())
				next_tetroid_shift--;
		}
		else if (action == Action::move_next_tetroid_right)
		{

			if (move_next_tetroid_right())
				next_tetroid_shift++;
		}
	}
	paint_board();
	paint_next_tetroid_board();
}

void Tetris::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			target.draw(board[i][j], states);
		}
	}

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y/3; j++)
		{
			target.draw(next_tetroid_board[i][j], states);
		}
	}

	target.draw(game_info, states);
}
