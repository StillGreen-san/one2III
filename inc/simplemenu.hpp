/**
 * @file simplemenu.hpp
 * @brief include file for menu and state
 *
 */

#pragma once

#include <string>
#include <vector>

class SimpleMenu
{
public:
	struct State
	{
		std::string_view text;
		struct Action
		{
			std::string_view input;
			bool (*external)(std::string_view);
			std::string_view state;
		};
		std::vector<Action> inputmap;
	};
	void show(size_t _startingState = 0);
	void addState(SimpleMenu::State&& _state);

private:
	std::vector<State> states;
	size_t activeState = 0;
};

#include <functional>

struct NewSimpleScreen
{
	NewSimpleScreen& description(std::string desc);
	NewSimpleScreen& addOption(char key, std::string desc, int screen);
	NewSimpleScreen& addOption(char key, std::string desc, std::function<void()> cllbck);
	NewSimpleScreen& addOption(char key, std::string desc, void (NewSimpleMenu::*cllbck)());
};

struct NewSimpleMenu
{
	NewSimpleScreen& addScreen(int id);
	void exit();
	void restart();
};

void NSMtest()
{
	auto AAAAAA = NewSimpleMenu::exit;
	NewSimpleMenu menu;
	menu.addScreen(69).description("valuable text").addOption('k', "som optn", 42);
	menu.addScreen(42)
	    .description("valuable text")
	    .addOption(
	        'k', "som optn",
	        []()
	        {
	        });
	menu.addScreen(-1).description("valuable text").addOption('e', "baiii", NewSimpleMenu::exit);
}
