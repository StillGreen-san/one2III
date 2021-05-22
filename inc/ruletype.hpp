#pragma once

#include <string>

/**
 * @brief enumeration of all available rule types
 *
 */
enum class RuleType : uint8_t
{
	/**
	 * @brief converts a number sequence to roman numerals
	 *
	 */
	RomanNumeralConversion,

	/**
	 * @brief returns a number sequence as is
	 *
	 */
	AsNumberConversion,

	/**
	 * @brief interprets a number sequence as run length encoding
	 *
	 */
	AsRunLengthEncodingConversion,

	/**
	 * @brief converts a number sequence to english words
	 *
	 */
	NumberToEnglishConversion,

	/**
	 * @brief converts a number sequence as run length encoding
	 *
	 */
	RunLengthEncodingConversion,

	/**
	 * @brief converts a number sequence as run length encoding
	 *
	 */
	RunLengthDecodingConversion,

	/**
	 * @brief converts a number sequence with run length encoding then to english words
	 *
	 */
	LookAndSayConversion,

	/**
	 * @brief invalid
	 *
	 */
	None
};
