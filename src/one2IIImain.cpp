#include <algorithm>
#include <iostream>

#include "conversionrule.hpp"
#include "converter.hpp"
#include "helperfunctions.hpp"
#include "rulebook.hpp"
#include "simplemenu.hpp"

// TODO add noexecpt where possible

int main()
{
	RuleBook ruleBook;
	std::string numberSequence;

	enum ID : int
	{
		Main = 1,
		Rules,
		Convert
	};

	SimpleMenu sm;
	sm.addScreen(ID::Main)
	    .setDescription("one2III\n"
	                    "given a string of digits and a list of conversion rules\n"
	                    "split the string into all possible substrings\n"
	                    "convert every substring using every possible conversion rule\n")
	    .addOption('e', "Exit", SimpleMenu::Exit)
	    .addOption(SimpleMenu::AnyKey, "press enter to continue", ID::Rules,
	        [&]()
	        {
		        numberSequence.clear();
		        ruleBook = RuleBook();

		        while(!isValidNumberSequence(numberSequence))
		        {
			        std::cout << "enter a number sequence\n";
			        std::cin >> numberSequence;
		        }
		        std::cin.get();
	        });

	sm.addScreen(ID::Rules)
	    .setDescription("Select a Rule to add")
	    .addOption('r', "RomanNumeralConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::RomanNumeralConversion);
	        })
	    .addOption('n', "AsNumberConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::AsNumberConversion);
	        })
	    .addOption('a', "AsRunLengthEncodingConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::AsRunLengthEncodingConversion);
	        })
	    .addOption('e', "NumberToEnglishConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::NumberToEnglishConversion);
	        })
	    .addOption('l', "RunLengthEncodingConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::RunLengthEncodingConversion);
	        })
	    .addOption('s', "LookAndSayConversion", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::LookAndSayConversion);
	        })
	    .addOption('c', "Convert", ID::Convert,
	        [&]()
	        {
		        sm.at(ID::Convert)
		            .setDescription(std::to_string(Converter::calculatePossibilities(ruleBook, numberSequence))
		                                .append(" possible conversions. Choose which to display."));
	        })
	    .addOption('b', "Restart", SimpleMenu::Restart);

	sm.addScreen(ID::Convert)
	    .setDescription("")
	    .addOption('a', "Show all", SimpleMenu::This,
	        [&]()
	        {
		        Converter::allConversions(ruleBook, numberSequence,
		            [](std::string&& conversion)
		            {
			            std::cout << '\n' << conversion;
			            return true;
		            });
		        std::cout << '\n' << '\n';
	        })
	    .addOption('r', "Show a random", SimpleMenu::This,
	        [&]()
	        {
		        std::cout << '\n' << Converter::randomConversion(ruleBook, numberSequence) << '\n';
	        })
	    .addOption('s', "Show a single", SimpleMenu::This,
	        [&]()
	        {
		        size_t number;
		        std::cout << "\nEnter a number: ";
		        std::cin >> number;
		        std::cout << Converter::singleConversion(ruleBook, numberSequence, number) << '\n';
		        std::cin.get();
	        })
	    .addOption('b', "Restart", SimpleMenu::Restart);

	sm.show(ID::Main);
}
