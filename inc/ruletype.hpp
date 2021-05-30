#pragma once

#include <string>

/**
 * @brief enumeration of all available rule types
 *
 */
enum class RuleType : uint8_t
{
	/**
	 * @brief converts a number sequence to roman numerals.
	 * e.g. from '123' to 'CXXIII'
	 *
	 */
	RomanNumeralConversion,

	/**
	 * @brief returns a number sequence as is.
	 * e.g. from '123' to '123'
	 *
	 */
	AsNumberConversion,

	/**
	 * @brief converts a number sequence to english words.
	 * e.g. from '321' to 'three hundred twenty one'
	 *
	 */
	NumberToEnglishConversion,

	/**
	 * @brief converts a number sequence as run length encoding.
	 * e.g. from '335' to '2:2 1:5'
	 *
	 */
	RunLengthEncodingConversion,

	/**
	 * @brief converts a number sequence as run length encoding.
	 * e.g. from '3211' to '2221'
	 *
	 */
	RunLengthDecodingConversion,

	/**
	 * @brief converts a number sequence with run length encoding then to english words.
	 * e.g. from '770' to 'two sevens one zero'
	 *
	 */
	LookAndSayConversion,

	/**
	 * @brief invalid
	 *
	 */
	None
};
