/**
 * @file conversionrule.hpp
 * @brief include file for ConversionRule static struct
 */

#pragma once

#include <string>

#include "ruletype.hpp"

/**
 * @brief static struct to handle conversion rules
 * 
 */
struct ConversionRule
{
	/**
	 * @brief returns a number sequence converted according to rule type
	 * 
	 * @param _rule the rule type to convert by
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(RuleType _rule, std::string_view _string);//TODO make inline also?

	/**
	 * @brief returns the minimum supported input size for conversion with rule type
	 * 
	 * @param _rule the rule type to return the minimum supported input size for
	 * @return constexpr size_t the minimum supported input size for conversion with rule type
	 */
	static constexpr size_t minInputSize(RuleType _rule) noexcept
	{
		switch(_rule)
		{
		case RuleType::RomanNumeralConversion :
			return 1;
		case RuleType::RunLengthEncodingConversion :
			return 1;
		case RuleType::NumberToEnglishConversion :
			return 1;
		case RuleType::AsRunLengthEncodingConversion :
			return 2;
		case RuleType::LookAndSayConversion :
			return 1;
		case RuleType::AsNumberConversion :
			return 1;
		default:
			return std::numeric_limits<size_t>::max();
		}
	}

	/**
	 * @brief returns the maximum supported input size for conversion with rule type
	 * 
	 * @param _rule the rule type to return the maximum supported input size for
	 * @return constexpr size_t the maximum supported input size for conversion with rule type
	 */
	static constexpr size_t maxInputSize(RuleType _rule) noexcept
	{
		switch(_rule)
		{
		case RuleType::RomanNumeralConversion :
			return 4;
		case RuleType::RunLengthEncodingConversion :
			return std::numeric_limits<size_t>::max();
		case RuleType::NumberToEnglishConversion :
			return 3;
		case RuleType::AsRunLengthEncodingConversion :
			return std::numeric_limits<size_t>::max();
		case RuleType::LookAndSayConversion :
			return std::numeric_limits<size_t>::max();
		case RuleType::AsNumberConversion :
			return std::numeric_limits<size_t>::max();
		default:
			return std::numeric_limits<size_t>::min();
		}
	}
};