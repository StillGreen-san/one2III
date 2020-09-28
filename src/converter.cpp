/**
 * @file convert.cpp
 * @brief implementation file for conversion functions
 */

#include "converter.hpp"

std::string runLengthEncode(const std::string_view _number) 
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
