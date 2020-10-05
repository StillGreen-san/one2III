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

/**
 * @brief returns a number sequence interpreted as RLE, space separated 
 * 
 * @param _number 
 * @return std::string 
 */
std::string asRunLengthEncode(std::string_view _number);

/**
 * @brief returns a number sequence as roman numerals
 * 
 * @param _number 0 <=> 3999
 * @return std::string
 */
std::string romanNumerals(std::string_view _number);

/**
 * @brief returns a number in english words
 * 
 * @param _number 0 <=> 999
 * @return std::string 
 */
std::string numberToEnglish(std::string_view _number);
