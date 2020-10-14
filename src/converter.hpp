/**
 * @file convert.hpp
 * @brief include file for conversion functions
 */

#pragma once

#include <string>

/**
 * @brief returns a number sequence processed with RLE, space separated
 * 
 * @param _number 1<=len=>inf
 * @return std::string the converted string
 */
std::string runLengthEncode(std::string_view _number);

/**
 * @brief returns a number sequence interpreted as RLE, space separated 
 * 
 * @param _number 2<=len=>inf
 * @return std::string the converted string
 */
std::string asRunLengthEncode(std::string_view _number);

/**
 * @brief returns a number sequence as roman numerals
 * 
 * @param _number "0" <=> "3999"
 * @return std::string the converted string
 */
std::string romanNumerals(std::string_view _number);

/**
 * @brief returns a number in english words
 * 
 * @param _number "0" <=> "999"
 * @return std::string the converted string
 */
std::string numberToEnglish(std::string_view _number);

/**
 * @brief returns a number sequence converted with run length encoding then to english words
 * 
 * @param _number 1<=len=>inf
 * @return std::string the converted string
 */
std::string lookAndSay(std::string_view _number);

//TODO asNumber conversion?
