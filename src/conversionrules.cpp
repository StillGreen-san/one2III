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

#pragma region NumberToEnglishConversion

NumberToEnglishConversion::NumberToEnglishConversion() :
	ConversionRule::ConversionRule(1, 3)
{

}

std::string NumberToEnglishConversion::convert(std::string_view _string) const 
{
	return numberToEnglish(_string);
}

#pragma endregion NumberToEnglishConversion

#pragma region AsRunLengthEncodingConversion

AsRunLengthEncodingConversion::AsRunLengthEncodingConversion() :
	ConversionRule::ConversionRule(2, std::numeric_limits<size_t>::max())
{

}

std::string AsRunLengthEncodingConversion::convert(std::string_view _string) const
{
	return asRunLengthEncode(_string);
}

#pragma endregion AsRunLengthEncodingConversion

#pragma region LookAndSay

LookAndSayConversion::LookAndSayConversion() :
	ConversionRule::ConversionRule(1, std::numeric_limits<size_t>::max())
{

}

std::string LookAndSayConversion::convert(std::string_view _string) const
{
	std::string runLengthEncoded = runLengthEncode(_string);
	if(runLengthEncoded == "") return runLengthEncoded;
	const size_t sectionHalf = 1;
	std::string separator = "";
	std::string lookAndSay;
	auto stringEnd = std::remove(begin(runLengthEncoded), end(runLengthEncoded), ' ');
	auto sectionBegin = begin(runLengthEncoded);
	while(sectionBegin != stringEnd)
	{
		lookAndSay
			.append(separator)
			.append(numberToEnglish(std::string_view(&*sectionBegin , sectionHalf)));
		std::advance(sectionBegin, sectionHalf);
		lookAndSay
			.append(separator = " ")
			.append(numberToEnglish(std::string_view(&*sectionBegin , sectionHalf)));
		std::advance(sectionBegin, sectionHalf);
	}
	return lookAndSay;
}

#pragma endregion LookAndSay

#pragma region AsNumber

AsNumberConversion::AsNumberConversion() :
	ConversionRule::ConversionRule(1, std::numeric_limits<size_t>::max())
{

}

std::string AsNumberConversion::convert(std::string_view _string) const
{
	return std::string(_string);
}

#pragma endregion AsNumber
