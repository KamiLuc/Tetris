#include "Expanded_text_options.h"

Expanded_text_options::Expanded_text_options(float message_xpos, float message_ypos, float message_dx, float message_dy, sf::Font* font, int font_size, sf::Color text_color, sf::Color marked_text_color, std::string text_string):
	Text_options(message_xpos, message_ypos, font, font_size, text_color, text_string),
	dx(dx), dy(dy), marked_text_color(marked_text_color)
{
}

void Expanded_text_options::Load_text_options(sf::Text& source_text) const
{
	Text_options::Load_text_options(source_text);
}
