/**
 * @file conversionrules.hpp
 * @brief include file for conversion rules
 */

#pragma once

#include <string>
#include <set>

/**
 * @brief enumeration of all available rule types
 * 
 */
enum class RuleType : uint8_t
{
	RomanNumeralConversion, /* converts a number sequence to roman numerals */
	AsNumberConversion, /* returns a number sequence as is */
	AsRunLengthEncodingConversion, /* interprets a number sequence as run length encoding */
	NumberToEnglishConversion, /* converts a number sequence to english words */
	RunLengthEncodingConversion, /* converts a number sequence to english words */
	LookAndSayConversion, /* converts a number sequence with run length encoding then to english words */

	None /* invalid */
};

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

/**
 * @brief class to store multiple rules in on place
 * 
 */
class RuleBook
{
public:
	/**
	 * @brief add a conversion rule to the collection
	 * 
	 * @param _rule the conversion rule type to add
	 * @return true if rule was added
	 * @return false if was rule already added
	 */
	bool add(RuleType _rule);

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

	/**
	 * @brief returns an iterator to the first rule 
	 * 
	 * @return std::set<RuleType>::const_iterator 
	 */
	std::set<RuleType>::const_iterator begin() const;

	/**
	 * @brief returns an iterator to one past the last rule
	 * 
	 * @return std::set<RuleType>::const_iterator 
	 */
	std::set<RuleType>::const_iterator end() const;
private:
	/**
	 * @brief !INTERNAL! set to store all added rules
	 * 
	 */
	std::set<RuleType> rules;

	/**
	 * @brief !INTERNAL! the minimum supported input size for conversion
	 * 
	 */
	size_t minInputSize = std::numeric_limits<size_t>::max();

	/**
	 * @brief !INTERNAL! the maximum supported input size for conversion
	 * 
	 */
	size_t maxInputSize = std::numeric_limits<size_t>::min();
};
