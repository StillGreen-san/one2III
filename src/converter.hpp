/**
 * @file convert.hpp
 * @brief include file for conversion functions
 */

#pragma once

#include <string>

/**
 * @brief returns a number sequence processed with RLE, space separated
 * 
 * @param _number
 * @return std::string
 */
std::string runLengthEncode(std::string_view _number);