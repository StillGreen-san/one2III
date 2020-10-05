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
	ConversionRule(size_t _minInputSize, size_t _maxInputSize);

	virtual std::string convert(std::string_view _string) = 0;

	/**
	 * @brief gets the minimum supported input size for conversion
	 * 
	 * @return size_t minimum supported input size for conversion
	 */
	size_t getMinInputSize();

	/**
	 * @brief gets the maximum supported input size for conversion
	 * 
	 * @return size_t maximum supported input size for conversion
	 */
	size_t getMaxInputSize();

	/**
	 * @brief checks if the string can be converted by this rule
	 * 
	 * @param _string the string to be converted
	 * @return true if the string can be converted
	 * @return false otherwise
	 */
	bool canBeConverted(std::string_view _string);

protected:
	size_t minInputSize;
	size_t maxInputSize;
};
