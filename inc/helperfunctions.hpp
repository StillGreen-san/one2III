/**
 * @file helperfunctions.hpp
 * @brief include file for helper functions
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief returns a all possible integer partitions of an integer within the give contraints
 *
 * @param _integer the integer to partition
 * @param _partcount the amount of parts to be splitted into
 * @param _minpart the minimum value of a part
 * @param _maxpart the maximum value of a part
 * @return std::vector<std::vector<size_t>>
 */
std::vector<std::vector<size_t>> integerPartitions(
    size_t _integer, size_t _partcount, size_t _minpart = 1, size_t _maxpart = 255);

/**
 * @brief checks if string is a valid number sequence
 *
 * @param _sequence the sring to check
 * @return true if it contains only numbers
 * @return false otherwise
 */
bool isValidNumberSequence(std::string_view _sequence);

/**
 * @brief returns string_views of a string for a partion of that string
 *
 * @param _string the string to partition
 * @param _partition a list of ints forming a partition
 * @return std::vector<std::string_view>
 */
std::vector<std::string_view> partitionString(std::string_view _string, const std::vector<size_t>& _partition);

template<typename T>
std::ostream& operator<<(std::ostream& _os, const std::vector<T>& _vec)
{
	_os << "[ ";
	std::string sep = "";
	for(auto& val : _vec)
	{
		if constexpr(std::is_same<T, uint8_t>::value || std::is_same<T, int8_t>::value)
		{
			_os << sep << static_cast<short>(val);
		}
		else
		{
			_os << sep << val;
		}
		sep = ", ";
	}
	_os << " ]";
	return _os;
}
