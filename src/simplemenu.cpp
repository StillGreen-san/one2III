/**
 * @file simplemenu.hpp
 * @brief include file for menu and state
 * 
 */

#include "simplemenu.hpp"

#include <functional>

void SimpleMenu::show()
{
	StateHandler sh;
	auto r = (sh.*callback)({nullptr});//TODO resolve this mess
}

SimpleMenu StateHandler::makeMenu()
{
	return SimpleMenu(states.front()->text, &StateHandler::parseInput);
}

std::string_view StateHandler::parseInput(std::string_view _input)
{
	return {};
}

void StateHandler::addState(const SimpleState* _state)
{
	states.push_back(_state);//TODO handle duplicates
}
