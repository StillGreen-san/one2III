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

std::string romanNumerals(std::string_view _number) 
{
	if(_number.size() > 4 || _number.size() < 1 || (_number.size() == 4 && _number[0] > '3')) return {}; //TODO handle leading zeros
	static const std::vector<std::pair<unsigned short, const char*>> roman //TODO? make array?
	{
		{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
		{100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
		{10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
	};
	std::string converted{};
	unsigned short number = std::stoul(std::string(_number)); //TODO find way without converting?
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
