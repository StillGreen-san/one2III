/**
 * @file one2IIImain.cpp
 * @brief this is the main file for one2III, tying all functionality together
 */

#include <algorithm>
#include <iostream>

#include "conversionrule.hpp"
#include "helperfunctions.hpp"
#include "rulebook.hpp"
#include "simplemenu.hpp"

int main()
{
	SimpleMenu sm;

	sm.addScreen(1)
	    .setDescription("Main Test Menu")
	    .addOption('t', "open this screen again", SimpleMenu::This)
	    .addOption('e', "show the exit screen", -1);
	sm.addScreen(-1)
	    .setDescription("here you can exit this menu")
	    .addOption(SimpleMenu::AnyKey, "exit this menu", SimpleMenu::Exit);

	// sm.addState(SimpleMenu::State(ConversionStates::Info));
	// sm.addState(SimpleMenu::State(ConversionStates::Test));
	// sm.addState(SimpleMenu::State(ConversionStates::Nums));
	// sm.addState(SimpleMenu::State(ConversionStates::Rule));
	// sm.addState(SimpleMenu::State(ConversionStates::Conv));
	// sm.addState(SimpleMenu::State(ConversionStates::Exit));

	sm.show(1);

	RuleBook ruleBook;          // = ConversionStates::Rule_get();
	std::string numberSequence; // = ConversionStates::Nums_get();

	size_t digits = numberSequence.size();
	for(size_t parts = digits; parts > 0; --parts)
	{
		auto partitions = integerPartitions(digits, parts, ruleBook.getMinInputSize(), ruleBook.getMaxInputSize());
		for(auto& partition : partitions)
		{
			do
			{
				std::cout << partition << std::endl;
				const auto views = partitionString(numberSequence, partition);
				if(views.size() == 0)
					continue;
				std::vector<std::vector<std::string>> allConversions;
				for(auto& view : views)
				{
					std::vector<std::string> viewConversions;
					std::transform(
					    std::begin(ruleBook), std::end(ruleBook), std::back_inserter(viewConversions),
					    [&](const RuleType& rule)
					    {
						    return ConversionRule::convert(rule, view);
					    });
					allConversions.emplace_back(std::move(viewConversions));
				}
				for(size_t x = allConversions.front().size(); x > 0; --x)
				{
					std::cout << " | ";
					for(size_t y = 0; y < allConversions.size(); ++y)
					{
						std::cout << allConversions[y][x - 1] << " | ";
					}
					std::cout << std::endl;
				}
			} while(std::next_permutation(rbegin(partition), rend(partition)));
			std::cout << std::endl;
		}
	}
}
