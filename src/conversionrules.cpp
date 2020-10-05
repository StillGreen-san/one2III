/**
 * @file conversionrules.hpp
 * @brief implementation file for conversion rules
 */

#include "conversionrules.hpp"

ConversionRule::ConversionRule(size_t _minInputSize, size_t _maxInputSize) :
	minInputSize{_minInputSize},
	maxInputSize{_maxInputSize}
{
	
}

size_t ConversionRule::getMinInputSize()
{
	return minInputSize;
}

size_t ConversionRule::getMaxInputSize()
{
	return maxInputSize;
}

bool ConversionRule::canBeConverted(std::string_view _string)
{
	return _string.size() >= minInputSize
		&& _string.size() <= maxInputSize;
}
