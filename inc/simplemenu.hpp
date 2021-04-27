/**
 * @file simplemenu.hpp
 * @brief include file for menu
 *
 */

#pragma once

#include <functional>
#include <string>
#include <vector>

/**
 * @brief a simple console menu system
 *
 */
struct SimpleMenu
{
public:
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
		Restart,

		/**
		 * @brief screen id to signal the menu should go to this screen when the option is choosen
		 *
		 */
		This,

		/**
		 * @brief key code to signal the menu should accept any input for this option
		 *
		 */
		AnyKey
	};

	/**
	 * @brief screen obj used with SimpleMenu
	 *
	 */
	struct SimpleScreen
	{
	public:
		/**
		 * @brief adds the description displayed above the options
		 *
		 * @param desc the text to display
		 * @return SimpleScreen&
		 */
		SimpleScreen& setDescription(std::string desc);

		/**
		 * @brief add an option
		 *
		 * @param key the key to press to select this option,
		 * use SimpleMenu::AnyKey to allow any
		 * @param desc the description for this option
		 * @param screen the screen to transition to after this option was selected,
		 * use SimpleMenu::Exit/Restart to exit/restart the menu
		 * @param cllbck a function to call when this option was selected
		 * @return SimpleScreen& this screen
		 */
		SimpleScreen& addOption(char key, std::string desc, int screen, std::function<void()> cllbck = nullptr);

	private:
		friend SimpleMenu;
		explicit SimpleScreen(int id) : id{id} {};
		struct Option
		{
			char key;
			std::string description;
			int nextScreen;
			std::function<void()> callback;
		};
		int id;
		std::string description;
		std::vector<Option> options;
	};

	/**
	 * @brief adds a screen to the menu,
	 * use method chaining to set options for the screen,
	 * if no options are added this screen will exit the menu
	 *
	 * @param id identifier for the screen
	 * @return SimpleScreen& the new screen
	 */
	SimpleScreen& addScreen(int id);

	/**
	 * @brief enters the menu loop with the screen specified by id,
	 * will exit imediatly if id was not found
	 *
	 * @param id the screen id to show
	 */
	void show(int id);

private:
	std::vector<SimpleScreen> screens;
};
