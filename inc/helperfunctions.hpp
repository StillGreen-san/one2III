#pragma once

#include <ostream>
#include <string_view>
#include <vector>

/**
 * @brief maximum valid length of an input number sequence (limited by the factorial function (size of size_t))
 *
 */
constexpr size_t MAX_SEQUENCE_LENGTH = sizeof(detail::FACTORIAL_RESULTS) / sizeof(*detail::FACTORIAL_RESULTS);

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
 * @brief returns string_views of a string for a partion of that string
 *
 * @param string the string to partition
 * @param partition a list of ints forming a partition
 * @return std::vector<std::string_view>
 */
std::vector<std::string_view> partitionString(std::string_view string, const std::vector<size_t>& partition);

namespace detail
{
static constexpr size_t FACTORIAL_RESULTS[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800,
    479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000, 6402373705728000,
    121645100408832000, 2432902008176640000};
}
/**
 * @brief returns factorial for given number
 *
 * @param number the number to get the factorial of
 * @return size_t the factorial or 0 if number > 20
 */
constexpr size_t factorial(size_t number) noexcept
{
	using namespace detail;
	if(number < MAX_SEQUENCE_LENGTH)
	{
		return FACTORIAL_RESULTS[number];
	}
	return 0;
}

/**
 * @brief return the number of possible permutations for a partition with repetitions
 *
 * @param partition partition with repetitions
 * @return size_t the number of possible permutations
 */
size_t permutationsWithRepetitions(const std::vector<size_t>& partition);

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
