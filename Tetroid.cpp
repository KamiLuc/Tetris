#include "Tetroid.h"
#include <iostream>

using namespace tetris;

/*Creates transformation vector with given cell states
* 
* EX:
*		state 0:
*				[1,1], [3,2], [2,3]
*		state 1: 
*				[3,3], [2,1], [1,1]
*		
*		Transformation[0][0] = [3-1,3-1] = [2,2]
*		Transformation[0][1] = [2-3,1-2] = [-1,-1]
*		Transformation[0][2] = [1-2,1-3] = [-1,-2]
*		Transformation[1][0] = [1-3,1-3] = [-2,-2]
*		Transformation[1][1] = [3-2,2-1] = [1,1]
*		Transformation[1][2] = [2-1,1-1] = [1,0]
* 
*/

Tetroid::Tetroid(sf::Vector2i starting_posistion, const sf::Color& tetroid_color, const std::vector<std::vector<sf::Vector2i>>& cells_states)
	: transformations(cells_states.size()), color(tetroid_color), next_transformation(0)
{
	if (cells_states.size() == 0)
	{
		throw std::invalid_argument("No states");
	}

	if (starting_posistion.x < 0 || starting_posistion.y < 0)
	{
		throw std::invalid_argument("Bad starting positions coordinates");
	}

	int cells_ammount = cells_states[0].size();
	int states_ammount = cells_states.size();
	int current_transformation = 0;

	for (int i = 0; i < states_ammount-1; i++)
	{
		if (cells_states[i].size() != cells_ammount)
		{
			throw std::invalid_argument("Different numbers of cells in states");
		}

		for (int j = 0; j < cells_ammount; j++)
		{
			transformations[current_transformation].push_back(cells_states[i][j] - cells_states[i+1][j]);
		}
		current_transformation++;
	}

	for (int j = 0; j < cells_ammount; j++)
	{
		transformations[current_transformation].push_back(cells_states[states_ammount-1][j] - cells_states[0][j]);

		this->points.push_back(cells_states[0][j] + starting_posistion);
	}
}


void Tetroid::move_down() noexcept
{
	for (auto& el : points)
	{
		el.y += 1;
	}
}

void Tetroid::move_left() noexcept
{
	for (auto& el : points)
	{
		el.x -= 1;
	}
}

void Tetroid::move_right() noexcept
{
	for (auto& el : points)
	{
		el.x += 1;
	}
}

void Tetroid::rotate_right()
{
	for (int i = 0; i < points.size(); i++)
	{
		points[i] -= (transformations[next_transformation])[i];
	}

	next_transformation++;

	if (next_transformation == transformations.size())
	{
		next_transformation = 0;
	}
}

void Tetroid::rotate_left()
{
	if (next_transformation == 0)
	{
		next_transformation = transformations.size();
		next_transformation--;
	}

	else
	{
		next_transformation--;
	}

	for (int i = 0; i < points.size(); i++)
	{
		points[i] += (transformations[next_transformation])[i];
	}


	if (next_transformation == transformations.size())
	{
		next_transformation = 0;
	}
}

sf::Color Tetroid::get_color() const noexcept
{
	return color;
}

std::vector<sf::Vector2i> Tetroid::get_points() const noexcept
{
	return points;
}


