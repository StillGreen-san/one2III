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

bool ConversionRule::canBeConverted(std::string_view _string) const
{
	size_t size = _string.size();
	return size >= minInputSize
		&& size <= maxInputSize;
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

bool RomanNumeralConversion::canBeConverted(std::string_view _string) const 
{
	size_t size = _string.size();
	if(size == maxInputSize)
		return _string.front() <= '3';
	return size >= minInputSize
		&& size <= maxInputSize;
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
