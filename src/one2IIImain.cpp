/**
 * @file one2IIImain.cpp
 * @brief this is the main file for one2III, tying all functionality together
 */

#include <iostream>

#include "helper.hpp"
#include "converter.hpp"

int main()
{
	std::cout << "enter a number sequence:";
	std::string numberSequence;
	std::cin >> numberSequence; //TODO validate input
	std::cout << "select converter: 1:rom, 2:rle, 3:eng :";
	short converter;
	std::cin >> converter;
	auto convert = [&](const std::string_view& view){
		switch (converter)
		{
		case 1: return romanNumerals(view);
		case 2: return runLengthEncode(view);
		case 3: return numberToEnglish(view);
		default: return std::string{};
		}
	};
	uint8_t digits = static_cast<uint8_t>(numberSequence.size());
	for(uint8_t parts = digits; parts > 0; --parts)
	{
		const auto partitions = integerPartitions(digits, parts);
		for(auto& partition : partitions)//TODO better naming?
		{
			const auto views = partitionString(numberSequence, partition);
			if(views.size() == 0) continue;
			std::string converted;
			const std::string seperator = " | ";
			for(auto& view : views)//TODO better naming?
			{
				converted.append(convert(view)).append(seperator);
			}
			converted[converted.size()-3] = '\0';
			std::cout << converted.c_str() << std::endl;
		}
	}
}