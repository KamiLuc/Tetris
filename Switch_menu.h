#pragma once
#include <SFML/Graphics.hpp>
#include "Expanded_text_options.h"

class Switch_menu
{
private:
	const Expanded_text_options text_options;
	void turn_text_regular(int index) noexcept;
	void turn_text_not_regular(int index) noexcept;
public:
	std::vector<sf::Text> menu_messages;
	int current_option = 0;
	Switch_menu(const std::vector<std::string>& menu_messages, const Expanded_text_options& text_options);
	void switch_up(void) noexcept;
	void switch_down(void) noexcept;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	std::string get_marked_option(void) noexcept;
};