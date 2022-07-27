#include "Text_options.h"

Text_options::Text_options(float message_xpos, float message_ypos, sf::Font* font, int font_size, sf::Color text_color, std::string text_string) :
text_string(text_string),
message_xpos(message_xpos),
message_ypos(message_ypos),
font(font),
font_size(font_size),
text_color(text_color)
{

}

void Text_options::Load_text_options(sf::Text& source_text) const
{
	source_text.setPosition(message_xpos, message_ypos);
	source_text.setFont(*font);
	source_text.setString(text_string);
	source_text.setFillColor(text_color);
	source_text.setCharacterSize(font_size);
}
