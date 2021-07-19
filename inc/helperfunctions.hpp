#pragma once

#include <ostream>
#include <string_view>
#include <vector>

/**
 * @brief returns a all possible integer partitions of an integer within the give contraints
 *
 * @param integer the integer to partition
 * @param partcount the amount of parts to be splitted into
 * @param minpart the minimum value of a part
 * @param maxpart the maximum value of a part
 * @return std::vector<std::vector<size_t>>
 */
std::vector<std::vector<size_t>> integerPartitions(
    size_t integer, size_t partcount, size_t minpart = 1, size_t maxpart = 255);

/**
 * @brief checks if string is a valid number sequence
 *
 * @param sequence the sring to check
 * @return true if it contains only numbers
 * @return false otherwise
 */
bool isValidNumberSequence(std::string_view sequence);

/**
 * @brief performs an unchecked conversion from std::string_view to INTEGER
 *
 * @tparam INTEGER the INTEGER type to convert to
 * @param view the string_view to convert from
 * @return INTEGER the converted number
 */
template<typename INTEGER, std::enable_if_t<std::is_integral_v<INTEGER>, int> = 0>
INTEGER viewToNumber(std::string_view view)
{
	INTEGER number = 0;
	for(char chr : view)
	{
		number *= 10;
		number += chr - '0';
	}
	return number;
}
