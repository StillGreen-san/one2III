/**
 * @file conversionrules.hpp
 * @brief include file for conversion rules
 */

#pragma once

#include <string>
#include <map>
#include <memory>

enum class Rule : uint8_t
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

class LookAndSayConversion : public ConversionRule
{
public:
	LookAndSayConversion::LookAndSayConversion();

	std::string convert(std::string_view _string) const override;
};

class AsNumberConversion : public ConversionRule
{
public:
	AsNumberConversion::AsNumberConversion();

	std::string convert(std::string_view _string) const override;
};

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
	std::map<Rule, std::unique_ptr<ConversionRule>>::const_iterator iterator;
};

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
	bool add(Rule _rule);

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

	RuleBookIterator begin() const;
	RuleBookIterator end() const;
private:
	std::pair<std::map<Rule, std::unique_ptr<ConversionRule>>::iterator, bool> emplaceRule(Rule _rule);
private:
	std::map<Rule, std::unique_ptr<ConversionRule>> rules;
	size_t minInputSize = std::numeric_limits<size_t>::max();
	size_t maxInputSize = std::numeric_limits<size_t>::min();
};
