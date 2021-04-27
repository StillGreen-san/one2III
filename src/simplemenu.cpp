/**
 * @file simplemenu.cpp
 * @brief implementation file for menu
 *
 */

#include "simplemenu.hpp"

#include <iostream>

SimpleMenu::SimpleScreen& SimpleMenu::SimpleScreen::setDescription(std::string desc)
{
	description = std::move(desc);
	return *this;
}

SimpleMenu::SimpleScreen& SimpleMenu::SimpleScreen::addOption(
    char key, std::string desc, int screen, std::function<void()> cllbck)
{
	options.emplace_back(key, std::move(desc), screen, std::move(cllbck));
	return *this;
}

std::vector<SimpleMenu::SimpleScreen>::iterator SimpleMenu::findScreen(int id)
{
	return std::find_if(
	    std::begin(screens), std::end(screens),
	    [id](const SimpleScreen& screen)
	    {
		    return screen.id == id;
	    });
}

SimpleMenu::SimpleScreen& SimpleMenu::addScreen(int id)
{
	if(auto it = findScreen(id); it != std::end(screens))
	{
		return *it;
	}
	return screens.emplace_back(SimpleScreen(id));
}

void SimpleMenu::show(int id)
{
	if(screens.empty())
	{
		return;
	}

	while(id != Exit)
	{
		// find id
		auto it = findScreen(id);
		if(it == std::end(screens))
		{
			it = std::begin(screens);
		}

		// display screen
		// get input
		// call callback
		// check/set id
	}
}
