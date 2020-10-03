/**
 * @file helper.hpp
 * @brief include file for helper functions
 */

#pragma once

#include <vector>

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