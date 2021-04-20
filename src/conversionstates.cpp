/**
 * @file conversionstates.hpp
 * @brief implementation file for conversion state functions
 */

#include "conversionstates.hpp"
#include "helperfunctions.hpp"

#include <iostream>

namespace ConversionStates
{
std::string numberSequence;
bool Nums_validate(std::string_view _sequence)
{
	if(isValidNumberSequence(_sequence))
	{
		numberSequence = _sequence;
		return true;
	}
	return false;
}

std::string Nums_get()
{
	return numberSequence;
}

RuleBook rulebook;
bool Rule_handle(std::string_view _sequence)
{
	if(_sequence == Rule_action_anc)
	{
		rulebook.add(RuleType::AsNumberConversion);
		return true;
	}
	if(_sequence == Rule_action_arl)
	{
		rulebook.add(RuleType::AsRunLengthEncodingConversion);
		return true;
	}
	if(_sequence == Rule_action_las)
	{
		rulebook.add(RuleType::LookAndSayConversion);
		return true;
	}
	if(_sequence == Rule_action_nte)
	{
		rulebook.add(RuleType::NumberToEnglishConversion);
		return true;
	}
	if(_sequence == Rule_action_rle)
	{
		rulebook.add(RuleType::RunLengthEncodingConversion);
		return true;
	}
	if(_sequence == Rule_action_rnc)
	{
		rulebook.add(RuleType::RomanNumeralConversion);
		return true;
	}
	return false;
}

RuleBook& Rule_get()
{
	return rulebook;
}

size_t trueCounter = 0;
bool trueCallback(std::string_view _string)
{
	++trueCounter;
	std::cout << " ~ trueCounter: " << trueCounter << "\n";
	return true;
}

size_t falseCounter = 0;
bool falseCallback(std::string_view _string)
{
	++falseCounter;
	std::cout << " ~ falseCounter: " << falseCounter << "\n";
	return false;
}
} // namespace ConversionStates