/**
 * @file helper.hpp
 * @brief include file for helper functions
 */

#pragma once

#include <vector>
#include <string>

/**
 * @brief returns a all possible integer partitions of an integer within the give contraints
 * 
 * @param _integer the integer to partition
 * @param _partcount the amount of parts to be splitted into
 * @param _minpart the minimum value of a part
 * @param _maxpart the maximum value of a part
 * @return std::vector<std::vector<uint8_t>> 
 */
std::vector<std::vector<uint8_t>> integerPartitions(uint8_t _integer,
	uint8_t _partcount, uint8_t _minpart = 1, uint8_t _maxpart = 255);

/**
 * @brief checks if string is a valid number sequence
 * 
 * @param _sequence the sring to check
 * @return true if it contains only numbers
 * @return false otherwise
 */
bool isValidNumberSequence(const std::string& _sequence);

/**
 * @brief returns string_views of a string for a partion of that string
 * 
 * @param _string the string to partition
 * @param _partition a list of ints forming a partition
 * @return std::vector<std::string_view> 
 */
std::vector<std::string_view> partitionString(std::string_view _string, const std::vector<uint8_t>& _partition);
