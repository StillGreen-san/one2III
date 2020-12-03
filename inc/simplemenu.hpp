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
			bool(*external)(std::string_view);
			std::string_view state;
		};
		std::vector<Action> inputmap;
	};
	void show();
	void addState(State&& _state);
private:
	std::vector<State> states;
	size_t activeState = 0;
};
