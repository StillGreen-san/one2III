#pragma once

#include "rulebook.hpp"

#include <functional>

/**
 * @brief namespace for converting a string
 *
 */
namespace Converter
{
/**
 * @brief estimates the total possible conversions
 *
 * @param rules the rules used for conversion
 * @param string the string to convert
 * @return size_t the estimated amount of possible conversions (always higher than actual)
 */
size_t estimatePossibilities(const RuleBook& rules, std::string_view string);

/**
 * @brief calculates the total possible conversions
 *
 * @param rules the rules used for conversion
 * @param string the string to convert
 * @return size_t the calcualated amount of possible conversions
 */
size_t calculatePossibilities(const RuleBook& rules, std::string_view string);

/**
 * @brief returns a random conversion of all possible ones
 *
 * @param rules the rules used for conversion
 * @param string the string to convert
 * @return std::string the converted string
 */
std::string randomConversion(const RuleBook& rules, std::string_view string);

/**
 * @brief returns the Nth conversion of all possible ones
 *
 * @param rules the rules used for conversion
 * @param string the string to convert
 * @param number the number(id) to return from all possible conversions
 * @return std::string the converted string
 */
std::string singleConversion(const RuleBook& rules, std::string_view string, size_t number);

/**
 * @brief generates all possible conversions and sends them to outputFunc
 *
 * @param rules the rules used for conversion
 * @param string the string to convert
 * @param outputFunc function called everytime a conversion is created (like output iterator),
 * returns false to stop conversions
 * @return size_t number of conversions
 */
size_t allConversions(
    const RuleBook& rules, std::string_view string, const std::function<bool(std::string&&)>& outputFunc);
}; // namespace Converter
