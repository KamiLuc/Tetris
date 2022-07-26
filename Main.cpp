﻿#include <SFML/Graphics.hpp>
#include "Tetris.h"
#include <chrono>
#include <iostream>
#include "Text_options.h"
#include "Config.h"

int main()
{
    sf::Font font;
    font.loadFromFile("ARCADECLASSIC.ttf");
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE);

    const Text_options TETRIS_TEXT_OPTIONS(TETRIS_TEXT_POSITION.x,
        TETRIS_TEXT_POSITION.y,
        &font,
        TETRIS_TEXT_CHARACTER_SIZE,
        TETRIS_TEXT_COLOR);

    tetris::Tetris game(GAME_ON_SCREEN_POSITION,
        BOARD_SIZE.x,
        BOARD_SIZE.y,
        CELL_SIZE,
        &CALCULATOR,
        DEFAULT_CELL_COLOR,
        TETRIS_TEXT_OPTIONS);

    game.add_new_tetroid(i_shape, sf::Color::Red);
    game.add_new_tetroid(o_shape, sf::Color::Yellow);
    game.add_new_tetroid(l_shape, { 255, 185, 8 });
    game.add_new_tetroid(j_shape, sf::Color::Blue);
    game.add_new_tetroid(s_shape, sf::Color::Magenta);
    game.add_new_tetroid(z_shape, { 60, 232, 123 });
    game.add_new_tetroid(t_shape, { 25, 224, 211 });

    sf::Event event;
    std::chrono::steady_clock::time_point start, stop;
    bool start_clock = true;

    while (window.isOpen())
    {
        if (start_clock)
        {
            start = std::chrono::high_resolution_clock::now();
            start_clock = false;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    game.update(tetris::Tetris::Action::move_tetroid_left);
                    break;
                case sf::Keyboard::Right:
                    game.update(tetris::Tetris::Action::move_tetroid_right);
                    break;
                case sf::Keyboard::Q:
                    game.update(tetris::Tetris::Action::rotate_tetroid_left);
                    break;
                case sf::Keyboard::E:
                    game.update(tetris::Tetris::Action::rotate_tetroid_right);
                    break;
                case sf::Keyboard::Down:
                    game.update(tetris::Tetris::Action::drop_tetroid);
                    break;
                case sf::Keyboard::R:
                    game.reset();
                    break;
                case sf::Keyboard::A:
                    game.update(tetris::Tetris::Action::move_next_tetroid_left);
                    break;
                case sf::Keyboard::D:
                    game.update(tetris::Tetris::Action::move_next_tetroid_right);
                    break;
                default:
                    break;
                }
            }
        }

        stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = stop - start;

        if (elapsed.count() >= game.get_fall_iteration() * 1000)
        {
            game.update(tetris::Tetris::Action::move_tetroid_down);
            start_clock = true;
        };

        window.clear();
        game.draw(window, sf::RenderStates::Default);
        window.display();
    }
    return 0;
}