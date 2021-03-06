#pragma once

#include "ruletype.hpp"

#include <set>

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
	bool add(RuleType rule);

	/**
	 * @brief gets the minimum supported input size for conversion
	 *
	 * @return size_t minimum supported input size for conversion
	 */
	size_t getMinInputSize() const noexcept;

	/**
	 * @brief gets the maximum supported input size for conversion
	 *
	 * @return size_t maximum supported input size for conversion
	 */
	size_t getMaxInputSize() const noexcept; // TODO change redundat descriptions to only return desc?

	/**
	 * @brief returns an iterator to the first rule
	 *
	 * @return std::set<RuleType>::const_iterator
	 */
	std::set<RuleType>::const_iterator begin() const noexcept;

	/**
	 * @brief returns an iterator to one past the last rule
	 *
	 * @return std::set<RuleType>::const_iterator
	 */
	std::set<RuleType>::const_iterator end() const noexcept;

	/**
	 * @brief returns the number of added rules
	 *
	 * @return size_t the number of rules
	 */
	size_t size() const noexcept;

	/**
	 * @brief returns the rules at the specified index
	 *
	 * @param index the index to return (unchecked)
	 * @return RuleType the rule at _index
	 */
	RuleType operator[](size_t index) const;

private:
	std::set<RuleType> rules;
	size_t minInputSize = std::numeric_limits<size_t>::max();
	size_t maxInputSize = std::numeric_limits<size_t>::min();
};
