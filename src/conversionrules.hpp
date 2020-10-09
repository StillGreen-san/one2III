/**
 * @file conversionrules.hpp
 * @brief include file for conversion rules
 */

#pragma once

#include <string>

/**
 * @brief base class for all conversion rules
 */
class ConversionRule
{
public:
	ConversionRule() = delete;

	virtual std::string convert(std::string_view _string) const = 0;

	/**
	 * @brief checks if the string can be converted by this rule
	 * 
	 * @param _string the string to be converted
	 * @return true if the string can be converted
	 * @return false otherwise
	 */
	virtual bool canBeConverted(std::string_view _string) const;

protected:
	ConversionRule(size_t _minInputSize, size_t _maxInputSize);

	const size_t minInputSize;
	const size_t maxInputSize;
};

class RomanNumeralConversion : public ConversionRule
{
public:
	RomanNumeralConversion::RomanNumeralConversion();

	std::string convert(std::string_view _string) const override;

	bool canBeConverted(std::string_view _string) const override;
};

class RunLengthEncodingConversion : public ConversionRule
{
public:
	RunLengthEncodingConversion::RunLengthEncodingConversion();

	std::string convert(std::string_view _string) const override;
};

//TODO implement rest of converter.hpp functions as rule
