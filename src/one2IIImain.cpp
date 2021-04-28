#include <algorithm>
#include <iostream>

#include "conversionrule.hpp"
#include "helperfunctions.hpp"
#include "rulebook.hpp"
#include "simplemenu.hpp"

void mainConvert(RuleBook& ruleBook, std::string& numberSequence)
{
	std::cout << std::endl;
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
				{
					continue;
				}
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

	numberSequence.clear();
	ruleBook = RuleBook();
}

int main()
{
	RuleBook ruleBook;
	std::string numberSequence;

	SimpleMenu sm;
	sm.addScreen(1)
	    .setDescription("one2III\n"
	                    "given a string of digits and a list of conversion rules\n"
	                    "split the string into all possible substrings\n"
	                    "convert every substring using every possible conversion rule\n")
	    .addOption('e', "Exit", SimpleMenu::Exit)
	    .addOption(
	        SimpleMenu::AnyKey, "press enter to continue", 2,
	        [&]()
	        {
		        while(!isValidNumberSequence(numberSequence))
		        {
			        std::cout << "enter a number sequence\n";
			        std::cin >> numberSequence;
		        }
		        std::cin.get();
	        });
	sm.addScreen(2)
	    .setDescription("Select a Rule to add")
	    .addOption(
	        'r', "RomanNumeralConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::RomanNumeralConversion);
	        })
	    .addOption(
	        'n', "AsNumberConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::AsNumberConversion);
	        })
	    .addOption(
	        'a', "AsRunLengthEncodingConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::AsRunLengthEncodingConversion);
	        })
	    .addOption(
	        'e', "NumberToEnglishConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::NumberToEnglishConversion);
	        })
	    .addOption(
	        'l', "RunLengthEncodingConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::RunLengthEncodingConversion);
	        })
	    .addOption(
	        's', "LookAndSayConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::LookAndSayConversion);
	        })
	    .addOption(
	        'c', "Convert", SimpleMenu::Restart,
	        [&]()
	        {
		        mainConvert(ruleBook, numberSequence);
	        });

	sm.show(1);
}
