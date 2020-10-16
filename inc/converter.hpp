/**
 * @file converter.hpp
 * @brief include file for Converter static struct
 */

#pragma once

#include <string>

#include "rulebook.hpp"

/**
 * @brief static Converster struct with functions for converting a string
 * 
 */
struct Converter
{

	/**
	 * @brief estimates the total possible conversions
	 * 
	 * @param _rules the rules used for conversion
	 * @param _string the string to convert
	 * @return size_t the estimated amount of possible conversions (always higher)
	 */
	static size_t estimatePossibilities(const RuleBook& _rules, std::string_view _string);

	/**
	 * @brief calculate the total possible conversions
	 * 
	 * @param _rules the rules used for conversion
	 * @param _string the string to convert
	 * @return size_t the calcualated amount of possible conversions
	 */
	static size_t calculatePossibilities(const RuleBook& _rules, std::string_view _string);

	/**
	 * @brief returns a random conversion of all possible ones
	 * 
	 * @param _rules the rules used for conversion
	 * @param _string the string to convert
	 * @return std::string the converted string
	 */
	static std::string randomConversion(const RuleBook& _rules, std::string_view _string);

	/**
	 * @brief returns the Nth conversion of all possible ones 
	 * 
	 * @param _rules the rules used for conversion
	 * @param _string the string to convert
	 * @param _number the number(id) to return from all possible conversions
	 * @return std::string the converted string
	 */
	static std::string singleConversion(const RuleBook& _rules, std::string_view _string, size_t _number);
	
};
