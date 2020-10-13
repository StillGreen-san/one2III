/**
 * @file conversionrules.hpp
 * @brief include file for conversion rules
 */

#pragma once

#include <string>
#include <map>
#include <memory>

//TODO make rules as constexpr function object template

/**
 * @brief enumeration of all available rule types
 * 
 */
enum class RuleType : uint8_t
{
	RomanNumeralConversion,
	AsNumberConversion,
	AsRunLengthEncodingConversion,
	NumberToEnglishConversion,
	RunLengthEncodingConversion,
	LookAndSayConversion,

	None
};

/**
 * @brief template for conversion rules
 * 
 * @tparam _RT one of RuleType
 */
template<RuleType _RT>
struct ConversionRule
{
	/* non specialized template should not be used */
};

/**
 * @brief specialized template for conversion rules see convert
 * 
 * @tparam RuleType::RomanNumeralConversion
 */
template<>
struct ConversionRule<RuleType::RomanNumeralConversion>
{
	/**
	 * @brief returns a number sequence converted to roman numerals
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(std::string_view _string) noexcept;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t minInputSize = 1;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t maxInputSize = 4;
};

/**
 * @brief specialized template for conversion rules see convert
 * 
 * @tparam RuleType::AsNumberConversion
 */
template<>
struct ConversionRule<RuleType::AsNumberConversion>
{
	/**
	 * @brief returns a number sequence as is
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(std::string_view _string) noexcept;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t minInputSize = 1;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t maxInputSize = std::numeric_limits<size_t>::max();
};

/**
 * @brief specialized template for conversion rules see convert
 * 
 * @tparam RuleType::RunLengthEncodingConversion
 */
template<>
struct ConversionRule<RuleType::RunLengthEncodingConversion>
{
	/**
	 * @brief returns a number sequence converted with run length encoding
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(std::string_view _string) noexcept;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t minInputSize = 1;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t maxInputSize = std::numeric_limits<size_t>::max();
};

/**
 * @brief specialized template for conversion rules see convert
 * 
 * @tparam RuleType::NumberToEnglishConversion
 */
template<>
struct ConversionRule<RuleType::NumberToEnglishConversion>
{
	/**
	 * @brief returns a number sequence converted to english words
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(std::string_view _string) noexcept;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t minInputSize = 1;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t maxInputSize = 3;
};

/**
 * @brief specialized template for conversion rules see convert
 * 
 * @tparam RuleType::RunLengthEncodingConversion
 */
template<>
struct ConversionRule<RuleType::RunLengthEncodingConversion>
{
	/**
	 * @brief returns a number sequence converted to english words
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(std::string_view _string) noexcept;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t minInputSize = 1;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t maxInputSize = std::numeric_limits<size_t>::max();
};

/**
 * @brief specialized template for conversion rules see convert
 * 
 * @tparam RuleType::AsRunLengthEncodingConversion
 */
template<>
struct ConversionRule<RuleType::AsRunLengthEncodingConversion>
{
	/**
	 * @brief returns a number sequence interpreted as run length encoding
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(std::string_view _string) noexcept;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t minInputSize = 2;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t maxInputSize = std::numeric_limits<size_t>::max();
};

/**
 * @brief specialized template for conversion rules see convert
 * 
 * @tparam RuleType::AsNumberConversion
 */
template<>
struct ConversionRule<RuleType::LookAndSayConversion>
{
	/**
	 * @brief returns a number sequence converted with run length encoding then to english words
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	static std::string convert(std::string_view _string) noexcept;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t minInputSize = 1;

	/**
	 * @brief the maximum supported input size for conversion
	 * 
	 */
	static constexpr size_t maxInputSize = std::numeric_limits<size_t>::max();
};

//TODO doc comments
class RuleBookIterator
{
public:
	bool operator!=(const RuleBookIterator& _other) const;
	bool operator==(const RuleBookIterator& _other) const;
	const ConversionRule& operator*() const;
	const ConversionRule* operator->() const;
	RuleBookIterator& operator++();
	RuleBookIterator& operator--();
private:
	friend class RuleBook;
	std::map<RuleType, std::unique_ptr<ConversionRule>>::const_iterator iterator;
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
	 * @return RuleBookIterator 
	 */
	RuleBookIterator begin() const;

	/**
	 * @brief returns an iterator to one past the last rule
	 * 
	 * @return RuleBookIterator 
	 */
	RuleBookIterator end() const;
private:
	/**
	 * @brief !INTERNAL! try_emplace a rule and return the result of try_emplace
	 * 
	 * @param _rule the rule type to emplace
	 * @return std::pair<std::map<Rule, std::unique_ptr<ConversionRule>>::iterator, bool> 
	 */
	std::pair<std::map<RuleType, std::unique_ptr<ConversionRule>>::iterator, bool> emplaceRule(RuleType _rule);
private:
	/**
	 * @brief !INTERNAL! map to store all added rules
	 * 
	 */
	std::map<RuleType, std::unique_ptr<ConversionRule>> rules;

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
