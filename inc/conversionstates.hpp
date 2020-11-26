/**
 * @file conversionstates.hpp
 * @brief include file for conversion state data
 * 
 */

#pragma once

#include "simplemenu.hpp"

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

//TODO support for dynamic text
//TODO check if string can be char*

namespace ConversionStates
{

static const std::string Info_text =
	"\none2III\n"
		"\tgiven a string of digits and a list of conversion rules\n"
		"\tsplit the string into all possible substrings\n"
		"\tconvert every substring using every possible conversion rule\n"
	"\nenter anything to continue";

static const std::string Test_text =
	"\ntest menu\n"
		"\ti: Info\n"
		"\tt: This\n"
		"\tc: Callback\n"
		"\te: Exit\n"
	"\nchoose one option";
static const std::string Test_action_i = "i";
static const std::string Test_action_t = "t";
static const std::string Test_action_c = "c";
static const std::string Test_action_e = "e";

static const std::string Exit_text =
	"\none2III\n"
	"\nenter anything to exit";

static const SimpleState Info
{
	Info_text,
	{
		{
			nullptr,
			nullptr,
			Test_text
		}
	}
};

static size_t testCounter = 0;
static void testCallback(std::string_view _string){
	++testCounter;
}
static const SimpleState Test
{
	Test_text,
	{
		{
			Test_action_t,
			nullptr,
			Test_text
		},
		{
			Test_action_i,
			nullptr,
			Info_text
		},
		{
			Test_action_c,
			testCallback,
			Info_text
		},
		{
			Test_action_e,
			nullptr,
			Exit_text
		}
	}
};

static const SimpleState Exit
{
	Exit_text,
	{
		{
			nullptr,
			nullptr,
			nullptr
		}
	}
};

} // namespace ConversionStates