/**
 * @file one2IIImain.cpp
 * @brief this is the main file for one2III, tying all functionality together
 */

#include <iostream>
#include <algorithm>

#include "helperfunctions.hpp"
#include "conversionrule.hpp"
#include "rulebook.hpp"
#include "conversionstates.hpp"

int main()
{
	SimpleMenu sm;
	sm.addState(SimpleMenu::State(ConversionStates::Info));
	sm.addState(SimpleMenu::State(ConversionStates::Test));
	sm.addState(SimpleMenu::State(ConversionStates::Exit));
	sm.show();
	
	std::string numberSequence;// = "123456";//
	while(isValidNumberSequence(numberSequence) == false)
	{
		std::cout << "enter a number sequence: ";
		std::cin >> numberSequence;
	}

	RuleBook ruleBook;
	ruleBook.add(RuleType::RomanNumeralConversion);
	ruleBook.add(RuleType::AsNumberConversion);
	ruleBook.add(RuleType::AsRunLengthEncodingConversion);
	ruleBook.add(RuleType::NumberToEnglishConversion);
	ruleBook.add(RuleType::RunLengthEncodingConversion);
	ruleBook.add(RuleType::LookAndSayConversion);

	uint8_t digits = static_cast<uint8_t>(numberSequence.size());
	for(uint8_t parts = digits; parts > 0; --parts)
	{
		auto partitions = integerPartitions(digits, parts,
								(uint8_t)ruleBook.getMinInputSize(), (uint8_t)ruleBook.getMaxInputSize());
		for(auto& partition : partitions)
		{
			do
			{
				std::cout << partition << std::endl;
				const auto views = partitionString(numberSequence, partition);
				if(views.size() == 0) continue;
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
						std::cout << allConversions[y][x-1] << " | ";
					}
					std::cout << std::endl;
				}
			} while(std::next_permutation(rbegin(partition), rend(partition)));
			std::cout << std::endl;
		}
	}
}
