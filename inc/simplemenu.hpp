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
	static const std::string_view exit;
private:
	std::string_view text;
	std::string_view(*callback)(std::string_view);
};
const std::string_view SimpleMenu::exit{nullptr, std::numeric_limits<size_t>::max()};

struct SimpleState
{
	std::string_view text;
	struct Action
	{
		std::string_view input;
		void(*external)(std::string_view);
		std::string_view state;
	};
	std::vector<Action> inputmap;
};

class StateHandler
{
public:
	SimpleMenu makeMenu();
	std::string_view parseInput(std::string_view _input);
	void addState(const SimpleState& _state);
private:
	std::vector<const SimpleState&> states;
};
