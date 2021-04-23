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

#include <functional>

struct NewSimpleMenu
{
	enum : int
	{
		/**
		 * @brief screen id to signal the menu should exit when the option is choosen
		 *
		 */
		Exit = std::numeric_limits<int>::min(),

		/**
		 * @brief screen id to signal the menu should go to the screen specified with show() when the option is choosen
		 *
		 */
		Restart
	};
	enum : char
	{
		/**
		 * @brief key code to signal the menu should accept any input for this option
		 *
		 */
		AnyKey = std::numeric_limits<char>::min()
	};
	struct NewSimpleScreen
	{
		/**
		 * @brief adds the description displayed above the options
		 *
		 * @param desc the text to display
		 * @return NewSimpleScreen&
		 */
		NewSimpleScreen& description(std::string desc)
		{
			return *this;
		}

		/**
		 * @brief add an option
		 *
		 * @param key the key to press to select this option,
		 * use SimpleMenu::AnyKey to allow any
		 * @param desc the description for this option
		 * @param screen the screen to transition to after this option was selected,
		 * use SimpleMenu::Exit/Restart to exit/restart the menu
		 * @return NewSimpleScreen& this screen
		 */
		NewSimpleScreen& addOption(char key, std::string desc, int screen)
		{
			return *this;
		}

		/**
		 * @brief add an option
		 *
		 * @param key the key to press to select this option,
		 * use SimpleMenu::AnyKey to allow any
		 * @param desc the description for this option
		 * @param cllbck a function to call when this option was selected
		 * @return NewSimpleScreen& this screen
		 */
		NewSimpleScreen& addOption(char key, std::string desc, std::function<void()> cllbck)
		{
			return *this;
		}
	} TMP_REMOVE_ME;

	/**
	 * @brief adds a screen to the menu,
	 * use method chaining to set options for the screen,
	 * if no options are added this screen will exit the menu
	 *
	 * @param id identifier for the screen
	 * @return NewSimpleScreen& the new screen
	 */
	NewSimpleScreen& addScreen(int id)
	{
		return TMP_REMOVE_ME;
	}

	/**
	 * @brief enters the menu loop with the screen specified by id,
	 * will exit imediatly if id was not found
	 *
	 * @param id the screen id to show
	 */
	void show(int id)
	{
	}
};

void NSMtest()
{
	NewSimpleMenu menu;
	menu.addScreen(69).description("valuable text").addOption('k', "som optn", 42);
	menu.addScreen(42)
	    .description("valuable text")
	    .addOption(
	        'k', "som optn",
	        []()
	        {
	        });
	menu.addScreen(-1).description("valuable text").addOption('e', "baiii", NewSimpleMenu::Exit);
	menu.addScreen(-2).description("valuable text").addOption(NewSimpleMenu::AnyKey, "baiii", NewSimpleMenu::Exit);

	menu.show(-1);
}
