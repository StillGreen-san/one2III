/**
 * @file simplemenu.cpp
 * @brief implementation file for menu
 *
 */

#include "simplemenu.hpp"

#include <iostream>

SimpleMenu::SimpleScreen& SimpleMenu::SimpleScreen::setDescription(std::string desc)
{
	return *this;
}

SimpleMenu::SimpleScreen& SimpleMenu::SimpleScreen::addOption(
    char key, std::string desc, int screen, std::function<void()> cllbck)
{
	return *this;
}

SimpleMenu::SimpleScreen& SimpleMenu::addScreen(int id)
{
	auto it = std::find_if(
	    std::begin(screens), std::end(screens),
	    [id](const SimpleScreen& screen)
	    {
		    return screen.id == id;
	    });
	if(it != std::cend(screens))
	{
		return *it;
	}
	return screens.emplace_back(id);
}

void SimpleMenu::show(int id)
{
	//
}

// ##########################################

void NSMtest()
{
	SimpleMenu menu;
	menu.addScreen(69).setDescription("valuable text").addOption('k', "som optn", 42);
	menu.addScreen(42)
	    .setDescription("valuable text")
	    .addOption(
	        'k', "som optn", SimpleMenu::This,
	        []()
	        {
	        });
	menu.addScreen(-1).setDescription("valuable text").addOption('e', "baiii", SimpleMenu::Exit);
	menu.addScreen(-2).setDescription("valuable text").addOption(SimpleMenu::AnyKey, "baiii", SimpleMenu::Exit);

	menu.show(-1);
}