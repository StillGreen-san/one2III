/**
 * @file conversionrules.hpp
 * @brief implementation file for conversion rules
 */

#include "conversionrules.hpp"
#include "converter.hpp"

#pragma region ConversionRule

ConversionRule::ConversionRule(size_t _minInputSize, size_t _maxInputSize) :
	minInputSize{_minInputSize},
	maxInputSize{_maxInputSize}
{
	
}

size_t ConversionRule::getMinInputSize() const
{
	return minInputSize;
}

size_t ConversionRule::getMaxInputSize() const
{
	return maxInputSize;
}

bool ConversionRule::canBeConverted(std::string_view _string) const
{
	return _string.size() >= minInputSize
		&& _string.size() <= maxInputSize;
}

#pragma endregion ConversionRule

#pragma region RomanNumeralConversion

RomanNumeralConversion::RomanNumeralConversion() :
	ConversionRule::ConversionRule(1, 4)
{

}

std::string RomanNumeralConversion::convert(std::string_view _string) const
{
	return romanNumerals(_string);
}

#pragma endregion RomanNumeralConversion

#pragma region RunLengthEncodingConversion

RunLengthEncodingConversion::RunLengthEncodingConversion() :
	ConversionRule::ConversionRule(1, std::numeric_limits<size_t>::max())
{

}

std::string RunLengthEncodingConversion::convert(std::string_view _string) const
{
	return runLengthEncode(_string);
}

#pragma endregion RunLengthEncodingConversion
