/**
 * @file conversionstates.hpp
 * @brief include file for conversion state data
 * 
 */

#pragma once

#include "simplemenu.hpp"
#include "rulebook.hpp"

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

//TODO complete rewrite to get options text from options instead of hardcode

namespace ConversionStates
{
static const std::string Glob_action_i = "i";//Info
static const std::string Glob_action_t = "t";//Tets
static const std::string Glob_action_e = "e";//Exit

static const std::string Info_text =
	"\none2III\n"
		"\tgiven a string of digits and a list of conversion rules\n"
		"\tsplit the string into all possible substrings\n"
		"\tconvert every substring using every possible conversion rule\n"
		"\n"
		"\tt: Test\n"
		"\te: Exit\n"
	"\nenter anything to continue";

static const std::string Test_text =
	"\ntest menu\n"
		"\ti: Info\n"
		"\tt: This\n"
		"\tc: Callback\n"
		"\tf: False\n"
		"\te: Exit\n"
	"\nchoose one option";
static const std::string Test_action_c = "c";
static const std::string Test_action_f = "f";

static const std::string Nums_text =
	"\nNumber Sequence\n"
		"\te: Exit\n"
	"\nenter a number sequence";
static std::string numberSequence;
bool Nums_validate(std::string_view _sequence);

static const std::string Rule_text =
	"\nSelect a Rule to add\n"
		"\trnc: RomanNumeralConversion\n"
		"\tanc: AsNumberConversion\n"
		"\tarl: AsRunLengthEncodingConversion\n"
		"\tnte: NumberToEnglishConversion\n"
		"\trle: RunLengthEncodingConversion\n"
		"\tlas: LookAndSayConversion\n"
		"\n"
		"\tc: Convert\n"
		"\te: Exit\n"
	"\nchoose one option";
static const std::string Rule_action_rnc = "rnc";
static const std::string Rule_action_anc = "anc";
static const std::string Rule_action_arl = "arl";
static const std::string Rule_action_nte = "nte";
static const std::string Rule_action_rle = "rle";
static const std::string Rule_action_las = "las";
static const std::string Rule_action_c = "c";
static RuleBook rulebook;
bool Rule_handle(std::string_view _sequence);

static const std::string Conv_text =
	"\none2III\n"
	"\nenter anything to show all conversions";
// bool Conv_show(std::string_view _sequence);//TODO implmnt

static const std::string Exit_text =
	"\none2III\n"
	"\nenter anything to exit";

static const SimpleMenu::State Info
{
	Info_text,
	{
		{
			Glob_action_t,
			nullptr,
			Test_text
		},
		{
			Glob_action_e,
			nullptr,
			Exit_text
		},
		{
			{nullptr, 0},
			nullptr,
			Nums_text
		}
	}
};

static size_t trueCounter = 0;
bool trueCallback(std::string_view _string);
static size_t falseCounter = 0;
bool falseCallback(std::string_view _string);
static const SimpleMenu::State Test
{
	Test_text,
	{
		{
			Glob_action_t,
			nullptr,
			Test_text
		},
		{
			Glob_action_i,
			nullptr,
			Info_text
		},
		{
			Test_action_c,
			trueCallback,
			Test_text
		},
		{
			Test_action_f,
			falseCallback,
			Test_text
		},
		{
			Glob_action_e,
			nullptr,
			Exit_text
		}
	}
};

static const SimpleMenu::State Exit
{
	Exit_text,
	{
		{
			{nullptr, 0},
			nullptr,
			{nullptr, 0}
		}
	}
};

static const SimpleMenu::State Conv//TODO implmnt
{
	Conv_text,
	{
		{
			{nullptr, 0},
			nullptr,
			{nullptr, 0}
		}
	}
};

static const SimpleMenu::State Rule
{
	Rule_text,
	{
		{
			Rule_action_c,
			nullptr,
			Conv_text
		},
		{
			Glob_action_e,
			nullptr,
			Exit_text
		},
		{
			{nullptr, 0},
			Rule_handle,
			Rule_text
		}
	}
};

static const SimpleMenu::State Nums
{
	Nums_text,
	{
		{
			Glob_action_e,
			nullptr,
			Exit_text
		},
		{
			{nullptr, 0},//TODO make glob placeholders for nullptr text & external
			Nums_validate,
			Rule_text
		}
	}
};

} // namespace ConversionStates
