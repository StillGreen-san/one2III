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
	 * @brief gets the minimum supported input size for conversion
	 * 
	 * @return size_t minimum supported input size for conversion
	 */
	size_t getMinInputSize() const;

	/**
	 * @brief gets the maximum supported input size for conversion
	 * 
	 * @return size_t maximum supported input size for conversion
	 */
	size_t getMaxInputSize() const;

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
};

class RunLengthEncodingConversion : public ConversionRule
{
public:
	RunLengthEncodingConversion::RunLengthEncodingConversion();

	std::string convert(std::string_view _string) const override;
};

class NumberToEnglishConversion : public ConversionRule
{
public:
	NumberToEnglishConversion::NumberToEnglishConversion();

	std::string convert(std::string_view _string) const override;
};

class AsRunLengthEncodingConversion : public ConversionRule
{
public:
	AsRunLengthEncodingConversion::AsRunLengthEncodingConversion();

	std::string convert(std::string_view _string) const override;
};

class LookAndSay : public ConversionRule
{
public:
	LookAndSay::LookAndSay();

	std::string convert(std::string_view _string) const override;
};

//TODO implement rest of converter.hpp functions as rule
