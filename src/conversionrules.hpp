/**
 * @file conversionrules.hpp
 * @brief include file for conversion rules
 */

#pragma once

#include <string>
#include <map>
#include <memory>

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
 * @brief base class for all conversion rules
 */
class ConversionRule
{
public:
	/**
	 * @brief deleted: as min,- maxinputsize need to be explicitly initialized
	 * 
	 */
	ConversionRule() = delete;

	/**
	 * @brief returns a number sequence converted according to rule derived from this class
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
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
	/**
	 * @brief !INTERNAL! construct a new ConversionRule object
	 * 
	 * @param _minInputSize the minimum supported input size for conversion
	 * @param _maxInputSize the maximum supported input size for conversion
	 */
	ConversionRule(size_t _minInputSize, size_t _maxInputSize);

	/**
	 * @brief !INTERNAL! the minimum supported input size for conversion
	 * 
	 */
	const size_t minInputSize;

	/**
	 * @brief !INTERNAL! the maximum supported input size for conversion
	 * 
	 */
	const size_t maxInputSize;
};

class RomanNumeralConversion : public ConversionRule
{
public:
	/**
	 * @brief Construct a new RomanNumeralConversion rule
	 * 
	 */
	RomanNumeralConversion::RomanNumeralConversion();

	/**
	 * @brief returns a number sequence converted to roman numerals
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	std::string convert(std::string_view _string) const override;
};

class RunLengthEncodingConversion : public ConversionRule
{
public:
	/**
	 * @brief Construct a new RunLengthEncodingConversion rule
	 * 
	 */
	RunLengthEncodingConversion::RunLengthEncodingConversion();

	/**
	 * @brief returns a number sequence converted with run length encoding
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	std::string convert(std::string_view _string) const override;
};

class NumberToEnglishConversion : public ConversionRule
{
public:
	/**
	 * @brief Construct a new NumberToEnglishConversion rule
	 * 
	 */
	NumberToEnglishConversion::NumberToEnglishConversion();

	/**
	 * @brief returns a number sequence converted to english words
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	std::string convert(std::string_view _string) const override;
};

class AsRunLengthEncodingConversion : public ConversionRule
{
public:
	/**
	 * @brief Construct a new AsRunLengthEncodingConversion rule
	 * 
	 */
	AsRunLengthEncodingConversion::AsRunLengthEncodingConversion();

	/**
	 * @brief returns a number sequence interpreted as run length encoding
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	std::string convert(std::string_view _string) const override;
};

class LookAndSayConversion : public ConversionRule
{
public:
	/**
	 * @brief Construct a new LookAndSayConversion rule
	 * 
	 */
	LookAndSayConversion::LookAndSayConversion();

	/**
	 * @brief returns a number sequence converted with run length encoding then to english words
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	std::string convert(std::string_view _string) const override;
};

class AsNumberConversion : public ConversionRule
{
public:
	/**
	 * @brief Construct a new AsNumberConversion rule
	 * 
	 */
	AsNumberConversion::AsNumberConversion();

	/**
	 * @brief returns a number sequence as is
	 * 
	 * @param _string the number sequence to convert
	 * @return std::string the converted number sequence
	 */
	std::string convert(std::string_view _string) const override;
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
