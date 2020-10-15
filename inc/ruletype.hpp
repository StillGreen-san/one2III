/**
 * @file ruletype.hpp
 * @brief include file for RuleType enum
 */

#pragma once

#include <cstdint>

/**
 * @brief enumeration of all available rule types
 * 
 */
enum class RuleType : uint8_t
{
	RomanNumeralConversion, /* converts a number sequence to roman numerals */
	AsNumberConversion, /* returns a number sequence as is */
	AsRunLengthEncodingConversion, /* interprets a number sequence as run length encoding */
	NumberToEnglishConversion, /* converts a number sequence to english words */
	RunLengthEncodingConversion, /* converts a number sequence to english words */
	LookAndSayConversion, /* converts a number sequence with run length encoding then to english words */

	None /* invalid */
};
