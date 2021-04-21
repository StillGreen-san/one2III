/**
 * @file one2IIImain.cpp
 * @brief this is the main file for one2III, tying all functionality together
 */

#include <algorithm>
#include <iostream>

#include "conversionrule.hpp"
#include "conversionstates.hpp"
#include "helperfunctions.hpp"

int main()
{
	SimpleMenu sm;
	sm.addState(SimpleMenu::State(ConversionStates::Info));
	sm.addState(SimpleMenu::State(ConversionStates::Test));
	sm.addState(SimpleMenu::State(ConversionStates::Nums));
	sm.addState(SimpleMenu::State(ConversionStates::Rule));
	sm.addState(SimpleMenu::State(ConversionStates::Conv));
	sm.addState(SimpleMenu::State(ConversionStates::Exit));
	sm.show();

	RuleBook& ruleBook = ConversionStates::Rule_get();
	std::string& numberSequence = ConversionStates::Nums_get();

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
					for(auto& rule : ruleBook)
					{
						viewConversions.push_back(std::move(ConversionRule::convert(rule, view)));
					}
					allConversions.push_back(std::move(viewConversions));
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
