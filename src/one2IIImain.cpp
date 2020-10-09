/**
 * @file one2IIImain.cpp
 * @brief this is the main file for one2III, tying all functionality together
 */

#include <iostream>
#include <algorithm>

#include "helper.hpp"
#include "converter.hpp"
#include "conversionrules.hpp"

std::ostream& operator<<(std::ostream& _os, const std::vector<uint8_t>& _vec)
{
	_os << "[ ";
	std::string sep = "";
	for(auto& v : _vec)
	{
		_os << sep << static_cast<short>(v);
		sep = ", ";
	}
	_os << " ]";
	return _os;
}

int main()
{
	std::string numberSequence;// = "123456";//
	while(isValidNumberSequence(numberSequence) == false)
	{
		std::cout << "enter a number sequence: ";
		std::cin >> numberSequence;
	}

	std::vector<std::unique_ptr<ConversionRule>> converters;
	converters.emplace_back(new RomanNumeralConversion);
	converters.emplace_back(new AsNumberConversion);
	converters.emplace_back(new AsRunLengthEncodingConversion);
	converters.emplace_back(new NumberToEnglishConversion);
	converters.emplace_back(new RunLengthEncodingConversion);
	converters.emplace_back(new LookAndSayConversion);

	RuleBook rb; rb ;  ;

	uint8_t digits = static_cast<uint8_t>(numberSequence.size());
	for(uint8_t parts = digits; parts > 0; --parts)
	{
		auto min = std::min_element(begin(converters), end(converters), [](auto& a, auto& b){
			return a->getMinInputSize() < b->getMinInputSize();
		});
		auto max = std::max_element(begin(converters), end(converters), [](auto& a, auto& b){
			return a->getMaxInputSize() < b->getMaxInputSize();
		});
		auto partitions = integerPartitions(digits, parts, (*min)->getMinInputSize(), (*max)->getMaxInputSize());
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
					for(auto& c : converters)
					{
						viewConversions.push_back(std::move(c->convert(view)));
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
