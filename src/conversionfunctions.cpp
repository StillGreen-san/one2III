/**
 * @file conversionfunctions.cpp
 * @brief implementation file for conversion functions
 */

#include <vector>

#include "conversionfunctions.hpp"

std::string runLengthEncode(std::string_view _number)
{
	size_t size = _number.size();
	if(size == 0)
	{
		return {};
	}
	std::string encoded;
	uint32_t groupCount = 1;
	for(size_t i = 1; i < size; ++i)
	{
		if(_number[i - 1] == _number[i])
		{
			++groupCount;
		}
		else
		{
			encoded.append(std::to_string(groupCount)).append(" ").append(1, _number[i - 1]).append(" ");
			groupCount = 1;
		}
	}
	encoded.append(std::to_string(groupCount)).append(" ").append(1, _number[size - 1]);
	return encoded;
}

std::string asRunLengthEncode(std::string_view _number)
{
	size_t size = _number.size();
	if(size == 0 || size % 2 != 0)
	{
		return {};
	}
	for(size_t i = 3; i < size; ++i)
	{
		if(_number[i - 2] == _number[i])
			return {};
	}
	std::string converted;
	converted.reserve((size * 2) - 1);
	for(char c : _number)
	{
		converted.append(1, c).append(1, ' ');
	}
	converted.pop_back();
	return converted;
}

std::string romanNumerals(std::string_view _number)
{
	static const std::vector<std::pair<uint16_t, const char*>> roman{
	    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
	    {40, "XL"},  {10, "X"},   {9, "IX"},  {5, "V"},    {4, "IV"},  {1, "I"}};
	if(_number.size() == 0)
	{
		return {};
	}
	uint16_t number = static_cast<uint16_t>(std::stoul(std::string(_number))); // TODO find way without converting?
	if(number < 1 || number > 3999)
	{
		return {};
	}
	std::string converted{};
	for(auto& r : roman)
	{
		while(number >= r.first)
		{
			number -= r.first;
			converted += r.second;
		}
		if(!number)
		{
			break;
		}
	}
	return converted;
}

std::string numberToEnglish(std::string_view _number)
{
	static const std::vector<std::string> numeng{
	    "",       "one",    "two",    "three",    "four",     "five",    "six",     "seven",     "eight",    "nine",
	    "ten",    "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
	    "twenty", "thirty", "forty",  "fifty",    "sixty",    "seventy", "eighty",  "ninety"};
	unsigned number = std::stoul(std::string(_number));
	if(number > 999)
	{
		return {};
	}
	if(number == 0)
	{
		return {"zero"};
	}
	if(number < 21)
	{
		return numeng[number];
	}
	std::string english;
	if(number > 99)
	{
		english += numeng[number / 100] + " hundred ";
		number = number % 100;
	}
	if(number < 21)
	{
		english += numeng[number];
	}
	else
	{
		english += numeng[(number / 10) + 18];
		english += " " + numeng[number % 10];
	}
	if(english.back() == ' ')
	{
		english.pop_back();
	}
	return english;
}

std::string lookAndSay(std::string_view _number)
{
	std::string runLengthEncoded = runLengthEncode(_number);
	if(runLengthEncoded.empty())
	{
		return runLengthEncoded;
	}

	runLengthEncoded.append(1, ' '); // makes conversion algo easier for last item
	for(char& chr : runLengthEncoded)
	{
		if(chr == ' ')
		{
			chr = '\0';
		}
	}

	std::string separator = "";
	std::string lookAndSay;
	const std::string::const_iterator stringEnd = runLengthEncoded.cend();
	std::string::const_iterator sectionBegin = runLengthEncoded.cbegin();
	while(sectionBegin != stringEnd)
	{
		lookAndSay.append(separator).append(numberToEnglish(sectionBegin.operator->()));
		sectionBegin += strlen(sectionBegin.operator->()) + 1;
		lookAndSay.append(separator = " ").append(numberToEnglish(sectionBegin.operator->()));
		sectionBegin += strlen(sectionBegin.operator->()) + 1;
	}

	return lookAndSay;
}
