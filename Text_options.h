#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Text_options
{
protected:
	std::string text_string;
	float message_xpos;
	float message_ypos;
	sf::Font* font;
	unsigned int font_size;
	sf::Color text_color;
public:
	Text_options(float message_xpos = 0, float message_ypos = 0,
		sf::Font* font = nullptr, int font_size = 0, sf::Color text_color = sf::Color::White, std::string text_string = "");
	void Load_text_options(sf::Text& source_text) const;
};