/**
 * @file conversionstates.hpp
 * @brief include file for conversion state data
 * 
 */

#pragma once

#include <string>

//  struct SimpleState
//  {
//  	std::string_view text;
//  	struct Action
//  	{
//  		std::string_view input;
//  		void(*external)(std::string_view);
//  		std::string_view state;
//  	};
//  	std::vector<Action> inputmap;
//  };

namespace Info
{
	static const std::string text =
		"\none2III\n"
			"\tgiven a string of digits and a list of conversion rules\n"
			"\tsplit the string into all possible substrings\n"
			"\tconvert every substring using every possible conversion rule\n"
		"\nenter anything to continue";
	
} // namespace Info


