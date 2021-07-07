#pragma once

#include <functional>
#include <string>
#include <vector>

/**
 * @brief a simple console menu system (as in not much internal code)
 *
 */
struct SimpleMenu
{
private:
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
		 * @param cllbck an optional function to call when this option was selected
		 * @return SimpleScreen& this screen
		 */
		SimpleScreen& addOption(char key, std::string desc, int screen, std::function<void()> cllbck = nullptr);

	private:
		friend struct SimpleMenu;

		explicit SimpleScreen(int id) : id{id} {};

		struct Option
		{
			Option(char k, std::string&& d, int s, std::function<void()>&& c) :
			    key{k}, description{std::move(d)}, nextScreen{s}, callback{std::move(c)}
			{ // TODO constructor needed?
			}

			char key;
			std::string description;
			int nextScreen;
			std::function<void()> callback;
		};

		int id;
		std::string description;
		std::vector<Option> options;
	};

	std::vector<SimpleScreen> screens;

	std::vector<SimpleScreen>::iterator findScreen(int id);

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
		 * @brief screen id to signal the menu should go back to itself when the option is choosen
		 *
		 */
		This
	};
	enum : char
	{
		/**
		 * @brief key code to signal the menu should accept any input for this option
		 *
		 */
		AnyKey = std::numeric_limits<char>::min()
	};

	/**
	 * @brief adds a screen to the menu,
	 * use method chaining to set options for the screen,
	 * if no options are added this screen will exit the menu
	 *
	 * @param id identifier for the screen
	 * @return SimpleScreen& the new screen or existing one
	 */
	SimpleScreen& addScreen(int id);

	/**
	 * @brief enters the menu loop with the screen specified by id,
	 * will exit immediatly if id was not found
	 *
	 * @param id the screen id to show
	 */
	void show(int id);

	/**
	 * @brief will try to return a reference to a screen
	 *
	 * @param id ID for which to return the reference
	 * @return SimpleScreen& reference for id, throws if not found
	 */
	SimpleScreen& at(int id);
};
