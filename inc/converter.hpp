#pragma once

#include "rulebook.hpp"

#include <functional>

/**
 * @brief static Converster struct with functions for converting a string
 *
 */
struct Converter
{

	/**
	 * @brief estimates the total possible conversions
	 *
	 * @param rules the rules used for conversion
	 * @param string the string to convert
	 * @return size_t the estimated amount of possible conversions (always higher)
	 */
	static size_t estimatePossibilities(const RuleBook& rules, std::string_view string);

	/**
	 * @brief calculate the total possible conversions
	 *
	 * @param rules the rules used for conversion
	 * @param string the string to convert
	 * @return size_t the calcualated amount of possible conversions
	 */
	static size_t calculatePossibilities(const RuleBook& rules, std::string_view string);

	/**
	 * @brief returns a random conversion of all possible ones
	 *
	 * @param rules the rules used for conversion
	 * @param string the string to convert
	 * @return std::string the converted string
	 */
	static std::string randomConversion(const RuleBook& rules, std::string_view string);

	/**
	 * @brief returns the Nth conversion of all possible ones
	 *
	 * @param rules the rules used for conversion
	 * @param string the string to convert
	 * @param number the number(id) to return from all possible conversions
	 * @return std::string the converted string
	 */
	static std::string singleConversion(const RuleBook& rules, std::string_view string, size_t number);

	/**
	 * @brief returns all conversions possible
	 *
	 * @param rules the rules used for conversion
	 * @param string the string to convert
	 * @param outputFunc function called everytime a conversion is created (like output iterator)
	 * @return size_t number of conversions
	 */
	static size_t allConversions(
	    const RuleBook& rules, std::string_view string, std::function<void(std::string&&)> outputFunc);
};
