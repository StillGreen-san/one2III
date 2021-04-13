/**
 * @file conversionstates.hpp
 * @brief include file for conversion state data
 *
 */

#pragma once

#include "rulebook.hpp"
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

// TODO support for dynamic text
// TODO check if string can be char*

// TODO complete rewrite to get options text from options instead of hardcode

namespace ConversionStates
{
const std::string Glob_action_i = "i"; // Info
const std::string Glob_action_t = "t"; // Test
const std::string Glob_action_e = "e"; // Exit

const std::string Info_text = "\none2III\n"
                              "\tgiven a string of digits and a list of conversion rules\n"
                              "\tsplit the string into all possible substrings\n"
                              "\tconvert every substring using every possible conversion rule\n"
                              "\n"
                              "\tt: Test\n"
                              "\te: Exit\n"
                              "\nenter anything to continue";

const std::string Test_text = "\ntest menu\n"
                              "\ti: Info\n"
                              "\tt: This\n"
                              "\tc: Callback\n"
                              "\tf: False\n"
                              "\te: Exit\n"
                              "\nchoose one option";
const std::string Test_action_c = "c";
const std::string Test_action_f = "f";

const std::string Nums_text = "\nNumber Sequence\n"
                              "\te: Exit\n"
                              "\nenter a number sequence";
bool Nums_validate(std::string_view _sequence);
std::string Nums_get();

const std::string Rule_text = "\nSelect a Rule to add\n"
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
const std::string Rule_action_rnc = "rnc";
const std::string Rule_action_anc = "anc";
const std::string Rule_action_arl = "arl";
const std::string Rule_action_nte = "nte";
const std::string Rule_action_rle = "rle";
const std::string Rule_action_las = "las";
const std::string Rule_action_c = "c";
bool Rule_handle(std::string_view _sequence);
RuleBook& Rule_get();

const std::string Conv_text = "\none2III\n"
                              "\nenter anything to show all conversions";
// bool Conv_show(std::string_view _sequence);//TODO implmnt

const std::string Exit_text = "\none2III\n"
                              "\nenter anything to exit";

const std::string STRING_TEST = "1234567890";

const SimpleMenu::State Info{
    Info_text,
    {{Glob_action_t, nullptr, Test_text}, {Glob_action_e, nullptr, Exit_text}, {{nullptr, 0}, nullptr, Nums_text}}};

bool trueCallback(std::string_view _string);
bool falseCallback(std::string_view _string);
const SimpleMenu::State Test{
    Test_text,
    {{Glob_action_t, nullptr, Test_text},
     {Glob_action_i, nullptr, Info_text},
     {Test_action_c, trueCallback, Test_text},
     {Test_action_f, falseCallback, Test_text},
     {Glob_action_e, nullptr, Exit_text}}};

const SimpleMenu::State Exit{Exit_text, {{{nullptr, 0}, nullptr, {nullptr, 0}}}};

const SimpleMenu::State Conv // TODO implmnt
    {Conv_text, {{{nullptr, 0}, nullptr, {nullptr, 0}}}};

const SimpleMenu::State Rule{
    Rule_text,
    {{Rule_action_c, nullptr, Conv_text}, {Glob_action_e, nullptr, Exit_text}, {{nullptr, 0}, Rule_handle, Rule_text}}};

const SimpleMenu::State Nums{
    Nums_text,
    {{Glob_action_e, nullptr, Exit_text},
     {{nullptr, 0}, // TODO make glob placeholders for nullptr text & external
      Nums_validate,
      Rule_text}}};

} // namespace ConversionStates
