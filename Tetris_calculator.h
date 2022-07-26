#pragma once

class Level_delay_score_calculator
{
private:
public:
	virtual unsigned int calculate_level(unsigned int lines_completed) = 0;
	virtual double calculate_iteration_time(unsigned int level) = 0;
	virtual unsigned int calculate_point_award(unsigned int level, unsigned int free_fall_iteration) = 0;
};

class Original_tetris_calculator : public Level_delay_score_calculator
{
private:
public:
	virtual unsigned int calculate_level(unsigned int lines_completed) override;
	virtual double calculate_iteration_time(unsigned int level) override;
	virtual unsigned int calculate_point_award(unsigned int level, unsigned int free_fall_iteration) override;
};