/**
 * @file ruletype.hpp
 * @brief implementation file for RuleType enum
 */

#include <ruletype.hpp>

// TODO use in menu

enumType<RuleType> enumCount(RuleType)
{
	return static_cast<enumType<RuleType>>(RuleType::None);
}

std::string enumName(RuleType _rule)
{
	switch(_rule)
	{
	case RuleType::RomanNumeralConversion:
		return {"RomanNumeralConversion"};
	case RuleType::AsNumberConversion:
		return {"AsNumberConversion"};
	case RuleType::AsRunLengthEncodingConversion:
		return {"AsRunLengthEncodingConversion"};
	case RuleType::NumberToEnglishConversion:
		return {"NumberToEnglishConversion"};
	case RuleType::RunLengthEncodingConversion:
		return {"RunLengthEncodingConversion"};
	case RuleType::LookAndSayConversion:
		return {"LookAndSayConversion"};
	default:
		return {"invalid"};
	}
}

std::string enumDescription(RuleType _rule)
{
	switch(_rule)
	{
	case RuleType::RomanNumeralConversion:
		return {"converts a number sequence to roman numerals"};
	case RuleType::AsNumberConversion:
		return {"returns a number sequence as is"};
	case RuleType::AsRunLengthEncodingConversion:
		return {"interprets a number sequence as run length encoding"};
	case RuleType::NumberToEnglishConversion:
		return {"converts a number sequence to english words"};
	case RuleType::RunLengthEncodingConversion:
		return {"converts a number sequence as run length encoding"};
	case RuleType::LookAndSayConversion:
		return {"converts a number sequence with run length encoding then to english words"};
	default:
		return {"invalid"};
	}
}
