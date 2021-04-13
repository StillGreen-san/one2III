/**
 * @file conversionrule.hpp
 * @brief implementation file for ConversionRule
 */

#include "conversionrule.hpp"
#include "conversionfunctions.hpp"

std::string ConversionRule::convert(RuleType _rule, std::string_view _string)
{
	switch(_rule)
	{
	case RuleType::RomanNumeralConversion:
		return romanNumerals(_string);
	case RuleType::RunLengthEncodingConversion:
		return runLengthEncode(_string);
	case RuleType::NumberToEnglishConversion:
		return numberToEnglish(_string);
	case RuleType::AsRunLengthEncodingConversion:
		return asRunLengthEncode(_string);
	case RuleType::LookAndSayConversion:
		return lookAndSay(_string);
	case RuleType::AsNumberConversion:
		return std::string(_string);
	default:
		return {};
	}
}
