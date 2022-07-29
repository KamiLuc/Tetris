#pragma once
#include "Text_options.h"

class Expanded_text_options : public Text_options
{
protected:
	float dx, dy;
	sf::Color marked_text_color;
public:
	Expanded_text_options(float message_xpos = 0, float message_ypos = 0, float message_dx = 0, float message_dy = 0,
		sf::Font* font = nullptr, int font_size = 0, sf::Color text_color = sf::Color::White, sf::Color marked_text_color = sf::Color::Blue, std::string text_string = "");
	void Load_text_options(sf::Text& source_text) const;
	sf::Color get_marked_text_color() const { return marked_text_color; }
	float get_dx() const { return dx; }
	float get_dy() const { return dy; }
	sf::Color get_normal_text_color() const { return text_color; }
};