#include "Tetris_calculator.h"

unsigned int Original_tetris_calculator::calculate_level(unsigned int lines_completed)
{
	if (lines_completed <= 0)
	{
		return 1;
	}
	else if ((lines_completed >= 1) && (lines_completed <= 90))
	{
		return 1 + ((lines_completed - 1) / 10);
	}
	else if (lines_completed >= 91)
	{
		return 10;
	}
}

double Original_tetris_calculator::calculate_iteration_time(unsigned int level)
{
	return ((11 - level) * 0.05);  // [seconds]
}

unsigned int Original_tetris_calculator::calculate_point_award(unsigned int level, unsigned int free_fall_iteration)
{
	return (21 + (3 //7 
		* level)) - free_fall_iteration;
}
