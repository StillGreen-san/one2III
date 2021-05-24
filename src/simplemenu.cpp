#include "simplemenu.hpp"

#include <exception>
#include <iostream>

SimpleMenu::SimpleScreen& SimpleMenu::SimpleScreen::setDescription(std::string desc)
{
	description = std::move(desc);
	return *this;
}

SimpleMenu::SimpleScreen& SimpleMenu::SimpleScreen::addOption(
    char key, std::string desc, int screen, std::function<void()> cllbck)
{
	options.emplace_back(key, std::move(desc), screen, std::move(cllbck));
	return *this;
}

std::vector<SimpleMenu::SimpleScreen>::iterator SimpleMenu::findScreen(int id)
{
	return std::find_if(std::begin(screens), std::end(screens),
	    [id](const SimpleScreen& screen)
	    {
		    return screen.id == id;
	    });
}

SimpleMenu::SimpleScreen& SimpleMenu::addScreen(int id)
{
	if(auto it = findScreen(id); it != std::end(screens))
	{
		return *it;
	}
	return screens.emplace_back(SimpleScreen(id));
}

void SimpleMenu::show(int id)
{
	if(screens.empty())
	{
		return;
	}

	const int initialId = id;

	while(id != Exit)
	{
		auto screen = findScreen(id);
		if(screen == std::end(screens))
		{
			screen = std::begin(screens);
		}

		std::cout << '\n' << screen->description << '\n';
		for(const SimpleScreen::Option& opt : screen->options)
		{
			if(opt.key == AnyKey)
			{
				std::cout << " any";
			}
			else
			{
				std::cout << "  " << opt.key << ' ';
			}
			std::cout << ": " << opt.description << '\n';
		}

		const auto noOption = std::end(screen->options);

		char key = '\000';
		std::cin.get(key);
		if(key != '\n')
		{
			std::cin.ignore();
		}

		auto option = std::find_if(std::begin(screen->options), noOption,
		    [key](const SimpleScreen::Option& opt)
		    {
			    return opt.key == key || opt.key == AnyKey;
		    });
		if(option == noOption)
		{
			continue;
		}

		if(option->callback)
		{
			option->callback();
		}

		if(option->nextScreen == Restart)
		{
			id = initialId;
		}
		else if(option->nextScreen != This)
		{
			id = option->nextScreen;
		}
	}
}

SimpleMenu::SimpleScreen& SimpleMenu::at(int id)
{
	for(auto& screen : screens)
	{
		if(screen.id == id)
		{
			return screen;
		}
	}
	throw std::invalid_argument("No Screen with this ID");
}
