/**
 * @file convert.cpp
 * @brief implementation file for conversion functions
 */

#include <vector>

#include "converter.hpp"

std::string runLengthEncode(std::string_view _number) 
{
	size_t size = _number.size();
	if(size == 0) return {};
	std::string encoded;
	unsigned groupCount = 1;
	for(size_t i = 1; i < size; ++i)
	{
		if(_number[i-1] == _number[i])
		{
			++groupCount;	
		}
		else
		{
			encoded.append(std::to_string(groupCount))
				.append(" ")
				.append(1, _number[i-1])
				.append(" ");
			groupCount = 1;
		}
	}
	encoded.append(std::to_string(groupCount))
		.append(" ")
		.append(1, _number[size-1]);
	return encoded;
}

std::string asRunLengthEncode(std::string_view _number) 
{
	return {};
}

std::string romanNumerals(std::string_view _number) 
{
	static const std::vector<std::pair<unsigned short, const char*>> roman //TODO? make array?
	{
		{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
		{100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
		{10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
	};
	if(_number.size() == 0) return {};
	unsigned short number = static_cast<unsigned short>(std::stoul(std::string(_number))); //TODO find way without converting?
	if(number < 1 || number > 3999) return {};
	std::string converted{};
	for(auto& r : roman)
	{
		while(number >= r.first)
		{
			number -= r.first;
			converted += r.second;
		}
		if(!number) break;
	}
	return converted;
}

std::string numberToEnglish(std::string_view _number) 
{
	static const std::vector<std::string> numeng //TODO? make array?
	{
		"", "one", "two", "three", "four", "five",
		"six", "seven", "eight", "nine", "ten",
		"eleven", "twelve", "thirteen",	"fourteen",
		"fifteen", "sixteen", "seventeen", "eighteen",
		"nineteen", "twenty", "thirty",	"forty",
		"fifty", "sixty", "seventy", "eighty", "ninety"
	};
	auto number = static_cast<unsigned short>(std::stoul(std::string(_number))); //TODO find way without converting?
	if(number > 999) return {};
	if(number == 0) return {"zero"};
	if(number < 21) return numeng[number];
	std::string english;
	if(number > 99){
		english += numeng[number / 100] + " hundred ";
		number = number % 100;
	}
	if(number < 21) english += numeng[number];
	else{
		english += numeng[(number / 10) + 18];
		english += " " + numeng[number % 10];
	}
	if(english.back() == ' ') english.pop_back();
	return english;
}
