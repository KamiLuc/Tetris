#pragma once
#include <SFML/Graphics.hpp>
#include "Tetris_calculator.h"

const sf::Vector2f GAME_ON_SCREEN_POSITION { 5.f, 5.f };

const sf::Vector2i BOARD_SIZE { 10, 20 };

const float CELL_SIZE = 30.f;

const sf::Vector2i WINDOW_SIZE { 670, 610 };

const char* WINDOW_TITLE = "Tetris!";

const sf::Color DEFAULT_CELL_COLOR{ 26, 8, 31 };

static Original_tetris_calculator CALCULATOR;

const std::string& FONT_NAME{ "ARCADECLASSIC.ttf" };

///////////////////////////////////////////////////////////////////////////////////////////////////////
using tetroid = std::vector<std::vector<sf::Vector2i>>;

tetroid i_shape{ {{0,0},{1,0},{2,0},{3,0}},{{2,-1},{2,0},{2,1},{2,2}} };
tetroid o_shape{ {{0,0},{0,1},{1,0},{1,1}} };
tetroid j_shape{
    {{0,0},{1,0},{2,0},{2,1}},
    {{1,-1},{1,0},{1,1},{0,1}},
    {{0,0},{0,1},{1,1},{2,1}},
    {{2,-1},{1,-1},{1,0},{1,1}}
};
tetroid l_shape{
    {{0,0},{1,0},{2,0},{0,1}},
    {{0,-1},{1,-1},{1,0},{1,1}},
    {{0,1},{1,1},{2,1},{2,0}},
    {{1,-1},{1,0},{1,1},{2,1}}
};
tetroid s_shape{
    {{0,1},{1,1},{1,0},{2,0}},
    {{0,-1},{0,0},{1,0},{1,1}},
    {{0,1},{1,1},{1,0},{2,0}},
    {{0,-1},{0,0},{1,0},{1,1}}
};
tetroid z_shape{
   {{0,0},{1,0},{1,1},{2,1}},
   {{1,0},{1,1},{2,-1},{2,0}},
   {{0,0},{1,0},{1,1},{2,1}},
   {{1,0},{1,1},{2,-1},{2,0}}
};
tetroid t_shape{
   {{0,0},{1,0},{2,0},{1,1}},
   {{1,-1},{1,0},{1,1},{0,0}},
   {{2,1},{1,1},{0,1},{1,0}},
   {{1,-1},{1,0},{1,1},{2,0}}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////