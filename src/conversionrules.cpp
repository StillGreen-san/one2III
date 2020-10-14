/**
 * @file conversionrules.hpp
 * @brief implementation file for conversion rules
 */

#include "conversionrules.hpp"
#include "converter.hpp"

#pragma region ConversionRule

std::string ConversionRule::convert(RuleType _rule, std::string_view _string)
{
	switch(_rule)
	{
	case RuleType::RomanNumeralConversion :
		return romanNumerals(_string);
	case RuleType::RunLengthEncodingConversion :
		return runLengthEncode(_string);
	case RuleType::NumberToEnglishConversion :
		return numberToEnglish(_string);
	case RuleType::AsRunLengthEncodingConversion :
		return asRunLengthEncode(_string);
	case RuleType::LookAndSayConversion :
		return lookAndSay(_string);
	case RuleType::AsNumberConversion :
		return std::string(_string);
	default: return {};
	}
}

#pragma endregion ConversionRule

#pragma region RuleBook

bool RuleBook::add(RuleType _rule) 
{
	if(_rule == RuleType::None) return false;
	auto result = rules.insert(_rule);
	if(result.second == false) return false;
	minInputSize = std::min(minInputSize, ConversionRule::minInputSize(*(result.first)));
	maxInputSize = std::max(maxInputSize, ConversionRule::maxInputSize(*(result.first)));
	return true;
}

size_t RuleBook::getMinInputSize() const
{
	return minInputSize;
}

size_t RuleBook::getMaxInputSize() const
{
	return maxInputSize;
}

std::set<RuleType>::const_iterator RuleBook::begin() const
{
	return rules.cbegin();
}

std::set<RuleType>::const_iterator RuleBook::end() const
{
	return rules.cend();
}

#pragma endregion RuleBook
