#include <algorithm>
#include <iostream>
#include <random>
#include <set>

#include "conversionrule.hpp"
#include "converter.hpp"
#include "helperfunctions.hpp"
#include "rulebook.hpp"
#include "simplemenu.hpp"

// TODO move lambdas out of addOption?
// TODO remove identical looking conversions or make conversions more destinct

int main()
{
	RuleBook ruleBook;
	std::string numberSequence;
	size_t possibilities = 0;

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
			        std::cout << "enter a number sequence with up to 20 digits\n";
			        std::cin >> numberSequence;
		        }
		        std::cin.get();
	        });

	sm.addScreen(ID::Rules)
	    .setDescription("Select a Rule to add")
	    .addOption('r', "Roman Numeral", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::RomanNumeralConversion);
	        })
	    .addOption('n', "As Number", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::AsNumberConversion);
	        })
	    .addOption('e', "Number To English", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::NumberToEnglishConversion);
	        })
	    .addOption('l', "Run Length Encoding", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::RunLengthEncodingConversion);
	        })
	    .addOption('d', "Run Length Decoding", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::RunLengthDecodingConversion);
	        })
	    .addOption('s', "Look And Say", SimpleMenu::This,
	        [&]()
	        {
		        ruleBook.add(RuleType::LookAndSayConversion);
	        })
	    .addOption('c', "Convert", ID::Convert,
	        [&]()
	        {
		        possibilities = Converter::calculatePossibilities(ruleBook, numberSequence);
		        sm.at(ID::Convert)
		            .setDescription(
		                std::to_string(possibilities).append(" possible conversions. Choose which to display."));
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
	    .addOption('n', "Show N random", SimpleMenu::This,
	        [&]()
	        {
		        size_t number;
		        std::cout << "\nHow many to show: ";
		        std::cin >> number;
		        std::cin.get();
		        number = std::min(number, possibilities);

		        std::random_device rd;
		        std::uniform_int_distribution<size_t> dist(1, possibilities);
		        std::set<size_t> ids;

		        while(ids.size() < number)
		        {
			        ids.insert(dist(rd));
		        }

		        for(size_t id : ids)
		        {
			        std::cout << '\n' << Converter::singleConversion(ruleBook, numberSequence, id);
		        }
		        std::cout << '\n';
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
