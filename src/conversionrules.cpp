/**
 * @file conversionrules.hpp
 * @brief implementation file for conversion rules
 */

#include "conversionrules.hpp"
#include "converter.hpp"

std::string ConversionRule<RuleType::RomanNumeralConversion>::convert(std::string_view _string) noexcept
{
	return romanNumerals(_string);
}

std::string ConversionRule<RuleType::RunLengthEncodingConversion>::convert(std::string_view _string) noexcept
{
	return runLengthEncode(_string);
}

std::string ConversionRule<RuleType::NumberToEnglishConversion>::convert(std::string_view _string) noexcept 
{
	return numberToEnglish(_string);
}

std::string ConversionRule<RuleType::AsRunLengthEncodingConversion>::convert(std::string_view _string) noexcept
{
	return asRunLengthEncode(_string);
}

//TODO move impl to converter
std::string ConversionRule<RuleType::LookAndSayConversion>::convert(std::string_view _string) noexcept
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

std::string ConversionRule<RuleType::AsNumberConversion>::convert(std::string_view _string) noexcept
{
	return std::string(_string);
}

#pragma region RuleBook

bool RuleBook::add(RuleType _rule) 
{
	if(rules.find(_rule) != rules.end()) return false;
	auto result = emplaceRule(_rule);
	if(result.second == false) return false;
	minInputSize = std::min(minInputSize, result.first->second->getMinInputSize());
	maxInputSize = std::max(maxInputSize, result.first->second->getMaxInputSize());
	return true;
}

size_t RuleBook::getMinInputSize() const
{
	return minInputSize;
}

size_t RuleBook::getMaxInputSize() const
{
	return maxInputSize;
}

RuleBookIterator RuleBook::begin() const
{
	RuleBookIterator iterator;
	iterator.iterator = rules.begin();
	return iterator;
}

RuleBookIterator RuleBook::end() const
{
	RuleBookIterator iterator;
	iterator.iterator = rules.end();
	return iterator;
}

std::pair<std::map<RuleType, std::unique_ptr<ConversionRule>>::iterator, bool> RuleBook::emplaceRule(RuleType _rule) 
{
	switch (_rule)
	{
	case RuleType::AsNumberConversion :
		return rules.emplace(_rule, new AsNumberConversion);
	case RuleType::AsRunLengthEncodingConversion :
		return rules.emplace(_rule, new AsRunLengthEncodingConversion);
	case RuleType::LookAndSayConversion :
		return rules.emplace(_rule, new LookAndSayConversion);
	case RuleType::NumberToEnglishConversion :
		return rules.emplace(_rule, new NumberToEnglishConversion);
	case RuleType::RomanNumeralConversion :
		return rules.emplace(_rule, new RomanNumeralConversion);
	case RuleType::RunLengthEncodingConversion :
		return rules.emplace(_rule, new RunLengthEncodingConversion);
	default: return {std::map<RuleType, std::unique_ptr<ConversionRule>>::iterator(), false};
	}
}

#pragma endregion RuleBook

#pragma region RuleBookIterator

bool RuleBookIterator::operator!=(const RuleBookIterator& _other) const
{
	return iterator != _other.iterator;
}

bool RuleBookIterator::operator==(const RuleBookIterator& _other) const
{
	return iterator == _other.iterator;
}

const ConversionRule* RuleBookIterator::operator->() const
{
	return iterator->second.operator->();
}

const ConversionRule& RuleBookIterator::operator*() const
{
	return iterator->second.operator*();
}

RuleBookIterator& RuleBookIterator::operator--() 
{
	iterator--;
	return *this;
}

RuleBookIterator& RuleBookIterator::operator++() 
{
	iterator++;
	return *this;
}

#pragma endregion RuleBookIterator
