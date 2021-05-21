#pragma once

#include <ostream>
#include <string>
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
	if(number < ((sizeof(FACTORIAL_RESULTS)) / (sizeof(*FACTORIAL_RESULTS))))
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << "[ ";
	std::string sep = "";
	for(auto& val : vec)
	{
		if constexpr(std::is_same<T, uint8_t>::value || std::is_same<T, int8_t>::value)
		{
			os << sep << static_cast<short>(val);
		}
		else
		{
			os << sep << val;
		}
		sep = ", ";
	}
	os << " ]";
	return os;
}
