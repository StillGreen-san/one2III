/**
 * @file simplemenu.hpp
 * @brief include file for menu and state
 * 
 */

#include "simplemenu.hpp"

#include <iostream>

void SimpleMenu::show() 
{
	if(states.size() == 0) return;

	std::cout << states[activeState].text << std::endl;

	std::string input;
	std::cin >> input;

	bool handled = false;
	for(auto& action : states[activeState].inputmap)
	{
		if(action.input == nullptr || action.input == input)//!does this work?
		{
			if(action.external)
			{
				if(action.external(input))
				{
					activeState = 0;
					size_t size = states.size();
					for(; activeState < size;)
					{
						if(states[activeState].text == action.state)
						{
							handled = true;
							break;
						}
					}
				}
				else
				{
					return;
				}
			}
			break;
		}
	}
	if(handled == false) return;
}

void SimpleMenu::addState(SimpleMenu::State&& _state) 
{
	states.emplace_back(_state);
}
