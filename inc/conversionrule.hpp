#pragma once

#include <string>

#include "ruletype.hpp"

/**
 * @brief static struct to handle conversion rules
 *
 */
struct ConversionRule
{
	ConversionRule() = delete;
	ConversionRule(ConversionRule&&) = delete;
	ConversionRule(const ConversionRule&) = delete;
	ConversionRule& operator=(ConversionRule&&) = delete;
	ConversionRule& operator=(const ConversionRule&) = delete;
	~ConversionRule() = delete;

	/**
	 * @brief returns a number sequence converted according to rule type
	 *
	 * @param rule the rule type to convert by
	 * @param string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(RuleType rule, std::string_view string);

	/**
	 * @brief returns the minimum supported input size for conversion with rule type
	 *
	 * @param rule the rule type to return the minimum supported input size for
	 * @return constexpr size_t the minimum supported input size for conversion with rule type
	 */
	static constexpr size_t minInputSize(RuleType rule) noexcept
	{
		switch(rule)
		{
		case RuleType::RomanNumeralConversion:
		case RuleType::RunLengthEncodingConversion:
		case RuleType::NumberToEnglishConversion:
		case RuleType::LookAndSayConversion:
		case RuleType::AsNumberConversion:
			return 1;
		case RuleType::AsRunLengthEncodingConversion:
		case RuleType::RunLengthDecodingConversion:
			return 2;
		default:
			return std::numeric_limits<size_t>::max();
		}
	}

	/**
	 * @brief returns the maximum supported input size for conversion with rule type
	 *
	 * @param rule the rule type to return the maximum supported input size for
	 * @return constexpr size_t the maximum supported input size for conversion with rule type
	 */
	static constexpr size_t maxInputSize(RuleType rule) noexcept
	{
		switch(rule)
		{
		case RuleType::RomanNumeralConversion:
			return 4;
		case RuleType::NumberToEnglishConversion:
			return 3;
		case RuleType::AsRunLengthEncodingConversion:
		case RuleType::LookAndSayConversion:
		case RuleType::AsNumberConversion:
			return std::numeric_limits<size_t>::max();
		case RuleType::RunLengthEncodingConversion:
		case RuleType::RunLengthDecodingConversion:
			return std::numeric_limits<size_t>::max() - 1;
		default:
			return std::numeric_limits<size_t>::min();
		}
	}
};
