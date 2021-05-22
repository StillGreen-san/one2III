#include <algorithm>
#include <vector>

#include "conversionfunctions.hpp"

std::string runLengthEncode(std::string_view number)
{
	if(number.empty())
	{
		return {};
	}

	const size_t size = number.size();
	std::string encoded;
	uint32_t groupCount = 1;
	for(size_t i = 1; i < size; ++i)
	{
		if(number[i - 1] == number[i])
		{
			++groupCount;
		}
		else
		{
			encoded.append(std::to_string(groupCount)).append(1, ' ').append(1, number[i - 1]).append(1, ' ');
			groupCount = 1;
		}
	}
	encoded.append(std::to_string(groupCount)).append(1, ' ').append(1, number[size - 1]);

	return encoded;
}

std::string runLengthDecode(std::string_view number)
{
	const size_t size = number.size();
	if(size == 0 || size % 2 != 0)
	{
		return {};
	}

	std::string decoded;

	unsigned count = 0;
	for(char n : number)
	{
		if(count == 0)
		{
			count = n - '0';
			if(count == 0)
			{
				return {};
			}
		}
		else
		{
			decoded.append(count, n);
			count = 0;
		}
	}

	return decoded;
}

std::string asRunLengthEncode(std::string_view number)
{
	const size_t size = number.size();
	if(size == 0 || size % 2 != 0)
	{
		return {};
	}

	for(size_t i = 3; i < size; ++i)
	{
		if(number[i - 2] == number[i])
		{
			return {};
		}
	}

	std::string converted;
	converted.reserve((size * 2) - 1);
	for(const char chr : number)
	{
		converted.append(1, chr).append(1, ' ');
	}
	converted.pop_back();

	return converted;
}

std::string romanNumerals(std::string_view number)
{
	static const std::vector<std::pair<int, const char*>> roman{{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
	    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
	constexpr auto MIN_ROMAN_INT = 1ULL;
	constexpr auto MAX_ROMAN_INT = 3999ULL;

	if(number.empty())
	{
		return {};
	}

	auto integer = std::stoull(std::string(number));
	if(integer < MIN_ROMAN_INT || integer > MAX_ROMAN_INT)
	{
		return {};
	}

	std::string converted;
	for(const auto& r : roman)
	{
		while(integer >= r.first)
		{
			integer -= r.first;
			converted += r.second;
		}
		if(integer == 0)
		{
			break;
		}
	}

	return converted;
}

std::string numberToEnglish(std::string_view number)
{
	static const std::vector<std::string> numeng{"", "one", "two", "three", "four", "five", "six", "seven", "eight",
	    "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
	    "nineteen", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
	constexpr auto TENTH_OFFSET = 18ULL;
	constexpr auto MAX_ENG_INT = 999ULL;

	if(number.empty())
	{
		return {};
	}

	auto integer = std::stoull(std::string(number));
	if(integer > MAX_ENG_INT)
	{
		return {};
	}
	if(integer == 0)
	{
		return {"zero"};
	}
	if(integer < 21)
	{
		return numeng[integer];
	}

	std::string english;
	if(integer > 99)
	{
		english += numeng[integer / 100] + " hundred ";
		integer = integer % 100;
	}
	if(integer < 21)
	{
		english += numeng[integer];
	}
	else
	{
		english += numeng[(integer / 10) + TENTH_OFFSET];
		english += " " + numeng[integer % 10];
	}
	if(english.back() == ' ')
	{
		english.pop_back();
	}

	return english;
}

std::string lookAndSay(std::string_view number)
{
	std::string runLengthEncoded = runLengthEncode(number);
	if(runLengthEncoded.empty())
	{
		return runLengthEncoded;
	}

	runLengthEncoded.append(1, ' '); // makes conversion algo easier for last item
	std::replace(std::begin(runLengthEncoded), std::end(runLengthEncoded), ' ', '\000');

	std::string separator;
	std::string lookAndSay;
	const std::string::const_iterator stringEnd = runLengthEncoded.cend();
	std::string::const_iterator sectionBegin = runLengthEncoded.cbegin();
	while(sectionBegin != stringEnd)
	{
		const std::string& firstNumber = numberToEnglish(sectionBegin.operator->());

		lookAndSay.append(separator).append(firstNumber);
		sectionBegin += strlen(sectionBegin.operator->()) + 1;

		const std::string& secondNumber = numberToEnglish(sectionBegin.operator->());
		lookAndSay.append(separator = " ").append(secondNumber);
		sectionBegin += strlen(sectionBegin.operator->()) + 1;

		if(firstNumber != "one")
		{
			if(secondNumber == "six")
			{
				lookAndSay.append(1, 'e');
			}
			lookAndSay.append(1, 's');
		}
	}

	return lookAndSay;
}
