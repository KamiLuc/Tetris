#include "Switch_menu.h"

Switch_menu::Switch_menu(const std::vector<std::string>& menu_messages, const Expanded_text_options& text_options):
	text_options(text_options), menu_messages(menu_messages.size()), current_option(0)
{
	if (menu_messages.size() == 0)
	{
		throw std::invalid_argument("Empty menu messages");
	}

	for (int i = 0; i < menu_messages.size(); i++)
	{
		this->menu_messages[i].setString(menu_messages[i]);
		text_options.Load_text_options(this->menu_messages[i]);
		this->menu_messages[i].move({ i * text_options.get_dx(), i * text_options.get_dy() });
	}

	this->menu_messages[0].setFillColor(text_options.get_marked_text_color());
}

void Switch_menu::turn_text_regular(int index) noexcept
{
	menu_messages[index].setFillColor(text_options.get_normal_text_color());
}

void Switch_menu::turn_text_not_regular(int index) noexcept
{
	menu_messages[index].setFillColor(text_options.get_marked_text_color());
}

void Switch_menu::switch_up(void) noexcept
{
	turn_text_regular(current_option);
	if (current_option == 0)
	{
		current_option = menu_messages.size() - 1;
	}
	else
	{
		current_option--;
	}
	turn_text_not_regular(current_option);
}

void Switch_menu::switch_down(void) noexcept
{
	turn_text_regular(current_option);
	if (current_option == menu_messages.size() - 1)
	{
		current_option = 0;
	}
	else
	{
		current_option++;
	}
	turn_text_not_regular(current_option);
}

void Switch_menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& text : this->menu_messages)
	{
		target.draw(text);
	}
}

std::string Switch_menu::get_marked_option(void)
{
	return std::string();
}
