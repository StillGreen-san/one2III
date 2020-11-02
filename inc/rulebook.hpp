/**
 * @file rulebook.hpp
 * @brief include file for RuleBook class
 */

#pragma once

#include <set>

#include "ruletype.hpp"

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