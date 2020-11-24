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
	SimpleMenu(std::string_view _text, std::string_view(*_callback)(std::string_view)) :
		text{_text}, callback{_callback} {}
	void show();
private:
	std::string_view text;
	std::string_view(*callback)(std::string_view);
};

class MenuState
{
public:
	struct State
	{
		std::string_view text;
		struct InputAndState
		{
			std::string_view input;
			std::string_view state;
		};
		std::vector<InputAndState> inputmap;
	};
public:
	SimpleMenu makeMenu();
	std::string_view parseInput(std::string_view);
	void addState(State&& _state);
private:
	std::vector<State> states;
};
