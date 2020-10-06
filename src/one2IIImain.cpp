/**
 * @file one2IIImain.cpp
 * @brief this is the main file for one2III, tying all functionality together
 */

#include <iostream>
#include <algorithm>

#include "helper.hpp"
#include "converter.hpp"
#include "conversionrules.hpp"

int main()
{
	std::string numberSequence;
	while(isValidNumberSequence(numberSequence) == false)
	{
		std::cout << "enter a number sequence: ";
		std::cin >> numberSequence;
	}

	std::vector<std::unique_ptr<ConversionRule>> converters;
	converters.emplace_back(new RomanNumeralConversion);
	converters.emplace_back(new RunLengthEncodingConversion);

	uint8_t digits = static_cast<uint8_t>(numberSequence.size());
	for(uint8_t parts = digits; parts > 0; --parts)
	{
		const auto partitions = integerPartitions(digits, parts);
		for(auto& partition : partitions)
		{
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
			std::cout << std::endl;
		}
	}
}
