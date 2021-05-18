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

// TODO stable/unsorted_unique() to eliminate identical looking strings

/**
 * @brief returns factorial for given number
 *
 * @param number the number to get the factorial of
 * @return size_t the factorial or 0 if number > 20
 */
size_t factorial(size_t number);

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
