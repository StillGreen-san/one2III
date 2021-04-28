#include "conversionrule.hpp"
#include "conversionfunctions.hpp"

std::string ConversionRule::convert(RuleType rule, std::string_view string)
{
	switch(rule)
	{
	case RuleType::RomanNumeralConversion:
		return romanNumerals(string);
	case RuleType::RunLengthEncodingConversion:
		return runLengthEncode(string);
	case RuleType::NumberToEnglishConversion:
		return numberToEnglish(string);
	case RuleType::AsRunLengthEncodingConversion:
		return asRunLengthEncode(string);
	case RuleType::LookAndSayConversion:
		return lookAndSay(string);
	case RuleType::AsNumberConversion:
		return std::string(string);
	default:
		return {};
	}
}
