/**
 * @file simplemenu.hpp
 * @brief include file for menu and state
 *
 */

#include "simplemenu.hpp"

#include <iostream>

void SimpleMenu::show(size_t _startingState)
{
	if(states.size() == 0)
	{
		return;
	}
	activeState = _startingState;

	while(true)
	{
		std::cout << states[activeState].text << std::endl;

		std::string input;
		std::cin >> input;

		bool handled = false;
		for(auto& action : states[activeState].inputmap)
		{
			if(action.input.data() == nullptr || action.input == input)
			{
				if(action.external)
				{
					if(!action.external(input))
					{
						handled = true;
						break;
					}
				}
				size_t size = states.size();
				for(activeState = 0; activeState < size; ++activeState)
				{
					if(states[activeState].text == action.state)
					{
						handled = true;
						break;
					}
				}
				break;
			}
		}
		if(handled == false)
		{
			return;
		}
	}
	return;
}

void SimpleMenu::addState(SimpleMenu::State&& _state)
{
	states.emplace_back(_state);
}
